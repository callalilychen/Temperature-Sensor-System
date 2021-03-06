#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdint.h>
//#include <stdlib.h>
#include <util/delay.h>
//#include "strfun.h"
#include "usart.h"
#define DELAY_AFTER_MR_MS 55
#define DELAY_BEFORE_DF_US 20
#define START_TIMER TCCR0B = (1<< CS02 | 1 << CS00);
#define STOP_TIMER TCCR0B = 0; //disable timer
#define SLA 0x28
#define CMODE 7
#define STALE 6
#define TSTART 60
#define TLONG 90
#define TSHORT 30
#define CRC8 49
uint8_t capH=0;
uint8_t capL=0;
uint8_t tempH=0;
uint8_t tempL=0;
uint8_t crc=0;
uint8_t result=0xff;
uint8_t counter_sent = 0;
// FIXME converted roughly for test
uint8_t cap=0xff;
uint8_t temp=0xff;
uint8_t counter=0;

void waitUntilFinished(){
  while(!(TWCR & (1 << TWINT))){
    asm("nop");
    // Sorry, I'm busy wating!!
  }
}
void waitUntil(){
  while(!(TWCR & (1 << TWINT))){
    printf("TWSR is %x\n\r", TWSR);
    asm("nop");
    // Sorry, I'm busy wating!!
  }
}
#define  MEASURINGREQUEST\
/*{*/\
  /*printf("Measurement Request\n\r");*/\
  /* Start condition*/\
  TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));\
  waitUntilFinished();\
  /*printf("TWCR out= %x\n\r", TWCR);*/\
  /*printf("TWSR= %x\n\r", TWSR);*/\
  if (TWSR != 0x8){\
    return;  \
  }\
  /*printf("Started\n\r");*/\
  /* SLA + W (bit 0)*/\
  TWDR = (SLA << 1);\
  TWCR = ((1 << TWINT) | (1 << TWEN));\
  waitUntilFinished();\
  /* TWSR = 0x18 means SLA+W has been transmitted; ACK has been received*/\
  if (TWSR != 0x18){\
    return;\
  }\
  /* Stop condition*/\
  TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));\
 /* printf("Required\n\r");*/\
  /* TODO what happend???*/\
  /* waitUntilFinished();*/\
/*}*/

uint8_t readByte(uint8_t ack){
  //printf("TWDR SLA + R = 0x%x\n\r", TWDR);
  TWCR = ((1 << TWINT) | (ack << TWEA) | (1 << TWEN));
  //printf("TWDR already received ??? = 0x%x\n\r", TWDR);
  waitUntilFinished();
  // TWSR = 0x50 means Data byte has been received; ACK has been returned
  if (TWSR != 0x50){
    return 0xff;
  }
  //printf("Read finished\n\r");
  return TWDR;
}

#define DATAFETCH\
/*{*/\
  /* printf("Data Fetch\n\r");*/\
  /* Start condition*/\
  TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));\
  waitUntilFinished();\
  if (TWSR != 0x8){\
    return;  \
  }\
  /* SLA + R (bit 1)*/\
  TWDR = (SLA << 1) | (1 << 0);\
  TWCR = ((1 << TWINT) | (1 << TWEN));\
  waitUntilFinished();\
  /* TWSR = 0x40 means SLA+R has been transmitted; ACK has been received*/\
  if (TWSR != 0x40){\
    return;\
  }\
\
  capH = readByte(1);\
  capL = readByte(1);\
  tempH = readByte(1);\
  tempL = readByte(0);\
\
  /* Stop condition*/\
  TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));\
 /* printf("Fetched\n\r");*/\
/*}*/

#define SEND_START\
/*{*/\
  PORTC &= ~(1<<PC0);  \
  _delay_us(TSTART);\
  PORTC |= (1<<PC0);  \
  _delay_us(TSTART);\
  PORTC &= ~(1<<PC0);  \
/*}*/

#define SEND0\
/*{*/\
  _delay_us(TLONG);\
  PORTC |= (1<<PC0);  \
  _delay_us(TSHORT);\
/*}*/

#define SEND1\
/*{*/\
  _delay_us(TSHORT);\
  PORTC |= (1<<PC0);  \
  _delay_us(TLONG);\
/*}*/

#define SEND_FIRST_BYTE(byte) {\
  int8_t index = 0;\
  int8_t byte_copy = byte;\
  for(index=7; index >= 0; index--){\
    PORTC &= ~(1<<PC0);  \
    if(byte_copy & (1 << 7)){\
      SEND1\
    }else{\
      SEND0\
    }\
    byte_copy = (byte_copy<<1);\
  }\
}

void sendBYTE(uint8_t byte){
  int8_t index = 0;
  for(index=7; index >= 0; index--){
    PORTC &= ~(1<<PC0);
    if(byte & (1 << 7)){
      SEND1
    }else{
      SEND0
    }
    byte = (byte<<1);
  }
}

#define CONVERT_TO_ZAC\
/*{*/\
  SEND_START\
  SEND_FIRST_BYTE(capH)\
  sendBYTE(capL);\
  sendBYTE(tempH);\
  sendBYTE(tempL);\
  sendBYTE(crc);\
/*}*/

#define DO_COMPUTING(byte, index) \
/*{*/\
  if(crc & (1<<7)){\
    crc = crc << 1;\
    crc |= ((byte >> index) & 1);\
    crc ^= CRC8;\
  } else  {\
    crc = crc << 1;\
    crc |= ((byte >> index) & 1);\
  }\
/*}*/

#define COMPUTE_CRC\
/*{*/\
  crc = capH;\
  int8_t index = 7;\
  for(index=7; index >= 0; index--){\
    DO_COMPUTING(capL, index)\
  }\
  for(index=7; index >= 0; index--){\
    DO_COMPUTING(tempH, index)\
  }\
  for(index=7; index >= 0; index--){\
    DO_COMPUTING(tempL, index)\
  }\
  for(index=7; index >= 0; index--){\
    DO_COMPUTING(0, index)\
  }\
  printf("\t\t\t!!!CRC is %x\n\r", crc);\
/*}*/

#define DO_COMPUTING2(byte, index) \
/*{*/\
  if(result & (1<<7)){\
    result = result << 1;\
    result |= ((byte >> index) & 1);\
    result ^= CRC8;\
  } else  {\
    result = result << 1;\
    result |= ((byte >> index) & 1);\
  }\
/*}*/
void verifyCRC(){
  result = capH;
  int8_t index = 7;
  for(index=7; index >= 0; index--){
    DO_COMPUTING2(capL, index)
  }
  for(index=7; index >= 0; index--){
    DO_COMPUTING2(tempH, index)
  }
  for(index=7; index >= 0; index--){
    DO_COMPUTING2(tempL, index)
  }
  for(index=7; index >= 0; index--){
    DO_COMPUTING2(crc, index)
  }
  printf("\t\t\t!!!Result is %x\n\r", result);
}

// interrupt handler for output compare register A
ISR(TIMER0_COMPA_vect){
  if (counter_sent < 40){
    if(capH & (1<<7)){
    // send 1
      OCR0B = TSHORT;
    }else{
    // send 0
      OCR0B = TLONG;
    }
    // enable compare match B interrupt
    TIMSK0 |= ( 1 << OCIE0B ); 
    // shift
    crc = crc << 1;
    // use "rol" to shift the other two bits with carry
    asm("rol %0" : "=r" (tempL) : "0" (tempL));
    asm("rol %0" : "=r" (tempH) : "0" (tempH));
    asm("rol %0" : "=r" (capL) : "0" (capL));
    asm("rol %0" : "=r" (capH) : "0" (capH));
  } else{
    // Set OC0B at the beginning
    TCCR0A |= (3 << COM0B0); 
    TCCR0B = (1 << FOC0B);
    // stop sending
    TCCR0A &= ~(3 << COM0B0); 
    TIMSK0 &= ~( 1 << OCIE0A); 
    TIMSK0 &= ~( 1 << OCIE0B); 
  }
}

// interrupt handler for output compare register B
ISR(TIMER0_COMPB_vect){
	TIMSK0 &= ~( 1 << OCIE0B); 
  OCR0B = 0;
}

void convertToZAC(){
  // send START bit
  counter_sent = 0;
  OCR0B = 0;
  TCCR0A |= (1 << COM0B0); 
  TCNT0=0;
  // enable compare match A interrupt
	TIMSK0 |= ( 1 << OCIE0A ); 
  OCR0B = TSTART;
  // enable compare match B interrupt
	TIMSK0 |= ( 1 << OCIE0B ); 
  
}

void loop(){
  // TODO debug, LED blink
 // _delay_ms(500);
 // PORTD = PORTD ^ (1<<PD6);
 // _delay_ms(500);
 // PORTD = PORTD ^ (1<<PD6);
  MEASURINGREQUEST
    // measurement will be ready after 50...60ms (this value was aquired by experimental meassurement).
  _delay_ms(DELAY_AFTER_MR_MS);
  counter=0;
  do{
    _delay_us(DELAY_BEFORE_DF_US);
    counter ++;
    DATAFETCH
    /* Do datafetch until the stale bit is 0 
     * If more than 100 times, give up */
  }while((capH & ( (1 << STALE))) && counter <100 );
  //printf("Counter is %d\n\r", counter);
  capH = capH & 0x3f;
  COMPUTE_CRC
  verifyCRC();

  printf("capH = %x\n\r", capH);
  printf("capL = %x\n\r", capL);
  printf("tempH = %x\n\r", tempH);
  printf("tempL = %x\n\r", tempL);

  cap = ((capH*3) >> 1) + (capH >>4);
  temp = (tempH >> 1) + (tempH >> 3) + (tempH >> 6);

  printf("converted cap = %u\n\r", cap);
  printf("converted temp = %u - 40 = %d\n\r", temp, temp-40);

  CONVERT_TO_ZAC 
  // Use timer
  convertToZAC();
}

int main (void)
{
	//          ppp static FILE usart_stdout = FDEV_SETUP_STREAM( mputc, 0, _FDEV_SETUP_WRITE);
	//          ppp stdout = &usart_stdout;

	//          ppp uart_init();
	//          ppp sei();

  //          ppp // init registers for i2c
  //          ppp // Set Fscl 100 kHz
  //          ppp TWBR = 32; 

  //          ppp printf("Start\n\r");
  //          ppp printf("OC0B = %d\n\r", PORTD);
  //          ppp // PC0 as output port
	//          ppp DDRC |= (1<<PC0);
  //          ppp   // TODO debug, LED blink
	//          ppp DDRD |= (1<<PD6);
  //          ppp PORTD = PORTD ^ (1<<PD6);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD6);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD6);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD6);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD6);

  //          ppp   // TODO debug, LED blink
	//          ppp DDRD |= (1<<PD5);
  //          ppp PORTD = PORTD ^ (1<<PD5);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD5);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD5);
  //          ppp   _delay_ms(500);
  //          ppp PORTD = PORTD ^ (1<<PD5);
  //          ppp   _delay_ms(500);
  // Clear timer TCNT0 on compare match register A: OCR0A
  //TCCR0A |= (1 << WGM01); 
  // Set prescaling clk/8
  //TCCR0B |= (1 << CS01);
  // Every 120 us will clear the timer 
  //OCR0B = 120;
	// enable timer output compare match A interrupt when sending bits
	// TIMSK0 |= ( 1 << OCIE0A ); 
  // Timer init 
  //START_TIMER 
  //TCNT0 = 0;
  // Set PD5 as output port
  //DDRD |= (1<<PD5);
  //printf("OC0B = %d\n\r", PORTD);
  // Clear OC0B at the beginning

  //TCCR0A |= (1 << COM0B1); 
  //TCCR0A &= ~(1 << COM0B0); 
  //TCCR0B = (1 << FOC0B);



  //printf("OC0B = %d\n\r", PORTD);
  //TCCR0A |= ((1 << COM0B0) | (1 << COM0B1)); 
  DDRD = (1<<PD5);
  OCR0B = 120;
  //TCCR0B = (1 << CS01);
  // Set OC0B at the beginning
  TCCR0A |= (1<<COM0B0);
  TCCR0A |= (1<<COM0B1);
  TCCR0B |= (1 << FOC0B);
  _delay_ms(500);
  // clear
  TCCR0A &= ~(1<<COM0B0);
  TCCR0A |= (1<<COM0B1);
  TCCR0B |= (1 << FOC0B);
  _delay_ms(500);
  // set
  TCCR0A |= (1<<COM0B0);
  TCCR0A |= (1<<COM0B1);
  TCCR0B |= (1 << FOC0B);
  //TCCR0B = (1 << FOC0B);
  //TCCR0A &= ~(3 << COM0B0); 
  //printf("OC0B = %d\n\r", PORTD);
  while(1){
   // loop();
  }
}
