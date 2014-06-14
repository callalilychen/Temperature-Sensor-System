#include "configuration.h"

//#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usart.h"
#include "sock_stream.h"
#include <Ethernet.h>
#include "w5100.h"
#include "socket.h"
#include "collector_twi.h"
#include "packet.h"
// set debug mode
// #define DEBUG
//
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
uint8_t mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xE3, 0x5B};
uint8_t ip[] = {10,0,1, 100};
uint8_t gw[] = {10,0,1, 1 };
uint8_t subnet = 16;
uint8_t subnetM[] = {255, 255, 0, 0};
uint16_t port = 8888;
uint8_t ip_db[] = {10,0,1, 100};
uint16_t port_db = 8888;
uint8_t clientSock = MAX_SERVER_SOCK_NUM;
uint8_t serverSock[MAX_SERVER_SOCK_NUM];
uint8_t data_request[MAX_SERVER_SOCK_NUM] = {0};

uint8_t listeningSock = MAX_SERVER_SOCK_NUM;
uint8_t closedSock = MAX_SERVER_SOCK_NUM;

uint32_t measure_interval = 1000;

char cmdBuff[MAX_CMD_LEN];
char receiveBuff[MAX_SERVER_SOCK_NUM][MAX_CMD_LEN];
uint8_t receiveBuffPointer[MAX_SERVER_SOCK_NUM] = {0}; // Point to a byte, which will be written

void send_result(struct dummy_packet * packets);
void (*twi_access_fun)();

#define UI_READY 0
#define UI_TWILOCK 1
uint8_t ui_state = UI_READY;

struct cmd{
  const char * name;
  void (*handle)(uint8_t, char*);
};

// XXX cmdLen should be always the length of the registered cmd array below! 
const uint8_t cmdLen = 12;
struct cmd cmds[]={
  {"ip", handleIp},
  {"port", handlePort},
  {"mac", handleMac},
  {"gw", handleGw},
  {"reset", handleReset},
  {"ip-db", handleIpDB},
  {"port-db", handlePortDB},
  {"twiaddr", handleTwiaddr},
  {"s", handleScan},
  {"m", handleDoMeasurement},
  {"v", handleViewMeasurement},
  {"i", handleInterval}
};

const char WillSet[] PROGMEM = " will be set to ";
const char IfUpdate[] PROGMEM = " (update option: reset)\n";
const char UpdateOption[] PROGMEM = ", update option: ";
const char WillReset[] PROGMEM = "The ethernet service will be reset, the future login is ";
const char Addr[] PROGMEM = " <addr>\n";


int8_t toSubnetMask(uint8_t subnet, uint8_t* addr){
  int8_t indexByte = 0;
  int8_t indexBit = 0;
  printf("Subnet Mask: %d.%d.%d.%d\n\r", subnetM[0], subnetM[1], subnetM[2], subnetM[3]);
  while((subnet >> 3) >0 ){
  printf("Subnet: %d %d\n\r", subnet, subnet-8<subnet);
    addr[indexByte] = 255;
    indexByte++;
    subnet -= 8;
  }
  if(indexByte>=4){
    return 0;
  }
  while(subnet != 0 ){
    addr[indexByte] |= 1 << indexBit;
    indexBit ++;
    subnet--;
    if(indexBit>=8){
      return 0;
    }
  }
  printf("Subnet Mask: %d.%d.%d.%d\n\r", subnetM[0], subnetM[1], subnetM[2], subnetM[3]);
  return 1;
}

int8_t convertParamToBytes(char * buff, int8_t len, uint8_t * params){
  int8_t index;
  int8_t paramIndex =0;
  int8_t paramCounter =0;
  char paramBuff[MAX_PARAM_LEN];
  for(index=0; index<len; index++){
    if(paramIndex<MAX_PARAM_LEN && buff[index]>=48 && buff[index]<=57){
      paramBuff[paramIndex] = buff[index];
      paramIndex++;
    }else if(buff[index] == '\0'){
      break;
    }else{
      if(paramIndex>0){
        paramBuff[paramIndex] = '\0';
        // FIXME for mac hex 
        params[paramCounter] = atoi(paramBuff);
        paramCounter++;
        paramIndex = 0;
      }
    }
  }
  if(paramIndex>0){
    paramBuff[paramIndex] = '\0';
    params[paramCounter] = atoi(paramBuff);
    paramCounter++;
  }
  return paramCounter;
}

void beginService() {
  //Init and config ethernet device w5100
  toSubnetMask(subnet, subnetM);
  W5100.init();
  W5100.setMACAddress(mac);
  W5100.setIPAddress(ip);
  W5100.setGatewayIp(gw);
  W5100.setSubnetMask(subnetM);
  // TODO reset client to db
  // Create the first server socket
  socket(0, SnMR::TCP, port, 0);
  serverSock[0] = W5100.readSnSR(0);
  while(!listen(0)){
    // wait a second and try again
    _delay_ms(1000);
  }
}



uint8_t print4dotarr(FILE *stream, uint8_t * arr){
  return fprintf(stream, "%d.%d.%d.%d", arr[0], arr[1], arr[2], arr[3]);
}


void dataAvailable(struct dummy_packet * received, uint8_t src_addr){
	uint8_t i;
	for(i=0; i< MAX_SERVER_SOCK_NUM; i++){
		// TODO: check if socket is still connected.
		if (data_request[i]){
			stream_set_sock(i);
			fprintf(&sock_stream, "%u :: ", src_addr);
			send_result(received);
		}
	}
}

void handleViewMeasurement(uint8_t sock, char* paramsStr){
	uint8_t socket = stream_get_sock();
	data_request[socket] = (!data_request[socket]);
}

void handleInterval(uint8_t sock, char* paramsStr){
  int16_t paramsCount=0;
	uint32_t interval_tmp;
  paramsCount = fscanf(&sock_stream, "%lu", &interval_tmp);
	if(paramsCount == 1){
		measure_interval = interval_tmp*1000;
		fprintf(&sock_stream, "OK\n");
	}
  fprintf(&sock_stream, "interval: %lu\n", measure_interval/1000);
}

void handleIp(uint8_t sock, char* paramsStr){
  int8_t index;
  int16_t paramsCount=0;
  uint8_t ipTMP[4];
  uint8_t subnetTMP; 
  fprintf(&sock_stream, "ip: ");
  paramsCount = fscanf(&sock_stream, "%u.%u.%u.%u/%u", ipTMP, ipTMP+1, ipTMP+2, ipTMP+3, &subnet);
  if(paramsCount==5){
    for(index=0; index<4; index++){
      ip[index] = ipTMP[index];
    }
  }
  print4dotarr(&sock_stream, ip);
  fprintf(&sock_stream, "/%d", subnet);
  if(paramsCount!=5){
    fprintf(&sock_stream, "%S", UpdateOption);
  }else{
    fprintf(&sock_stream, "%S", IfUpdate);
  }
}

void handleGw(uint8_t sock, char* paramsStr){
  int8_t index;
  int16_t paramsCount=0;
  uint8_t gwTMP[4];
  fprintf(&sock_stream, "gw: ");
  paramsCount = sscanf(paramsStr, "%u.%u.%u.%u", gwTMP, gwTMP+1, gwTMP+2, gwTMP+3);
  if(paramsCount == 4){
    for(index=0; index<4; index++){
      gw[index] = gwTMP[index];
    }
  }
  print4dotarr(&sock_stream, gw);
  if(paramsCount!=4){
    fprintf(&sock_stream, "%S", UpdateOption);
  }else{
    fprintf(&sock_stream, "%S", IfUpdate);
  }
}

void handleMac(uint8_t sock, char* paramsStr){
  int8_t index;
  int16_t paramsCount=0;
  uint8_t macTMP[6];
  fprintf(&sock_stream, "mac: ");
  paramsCount = sscanf(paramsStr, "%x:%x:%x:%x:%x:%x", macTMP, macTMP+1, macTMP+2, macTMP+3, macTMP+4, macTMP+5);
  if(paramsCount == 6){
    for(index=0; index<4; index++){
      mac[index] = macTMP[index];
    }
  }
  fprintf(&sock_stream, "%d:%d:%d:%d:%d:%d", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  if(paramsCount!=6){
    fprintf(&sock_stream, "%S", UpdateOption);
  }else{
    fprintf(&sock_stream, "%S", IfUpdate);
  }
}

void handlePort(uint8_t sock, char* paramsStr){
  fprintf(&sock_stream, "port: ");
  if(sscanf(paramsStr, "%u", &port)==1){
    fprintf(&sock_stream, "%S", UpdateOption);
  }else{
    fprintf(&sock_stream, "%S", IfUpdate);
  }
}

void handleReset(uint8_t sock, char* paramsStr){
  uint8_t index;
  // broadcast
  stream_set_sock(MAX_SERVER_SOCK_NUM); 
  fprintf(&sock_stream, "%S", WillReset);
  print4dotarr(&sock_stream, ip);
  fprintf(&sock_stream, ":%d\n", port);
  sock_stream_flush();
  for(index= 0; index<MAX_SERVER_SOCK_NUM; index++){
    disconnect(index);
  }
  // Wait a second to close all sockets
  _delay_ms(1000);
  // TODO LEDs action
  for(index= 0; index<MAX_SERVER_SOCK_NUM; index++){
    if(W5100.readSnSR(index) != SnSR::CLOSED){
      // If a socket is still not closed, force it
      close(index);
    }
  }
  beginService();
}

void handleIpDB(uint8_t sock, char* paramsStr){
  int8_t index;
  uint8_t ipTMP[4];
  int16_t paramsCount=0;
  fprintf(&sock_stream, "db ip: ");
  paramsCount = sscanf(paramsStr, "%u.%u.%u.%u/%u", ipTMP, ipTMP+1, ipTMP+2, ipTMP+3);
  if(paramsCount==4){
    for(index=0; index<4; index++){
      ip_db[index] = ipTMP[index];
    }
  }
  print4dotarr(&sock_stream, ip_db);
  if(paramsCount!=4){
    fprintf(&sock_stream, "%S", UpdateOption);
  }else{
    fprintf(&sock_stream, "%S", IfUpdate);
  }
}

void handlePortDB(uint8_t sock, char* paramsStr){
  fprintf(&sock_stream, "db port: ");
  if(sscanf(paramsStr, "%u", &port)==1){
    fprintf(&sock_stream, "%S", UpdateOption);
  }else{
    fprintf(&sock_stream, "%S", IfUpdate);
  } 
}

void send_result(struct dummy_packet * packets){
  char buffer[10];
	uint8_t s;
	int16_t temp;
  for (s=0;s<8;s++){
    fprintf(&sock_stream, " | P%u: ", s+1);
    if(packets[s].header.error && packets[s].header.connected){
      fprintf(&sock_stream, " ERROR ");
    }
    if(packets[s].header.connected){
      switch(packets[s].header.type){
        case PACKET_TYPE_TSIC:
          temp =  ((struct tsic_packet *)(packets) )[s].temperature;
          fprintf(&sock_stream, "T = %d.%02d", temp/100, temp%100);
          //printf(" T = %d", ( (struct tsic_packet *)(packets) )[s].temperature);
          break;
        case PACKET_TYPE_HYT:
          fprintf(&sock_stream, "T = %d", ( (struct hyt_packet *)(packets) )[s].temperature);
          fprintf(&sock_stream, " H = %d", ( (struct hyt_packet *)(packets) )[s].humidity);
          break;
        default:
          fprintf(&sock_stream, "---?---");
          break;
      }
    }else{
      fprintf(&sock_stream,  "---nc---");
    }
  }
  fprintf(&sock_stream,  "\n");
}

void handleDoMeasurement(uint8_t sock, char* paramsStr){
	printf("handler do measure\n\r");
  twi_start_measurement(0);
	uint8_t iaddr;
	uint8_t addr;
  uint8_t state;
  struct dummy_packet received[8];
	for (iaddr=0;iaddr<num_boards;iaddr++){
		addr = scanresults[iaddr];
		//printf("# %u # ", addr);
		state = twi_receive_data(addr, ((uint8_t*)received),8*sizeof(struct dummy_packet));
    if (state){
      send_result(received);
    }
  }


}

void handleScan_access(void){
	// FIXME: socket number is hardcoded here
	uint8_t sock = 0;
	uint8_t i;
	num_boards = twi_scan(scanresults, 20);
  fprintf(&sock_stream, "found boards");
	printf("found boards: ");
	for (i=0;i<num_boards;i++){
		printf("%u", scanresults[i]);
		uint8_t t;
    fprintf(&sock_stream, " %u", scanresults[i]);
	}
	printf("\n\r");
  fprintf(&sock_stream,  "\n");
}

void handleScan(uint8_t sock, char * paramsStr){
	//printf("sc\n\r");
	twi_access_fun = handleScan_access;
	ui_state = UI_TWILOCK;
}

void handleTwiaddr_access(void){
  uint8_t synerr = 1;
	uint8_t old_addr, new_addr;
	if(fscanf(&sock_stream, "%u.%u", &old_addr, &new_addr) ==2){
		printf("par %u, %u", old_addr, new_addr);
		//if(buff[4]=='g'){
		synerr = 0;
		if(twi_set_address(old_addr, new_addr)){
			fprintf(&sock_stream, "success\n");
		}else{
			fprintf(&sock_stream, "failed\n");
		}
	}
  if (synerr){
    fprintf(&sock_stream, "Usage: twiaddr <old>%S", Addr);
  }
}

void handleTwiaddr(uint8_t sock, char * paramsStr){
	//twi_access_fun = handleTwiaddr_access;
	//ui_state = UI_TWILOCK;
  uint8_t synerr = 1;
	uint8_t old_addr;
	uint8_t new_addr;
  int16_t paramsCount=0;
  paramsCount = fscanf(&sock_stream, "%u.%u", &old_addr, &new_addr);
	if(paramsCount == 2){
		printf("par %u, %u", old_addr, new_addr);
		//if(buff[4]=='g'){
		synerr = 0;
		//if(twi_set_address(old_addr, new_addr)){
		//	fprintf(&sock_stream, "success\n");
		//}else{
		//	fprintf(&sock_stream, "failed\n");
		//}
	}
  if (synerr){
    fprintf(&sock_stream, "Usage: twiaddr <old>%S", Addr);
  }
}

inline void sendError(uint8_t sock){
  fprintf(&sock_stream, "Error!\n");
}

char* cmpCMD(char* cmdstr, const char * cmd){
  while(*cmd!='\0' && cmdstr!='\0' && *cmd == *cmdstr){
    cmd++;
    cmdstr++;
  }
  if(*cmd=='\0'){
    if(*cmdstr=='\0'){
      return cmdstr; // equal, no param
    }else if(*cmdstr == ' '){
      cmdstr ++;
      return cmdstr; // equal, contains param
    }
  }
  return NULL; // not equal
}

void execCMD(uint8_t sock, char * buff){
  uint8_t params[MAX_PARAM_COUNT];
  int8_t paramCounter =0;
  int8_t index;
  char * cmpedBuff;
  struct cmd cmd;
  printf("Compare %s\n\r", buff);
  for(index= 0; index<cmdLen; index++){
    cmd = cmds[index];
    cmpedBuff = cmpCMD(buff, cmd.name);
    if(cmpedBuff!=NULL){
      cmd.handle(sock, cmpedBuff);
      sock_stream_flush();
      return;
    }
  }
  fprintf(&sock_stream, "Usage: TODO\n");
  sock_stream_flush();
}

void handleCMD(uint8_t sock){
  uint8_t pointer=0;
  int16_t b;
  int8_t cmd_flag=1;
  stream_set_sock(sock); 
  while((b=fgetc(&sock_stream)) != EOF){
    if(b == ' ' || b == '\n' || b == ';'){
      if(pointer>0){
        cmdBuff[pointer++] = '\0';
        execCMD(sock, cmdBuff);
        cmd_flag = 0;
      }
      if(b == '\n' || b == ';'){
        cmd_flag=1;
      }
      pointer = 0;
      continue;
    }
    if(pointer >= MAX_CMD_LEN){
      pointer = 0;
    }
    // XXX The first char should be alphabet in low case 
    if(pointer == 0 && (b<97 || b>122)){
      printf("first char %c %u\n\r", b,b);
      continue;
    }
    if(cmd_flag){
      cmdBuff[pointer++] = b;
    }
  }
}

void serve(){
  uint8_t i;
  closedSock = MAX_SERVER_SOCK_NUM;
  listeningSock = MAX_SERVER_SOCK_NUM;
  for(i=0; i<MAX_SERVER_SOCK_NUM; i++){
    serverSock[i] = W5100.readSnSR(i);
    //printf("%u. Status: %x\n\r",i, serverSock[i]);
#ifdef DEBUG
    printf("%u. Status: %x\n\r",i, serverSock[i]);
#endif
    switch (serverSock[i]){
      case SnSR::CLOSED:
        closedSock = i;
        break;
      case SnSR::INIT:
#ifdef DEBUG
        printf("Init Sock: %u\n\r", i);
#endif
        break;
      case SnSR::LISTEN:
        listeningSock = i;
        break;
      case SnSR::ESTABLISHED:
        handleCMD(i);
        break;
      case SnSR::CLOSING:
        // TODO if readCMD??
        printf("Closing Sock: %u\n\r", i);
        break;
      case SnSR::TIME_WAIT:
        printf("Time wait Sock: %u\n\r", i);
        break;
      case SnSR::CLOSE_WAIT:
        // TODO implement see Arduino Ethernet library
        printf("Close wait Sock: %u\n\r", i);
        break;
      default:
        break;
#ifdef DEBUG
        printf("Sock %u Status: %x\n\r", i, serverSock[i]);
#endif
    }
  }
#ifdef DEBUG
  printf("Listening socket %d, closed socket %d\n\r",listeningSock, closedSock);
#endif
  if(listeningSock == MAX_SERVER_SOCK_NUM && closedSock < MAX_SERVER_SOCK_NUM){
    socket(closedSock, SnMR::TCP, port, 0);    
    listen(closedSock);
  }
}

void ui_loop(){
	switch(ui_state){
		case UI_READY:
			serve();
			break;
		case UI_TWILOCK:
			// we do not process new socket inputs, as we have to wait for the twi bus to become ready:
			if(twi_try_lock_bus()){
				// we aquired the bus
				// now we have to do our access as fast as possible, as others might wait for bus access:
				// call command handler, who waits for access to the bus:
				twi_access_fun();
				// we again accept commands
				ui_state = UI_READY;
				twi_free_bus();
			}
			break;
	}
}

void setupServer() {
  sock_stream_init();
  printf("Set up server\n\r");
  beginService();
  //while(1){
  //  serve();
  //}
}


