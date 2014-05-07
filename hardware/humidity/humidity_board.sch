EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:TSic50xF
LIBS:HYT271
LIBS:ST485
LIBS:humidity_board-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "7 may 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VCC #PWR01
U 1 1 532DBFEE
P 4900 1750
F 0 "#PWR01" H 4900 1850 30  0001 C CNN
F 1 "VCC" H 4900 1850 30  0000 C CNN
F 2 "" H 4900 1750 60  0000 C CNN
F 3 "" H 4900 1750 60  0000 C CNN
	1    4900 1750
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 532DDB70
P 8250 2750
F 0 "R6" V 8330 2750 40  0000 C CNN
F 1 "120" V 8257 2751 40  0000 C CNN
F 2 "~" V 8180 2750 30  0000 C CNN
F 3 "~" H 8250 2750 30  0000 C CNN
	1    8250 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 532DDBFC
P 6200 4050
F 0 "#PWR02" H 6200 4050 30  0001 C CNN
F 1 "GND" H 6200 3980 30  0001 C CNN
F 2 "" H 6200 4050 60  0000 C CNN
F 3 "" H 6200 4050 60  0000 C CNN
	1    6200 4050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 532DDC02
P 6200 850
F 0 "#PWR03" H 6200 950 30  0001 C CNN
F 1 "VCC" H 6200 950 30  0000 C CNN
F 2 "" H 6200 850 60  0000 C CNN
F 3 "" H 6200 850 60  0000 C CNN
	1    6200 850 
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 532DDC2C
P 6650 1450
F 0 "C4" H 6650 1550 40  0000 L CNN
F 1 "10uF" H 6656 1365 40  0000 L CNN
F 2 "~" H 6688 1300 30  0000 C CNN
F 3 "~" H 6650 1450 60  0000 C CNN
	1    6650 1450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 532DDC32
P 7050 1650
F 0 "#PWR04" H 7050 1650 30  0001 C CNN
F 1 "GND" H 7050 1580 30  0001 C CNN
F 2 "" H 7050 1650 60  0000 C CNN
F 3 "" H 7050 1650 60  0000 C CNN
	1    7050 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 532DDC5E
P 9100 6650
F 0 "#PWR05" H 9100 6650 30  0001 C CNN
F 1 "GND" H 9100 6580 30  0001 C CNN
F 2 "" H 9100 6650 60  0000 C CNN
F 3 "" H 9100 6650 60  0000 C CNN
	1    9100 6650
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 532DDC6A
P 9500 4600
F 0 "C6" H 9500 4700 40  0000 L CNN
F 1 "100nF" H 9506 4515 40  0000 L CNN
F 2 "~" H 9538 4450 30  0000 C CNN
F 3 "~" H 9500 4600 60  0000 C CNN
	1    9500 4600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 532DDCAA
P 10000 5000
F 0 "#PWR06" H 10000 5000 30  0001 C CNN
F 1 "GND" H 10000 4930 30  0001 C CNN
F 2 "" H 10000 5000 60  0000 C CNN
F 3 "" H 10000 5000 60  0000 C CNN
	1    10000 5000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 532DDCEC
P 9100 4300
F 0 "#PWR07" H 9100 4400 30  0001 C CNN
F 1 "VCC" H 9100 4400 30  0000 C CNN
F 2 "" H 9100 4300 60  0000 C CNN
F 3 "" H 9100 4300 60  0000 C CNN
	1    9100 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 532DDE77
P 9650 3500
F 0 "#PWR08" H 9650 3500 30  0001 C CNN
F 1 "GND" H 9650 3430 30  0001 C CNN
F 2 "" H 9650 3500 60  0000 C CNN
F 3 "" H 9650 3500 60  0000 C CNN
	1    9650 3500
	1    0    0    -1  
$EndComp
$Comp
L HYT271 U2
U 1 1 532DEF53
P 9100 5550
F 0 "U2" H 9300 6000 70  0000 C CNN
F 1 "HYT271" H 9100 5300 70  0000 C CNN
F 2 "~" H 9100 5550 60  0000 C CNN
F 3 "~" H 9100 5550 60  0000 C CNN
	1    9100 5550
	1    0    0    -1  
$EndComp
$Comp
L ATMEGA88-A IC1
U 1 1 533024BD
P 2500 2550
F 0 "IC1" H 1750 3800 40  0000 L BNN
F 1 "ATMEGA88-A" H 2950 1150 40  0000 L BNN
F 2 "TQFP32" H 2500 2550 30  0000 C CIN
F 3 "~" H 2500 2550 60  0000 C CNN
	1    2500 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5330251C
P 1400 4050
F 0 "#PWR09" H 1400 4050 30  0001 C CNN
F 1 "GND" H 1400 3980 30  0001 C CNN
F 2 "" H 1400 4050 60  0000 C CNN
F 3 "" H 1400 4050 60  0000 C CNN
	1    1400 4050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR010
U 1 1 53302620
P 1450 700
F 0 "#PWR010" H 1450 800 30  0001 C CNN
F 1 "VCC" H 1450 800 30  0000 C CNN
F 2 "" H 1450 700 60  0000 C CNN
F 3 "" H 1450 700 60  0000 C CNN
	1    1450 700 
	1    0    0    -1  
$EndComp
Text Label 3800 2700 0    60   ~ 0
SDA
Text Label 10350 5450 0    60   ~ 0
SDA
Text Label 10350 5650 0    60   ~ 0
SCL
Text Label 3800 2800 0    60   ~ 0
SCL
Text Label 4700 2950 0    60   ~ 0
DI
Text Label 3800 3650 0    60   ~ 0
DI
$Comp
L LED D1
U 1 1 53302A6A
P 1900 6500
F 0 "D1" H 1900 6600 50  0000 C CNN
F 1 "LED" H 1900 6400 50  0000 C CNN
F 2 "~" H 1900 6500 60  0000 C CNN
F 3 "~" H 1900 6500 60  0000 C CNN
	1    1900 6500
	-1   0    0    1   
$EndComp
$Comp
L CONN_5X2 P1
U 1 1 53302A79
P 2400 5350
F 0 "P1" H 2400 5650 60  0000 C CNN
F 1 "ISP" V 2400 5350 50  0000 C CNN
F 2 "~" H 2400 5350 60  0000 C CNN
F 3 "~" H 2400 5350 60  0000 C CNN
	1    2400 5350
	1    0    0    -1  
$EndComp
Text Label 3800 1750 0    60   ~ 0
MOSI
Text Label 3800 1850 0    60   ~ 0
MISO
Text Label 3800 1950 0    60   ~ 0
SCK
Text Label 3800 2900 0    60   ~ 0
RESET
Text Label 1650 5350 0    60   ~ 0
RESET
Text Label 1650 5450 0    60   ~ 0
SCK
Text Label 1650 5150 0    60   ~ 0
MOSI
Text Label 1650 5550 0    60   ~ 0
MISO
$Comp
L GND #PWR011
U 1 1 53302A98
P 3000 5800
F 0 "#PWR011" H 3000 5800 30  0001 C CNN
F 1 "GND" H 3000 5730 30  0001 C CNN
F 2 "" H 3000 5800 60  0000 C CNN
F 3 "" H 3000 5800 60  0000 C CNN
	1    3000 5800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR012
U 1 1 53302A9E
P 2950 4900
F 0 "#PWR012" H 2950 5000 30  0001 C CNN
F 1 "VCC" H 2950 5000 30  0000 C CNN
F 2 "" H 2950 4900 60  0000 C CNN
F 3 "" H 2950 4900 60  0000 C CNN
	1    2950 4900
	1    0    0    -1  
$EndComp
Text Label 3800 2300 0    60   ~ 0
LED1
Text Label 3800 2400 0    60   ~ 0
LED2
Text Label 1300 6500 0    60   ~ 0
LED1
$Comp
L LED D2
U 1 1 53302E6F
P 1900 6950
F 0 "D2" H 1900 7050 50  0000 C CNN
F 1 "LED" H 1900 6850 50  0000 C CNN
F 2 "~" H 1900 6950 60  0000 C CNN
F 3 "~" H 1900 6950 60  0000 C CNN
	1    1900 6950
	-1   0    0    1   
$EndComp
Text Label 1300 6950 0    60   ~ 0
LED2
$Comp
L VCC #PWR013
U 1 1 5330344D
P 3000 6200
F 0 "#PWR013" H 3000 6300 30  0001 C CNN
F 1 "VCC" H 3000 6300 30  0000 C CNN
F 2 "" H 3000 6200 60  0000 C CNN
F 3 "" H 3000 6200 60  0000 C CNN
	1    3000 6200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 53303458
P 2600 6500
F 0 "R1" V 2680 6500 40  0000 C CNN
F 1 "150" V 2607 6501 40  0000 C CNN
F 2 "~" V 2530 6500 30  0000 C CNN
F 3 "~" H 2600 6500 30  0000 C CNN
	1    2600 6500
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 5330345E
P 2600 6950
F 0 "R2" V 2680 6950 40  0000 C CNN
F 1 "150" V 2607 6951 40  0000 C CNN
F 2 "~" V 2530 6950 30  0000 C CNN
F 3 "~" H 2600 6950 30  0000 C CNN
	1    2600 6950
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR014
U 1 1 53303543
P 3000 6700
F 0 "#PWR014" H 3000 6800 30  0001 C CNN
F 1 "VCC" H 3000 6800 30  0000 C CNN
F 2 "" H 3000 6700 60  0000 C CNN
F 3 "" H 3000 6700 60  0000 C CNN
	1    3000 6700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR015
U 1 1 53493890
P 9650 2800
F 0 "#PWR015" H 9650 2900 30  0001 C CNN
F 1 "VCC" H 9650 2900 30  0000 C CNN
F 2 "" H 9650 2800 60  0000 C CNN
F 3 "" H 9650 2800 60  0000 C CNN
	1    9650 2800
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 534938E9
P 8250 3300
F 0 "C5" H 8250 3400 40  0000 L CNN
F 1 "100nF" H 8256 3215 40  0000 L CNN
F 2 "~" H 8288 3150 30  0000 C CNN
F 3 "~" H 8250 3300 60  0000 C CNN
	1    8250 3300
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR016
U 1 1 53493BBC
P 10550 3600
F 0 "#PWR016" H 10550 3600 30  0001 C CNN
F 1 "GND" H 10550 3530 30  0001 C CNN
F 2 "" H 10550 3600 60  0000 C CNN
F 3 "" H 10550 3600 60  0000 C CNN
	1    10550 3600
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 535D7B1E
P 7400 3000
F 0 "R4" V 7480 3000 40  0000 C CNN
F 1 "22k" V 7407 3001 40  0000 C CNN
F 2 "~" V 7330 3000 30  0000 C CNN
F 3 "~" H 7400 3000 30  0000 C CNN
	1    7400 3000
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 535D7B2D
P 7650 3000
F 0 "R5" V 7730 3000 40  0000 C CNN
F 1 "22k" V 7657 3001 40  0000 C CNN
F 2 "~" V 7580 3000 30  0000 C CNN
F 3 "~" H 7650 3000 30  0000 C CNN
	1    7650 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 535D7B6F
P 7650 3400
F 0 "#PWR017" H 7650 3400 30  0001 C CNN
F 1 "GND" H 7650 3330 30  0001 C CNN
F 2 "" H 7650 3400 60  0000 C CNN
F 3 "" H 7650 3400 60  0000 C CNN
	1    7650 3400
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 532DDDA3
P 10200 2900
F 0 "J1" H 10400 3400 60  0000 C CNN
F 1 "RJ45" H 10050 3400 60  0000 C CNN
F 2 "~" H 10200 2900 60  0000 C CNN
F 3 "~" H 10200 2900 60  0000 C CNN
	1    10200 2900
	0    1    1    0   
$EndComp
Text Label 8650 3550 0    60   ~ 0
za
Text Label 8650 2500 0    60   ~ 0
zb
Text Label 9650 2550 0    60   ~ 0
za
Text Label 9650 2650 0    60   ~ 0
zb
$Comp
L C C3
U 1 1 535FF4F4
P 6650 1150
F 0 "C3" H 6650 1250 40  0000 L CNN
F 1 "100nF" H 6656 1065 40  0000 L CNN
F 2 "~" H 6688 1000 30  0000 C CNN
F 3 "~" H 6650 1150 60  0000 C CNN
	1    6650 1150
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 535FF5D2
P 1050 1200
F 0 "C2" H 1050 1300 40  0000 L CNN
F 1 "10uF" H 1056 1115 40  0000 L CNN
F 2 "~" H 1088 1050 30  0000 C CNN
F 3 "~" H 1050 1200 60  0000 C CNN
	1    1050 1200
	0    -1   -1   0   
$EndComp
$Comp
L C C1
U 1 1 535FF5D8
P 1050 900
F 0 "C1" H 1050 1000 40  0000 L CNN
F 1 "100nF" H 1056 815 40  0000 L CNN
F 2 "~" H 1088 750 30  0000 C CNN
F 3 "~" H 1050 900 60  0000 C CNN
	1    1050 900 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR018
U 1 1 535FF6E8
P 850 1950
F 0 "#PWR018" H 850 1950 30  0001 C CNN
F 1 "GND" H 850 1880 30  0001 C CNN
F 2 "" H 850 1950 60  0000 C CNN
F 3 "" H 850 1950 60  0000 C CNN
	1    850  1950
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 535FFA0A
P 6700 5750
F 0 "R3" V 6780 5750 40  0000 C CNN
F 1 "10k" V 6707 5751 40  0000 C CNN
F 2 "~" V 6630 5750 30  0000 C CNN
F 3 "~" H 6700 5750 30  0000 C CNN
	1    6700 5750
	-1   0    0    1   
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 535FFA17
P 7200 6350
F 0 "SW1" H 7350 6460 50  0000 C CNN
F 1 "SW_RESET" H 7200 6270 50  0000 C CNN
F 2 "~" H 7200 6350 60  0000 C CNN
F 3 "~" H 7200 6350 60  0000 C CNN
	1    7200 6350
	1    0    0    -1  
$EndComp
Text Label 6000 6350 0    60   ~ 0
RESET
$Comp
L VCC #PWR019
U 1 1 535FFA29
P 6700 5100
F 0 "#PWR019" H 6700 5200 30  0001 C CNN
F 1 "VCC" H 6700 5200 30  0000 C CNN
F 2 "" H 6700 5100 60  0000 C CNN
F 3 "" H 6700 5100 60  0000 C CNN
	1    6700 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 535FFA2F
P 7800 6800
F 0 "#PWR020" H 7800 6800 30  0001 C CNN
F 1 "GND" H 7800 6730 30  0001 C CNN
F 2 "" H 7800 6800 60  0000 C CNN
F 3 "" H 7800 6800 60  0000 C CNN
	1    7800 6800
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P2
U 1 1 535FFDDB
P 4000 5350
F 0 "P2" V 3950 5350 50  0000 C CNN
F 1 "UART" V 4050 5350 50  0000 C CNN
F 2 "~" H 4000 5350 60  0000 C CNN
F 3 "~" H 4000 5350 60  0000 C CNN
	1    4000 5350
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR021
U 1 1 535FFDF2
P 4650 4850
F 0 "#PWR021" H 4650 4950 30  0001 C CNN
F 1 "VCC" H 4650 4950 30  0000 C CNN
F 2 "" H 4650 4850 60  0000 C CNN
F 3 "" H 4650 4850 60  0000 C CNN
	1    4650 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 535FFDF8
P 4650 5850
F 0 "#PWR022" H 4650 5850 30  0001 C CNN
F 1 "GND" H 4650 5780 30  0001 C CNN
F 2 "" H 4650 5850 60  0000 C CNN
F 3 "" H 4650 5850 60  0000 C CNN
	1    4650 5850
	1    0    0    -1  
$EndComp
Text Label 4650 5300 2    60   ~ 0
RX
Text Label 4650 5400 2    60   ~ 0
TX
Wire Wire Line
	7100 2500 8650 2500
Wire Wire Line
	7100 2800 7200 2800
Wire Wire Line
	7200 2800 7200 3550
Wire Wire Line
	6200 850  6200 1600
Wire Wire Line
	6200 3600 6200 4050
Wire Wire Line
	6200 1450 6450 1450
Connection ~ 6200 1450
Wire Wire Line
	6850 1450 7050 1450
Wire Wire Line
	7050 1150 7050 1650
Wire Wire Line
	9300 4600 9100 4600
Wire Wire Line
	9700 4600 10000 4600
Wire Wire Line
	10000 4600 10000 5000
Connection ~ 9100 4600
Wire Wire Line
	4900 1750 4900 2750
Wire Wire Line
	4900 2550 5300 2550
Wire Wire Line
	4900 2750 5300 2750
Connection ~ 4900 2550
Wire Wire Line
	9750 3250 9650 3250
Wire Wire Line
	9650 3150 9650 3500
Wire Wire Line
	9100 4300 9100 4700
Wire Wire Line
	9100 6650 9100 6400
Wire Wire Line
	1600 3550 1400 3550
Wire Wire Line
	1400 3550 1400 4050
Wire Wire Line
	1600 3650 1400 3650
Connection ~ 1400 3650
Wire Wire Line
	1600 3750 1400 3750
Connection ~ 1400 3750
Wire Wire Line
	1450 700  1450 1750
Wire Wire Line
	1450 1450 1600 1450
Wire Wire Line
	1450 1550 1600 1550
Connection ~ 1450 1450
Wire Wire Line
	1450 1750 1600 1750
Connection ~ 1450 1550
Wire Wire Line
	3800 2700 3500 2700
Wire Wire Line
	3800 2800 3500 2800
Wire Wire Line
	10350 5450 9750 5450
Wire Wire Line
	10350 5650 9750 5650
Wire Wire Line
	4700 2950 5300 2950
Wire Wire Line
	3800 3650 3500 3650
Wire Wire Line
	2950 4900 2950 5150
Wire Wire Line
	2950 5150 2800 5150
Wire Wire Line
	3000 5350 3000 5800
Wire Wire Line
	3000 5350 2800 5350
Wire Wire Line
	2800 5450 3000 5450
Connection ~ 3000 5450
Wire Wire Line
	2800 5550 3000 5550
Connection ~ 3000 5550
Wire Wire Line
	1650 5150 2000 5150
Wire Wire Line
	1650 5350 2000 5350
Wire Wire Line
	1650 5450 2000 5450
Wire Wire Line
	1650 5550 2000 5550
Wire Wire Line
	3800 2900 3500 2900
Wire Wire Line
	3800 1950 3500 1950
Wire Wire Line
	3800 1850 3500 1850
Wire Wire Line
	3800 1750 3500 1750
Wire Wire Line
	1700 6500 1300 6500
Wire Wire Line
	1300 6950 1700 6950
Wire Wire Line
	3800 2300 3500 2300
Wire Wire Line
	3800 2400 3500 2400
Wire Wire Line
	3000 6200 3000 6500
Wire Wire Line
	3000 6500 2850 6500
Wire Wire Line
	2350 6500 2100 6500
Wire Wire Line
	3000 6700 3000 6950
Wire Wire Line
	3000 6950 2850 6950
Wire Wire Line
	2350 6950 2100 6950
Wire Wire Line
	7200 3550 8650 3550
Wire Wire Line
	8250 3500 8250 3550
Connection ~ 8250 3550
Wire Wire Line
	8250 3000 8250 3100
Wire Wire Line
	10550 3450 10550 3600
Wire Wire Line
	7650 3250 7650 3400
Wire Wire Line
	7400 3250 7400 3550
Connection ~ 7400 3550
Wire Wire Line
	9650 2800 9650 2950
Wire Wire Line
	9650 2850 9750 2850
Wire Wire Line
	9650 2950 9750 2950
Connection ~ 9650 2850
Wire Wire Line
	9750 3150 9650 3150
Connection ~ 9650 3250
Wire Wire Line
	6850 1150 7050 1150
Connection ~ 7050 1450
Wire Wire Line
	6450 1150 6200 1150
Connection ~ 6200 1150
Wire Wire Line
	1250 900  1450 900 
Connection ~ 1450 900 
Wire Wire Line
	1250 1200 1450 1200
Connection ~ 1450 1200
Wire Wire Line
	850  900  850  1950
Connection ~ 850  1200
Wire Wire Line
	6700 5100 6700 5500
Wire Wire Line
	6700 6000 6700 6350
Wire Wire Line
	6000 6350 6900 6350
Wire Wire Line
	7500 6350 7800 6350
Wire Wire Line
	7800 6350 7800 6800
Connection ~ 6700 6350
Wire Wire Line
	4650 4850 4650 5200
Wire Wire Line
	4650 5200 4350 5200
Wire Wire Line
	4350 5300 4650 5300
Wire Wire Line
	4650 5400 4350 5400
Wire Wire Line
	4350 5500 4650 5500
Wire Wire Line
	4650 5500 4650 5850
Text Label 3800 3050 0    60   ~ 0
RX
Text Label 3800 3150 0    60   ~ 0
TX
Wire Wire Line
	3800 3050 3500 3050
Wire Wire Line
	3800 3150 3500 3150
$Comp
L VCC #PWR023
U 1 1 536003C2
P 7400 2650
F 0 "#PWR023" H 7400 2750 30  0001 C CNN
F 1 "VCC" H 7400 2750 30  0000 C CNN
F 2 "" H 7400 2650 60  0000 C CNN
F 3 "" H 7400 2650 60  0000 C CNN
	1    7400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2650 7400 2750
Wire Wire Line
	7650 2750 7650 2500
Connection ~ 7650 2500
Wire Wire Line
	9750 2550 9650 2550
Wire Wire Line
	9750 2650 9650 2650
$Comp
L ST485 U1
U 1 1 53600A20
P 6200 2650
F 0 "U1" H 6650 3250 70  0000 C BNN
F 1 "ST485" H 6600 2100 70  0000 C CNN
F 2 "~" H 6200 2550 60  0000 C CNN
F 3 "~" H 6200 2550 60  0000 C CNN
	1    6200 2650
	1    0    0    -1  
$EndComp
Connection ~ 8250 2500
$EndSCHEMATC
