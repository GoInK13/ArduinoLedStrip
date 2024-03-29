EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:modules
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
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
LIBS:wemos_mini
LIBS:Arduino_LedStrip-cache
EELAYER 25 0
EELAYER END
$Descr User 8268 5827
encoding utf-8
Sheet 1 1
Title "Arduino LED Strip"
Date "2017-11-08"
Rev "V1r0"
Comp "GoInK13"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino_Nano_v3.x A1
U 1 1 5A030002
P 1850 2150
F 0 "A1" H 1900 2150 50  0000 R CNN
F 1 "Arduino_Nano_v3.x" H 1650 3100 50  0000 R CNN
F 2 "Modules:Arduino_Nano" H 2000 1200 50  0001 L CNN
F 3 "" H 1850 1150 50  0001 C CNN
	1    1850 2150
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW2
U 1 1 5A036085
P 1650 4400
F 0 "SW2" H 1700 4500 50  0000 L CNN
F 1 "SW_Push" H 1650 4340 50  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_PUSH_6mm_h13mm" H 1650 4600 50  0001 C CNN
F 3 "" H 1650 4600 50  0001 C CNN
	1    1650 4400
	0    1    1    0   
$EndComp
$Comp
L POT RV1
U 1 1 5A036106
P 750 5000
F 0 "RV1" V 575 5000 50  0000 C CNN
F 1 "PTV09A" V 650 5000 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Bourns_PTV09A-1_Horizontal" H 750 5000 50  0001 C CNN
F 3 "" H 750 5000 50  0001 C CNN
	1    750  5000
	-1   0    0    1   
$EndComp
$Comp
L SW_Push SW1
U 1 1 5A037113
P 1100 4450
F 0 "SW1" H 1150 4550 50  0000 L CNN
F 1 "SW_Push" H 1100 4390 50  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_PUSH_6mm_h13mm" H 1100 4650 50  0001 C CNN
F 3 "" H 1100 4650 50  0001 C CNN
	1    1100 4450
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 5A037190
P 1250 4850
F 0 "R7" V 1330 4850 50  0000 C CNN
F 1 "1k" V 1250 4850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1180 4850 50  0001 C CNN
F 3 "" H 1250 4850 50  0001 C CNN
	1    1250 4850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR01
U 1 1 5A037C46
P 2900 4650
F 0 "#PWR01" H 2900 4400 50  0001 C CNN
F 1 "GND" H 2900 4500 50  0000 C CNN
F 2 "" H 2900 4650 50  0001 C CNN
F 3 "" H 2900 4650 50  0001 C CNN
	1    2900 4650
	1    0    0    -1  
$EndComp
$Comp
L Barrel_Jack J6
U 1 1 5A037C66
P 2400 4600
F 0 "J6" H 2400 4810 50  0000 C CNN
F 1 "Barrel_Jack" H 2400 4425 50  0000 C CNN
F 2 "Connect:BARREL_JACK" H 2450 4560 50  0001 C CNN
F 3 "" H 2450 4560 50  0001 C CNN
	1    2400 4600
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5A039E73
P 1850 4850
F 0 "R8" V 1930 4850 50  0000 C CNN
F 1 "1k" V 1850 4850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1780 4850 50  0001 C CNN
F 3 "" H 1850 4850 50  0001 C CNN
	1    1850 4850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 5A03A6BE
P 2000 4850
F 0 "#PWR02" H 2000 4600 50  0001 C CNN
F 1 "GND" H 2000 4700 50  0000 C CNN
F 2 "" H 2000 4850 50  0001 C CNN
F 3 "" H 2000 4850 50  0001 C CNN
	1    2000 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5A03A833
P 1400 4850
F 0 "#PWR03" H 1400 4600 50  0001 C CNN
F 1 "GND" H 1400 4700 50  0000 C CNN
F 2 "" H 1400 4850 50  0001 C CNN
F 3 "" H 1400 4850 50  0001 C CNN
	1    1400 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5A03AAF0
P 750 5150
F 0 "#PWR04" H 750 4900 50  0001 C CNN
F 1 "GND" H 750 5000 50  0000 C CNN
F 2 "" H 750 5150 50  0001 C CNN
F 3 "" H 750 5150 50  0001 C CNN
	1    750  5150
	1    0    0    -1  
$EndComp
Text Label 1350 2750 2    60   ~ 0
ar_IR
Text Notes 1200 750  0    60   ~ 0
PWM : D3,D5,D6,D9,D10,D11
Text Label 1350 1950 2    60   ~ 0
ar_Din_LEDWS
$Comp
L GND #PWR05
U 1 1 5A0E71A2
P 1900 3200
F 0 "#PWR05" H 1900 2950 50  0001 C CNN
F 1 "GND" H 1900 3050 50  0000 C CNN
F 2 "" H 1900 3200 50  0001 C CNN
F 3 "" H 1900 3200 50  0001 C CNN
	1    1900 3200
	1    0    0    -1  
$EndComp
Text Label 2350 2150 0    60   ~ 0
ar_A0_Pot
Text Label 2350 1550 0    60   ~ 0
ar_Reset1
Text Label 2350 1650 0    60   ~ 0
ar_Reset2
Text Label 1350 2450 2    60   ~ 0
ar_LED0_R
Text Label 1350 2150 2    60   ~ 0
ar_LED0_B
Text Label 1350 2550 2    60   ~ 0
ar_LED0_G
$Comp
L Q_NMOS_GDS Q3
U 1 1 5A0EAFAA
P 7050 950
F 0 "Q3" H 7250 1000 50  0000 L CNN
F 1 "IRFZ44N" H 7250 900 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 7250 1050 50  0001 C CNN
F 3 "" H 7050 950 50  0001 C CNN
	1    7050 950 
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5A0EBAAD
P 6700 950
F 0 "R3" V 6780 950 50  0000 C CNN
F 1 "1k" V 6700 950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6630 950 50  0001 C CNN
F 3 "" H 6700 950 50  0001 C CNN
	1    6700 950 
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 5A0EC08C
P 7150 1150
F 0 "#PWR06" H 7150 900 50  0001 C CNN
F 1 "GND" H 7150 1000 50  0000 C CNN
F 2 "" H 7150 1150 50  0001 C CNN
F 3 "" H 7150 1150 50  0001 C CNN
	1    7150 1150
	1    0    0    -1  
$EndComp
Text Label 7150 750  0    60   ~ 0
LED0_G
Text Label 1350 2850 2    60   ~ 0
ar_LED_BuiltIn
Text Label 6550 950  2    60   ~ 0
ar_LED0_G
$Comp
L Q_NMOS_GDS Q2
U 1 1 5A0EE48C
P 5750 950
F 0 "Q2" H 5950 1000 50  0000 L CNN
F 1 "IRFZ44N" H 5950 900 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 5950 1050 50  0001 C CNN
F 3 "" H 5750 950 50  0001 C CNN
	1    5750 950 
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A0EE492
P 5400 950
F 0 "R2" V 5480 950 50  0000 C CNN
F 1 "1k" V 5400 950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5330 950 50  0001 C CNN
F 3 "" H 5400 950 50  0001 C CNN
	1    5400 950 
	0    1    1    0   
$EndComp
$Comp
L GND #PWR07
U 1 1 5A0EE498
P 5850 1150
F 0 "#PWR07" H 5850 900 50  0001 C CNN
F 1 "GND" H 5850 1000 50  0000 C CNN
F 2 "" H 5850 1150 50  0001 C CNN
F 3 "" H 5850 1150 50  0001 C CNN
	1    5850 1150
	1    0    0    -1  
$EndComp
Text Label 5850 750  0    60   ~ 0
LED0_B
Text Label 5250 950  2    60   ~ 0
ar_LED0_B
$Comp
L Q_NMOS_GDS Q1
U 1 1 5A0EE809
P 4450 950
F 0 "Q1" H 4650 1000 50  0000 L CNN
F 1 "IRFZ44N" H 4650 900 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 4650 1050 50  0001 C CNN
F 3 "" H 4450 950 50  0001 C CNN
	1    4450 950 
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A0EE80F
P 4100 950
F 0 "R1" V 4180 950 50  0000 C CNN
F 1 "1k" V 4100 950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4030 950 50  0001 C CNN
F 3 "" H 4100 950 50  0001 C CNN
	1    4100 950 
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5A0EE815
P 4550 1150
F 0 "#PWR08" H 4550 900 50  0001 C CNN
F 1 "GND" H 4550 1000 50  0000 C CNN
F 2 "" H 4550 1150 50  0001 C CNN
F 3 "" H 4550 1150 50  0001 C CNN
	1    4550 1150
	1    0    0    -1  
$EndComp
Text Label 4550 750  0    60   ~ 0
LED0_R
Text Label 3950 950  2    60   ~ 0
ar_LED0_R
Text Label 1350 2050 2    60   ~ 0
ar_LED1_R
Text Label 1350 2650 2    60   ~ 0
ar_LED1_B
Text Label 1350 1850 2    60   ~ 0
ar_LED1_G
Text Label 1350 2250 2    60   ~ 0
ar_D7
Text Label 1350 2350 2    60   ~ 0
ar_D8
Text Label 1350 1750 2    60   ~ 0
ar_D2
Text Label 1350 1650 2    60   ~ 0
ar_D1_TX
Text Label 1350 1550 2    60   ~ 0
ar_D0_RX
Text Label 2350 2250 0    60   ~ 0
ar_A1_D15
Text Label 2350 2350 0    60   ~ 0
ar_A2_D16
Text Label 2350 2450 0    60   ~ 0
ar_A3_D17
Text Label 2350 2550 0    60   ~ 0
ar_A4_D18
Text Label 2350 2650 0    60   ~ 0
ar_A5_D19
Text Label 2350 2750 0    60   ~ 0
ar_A6
Text Label 2350 2850 0    60   ~ 0
ar_A7
$Comp
L Q_NMOS_GDS Q6
U 1 1 5A0F1E43
P 7050 1700
F 0 "Q6" H 7250 1750 50  0000 L CNN
F 1 "IRFZ44N" H 7250 1650 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 7250 1800 50  0001 C CNN
F 3 "" H 7050 1700 50  0001 C CNN
	1    7050 1700
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5A0F1E49
P 6700 1700
F 0 "R6" V 6780 1700 50  0000 C CNN
F 1 "1k" V 6700 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6630 1700 50  0001 C CNN
F 3 "" H 6700 1700 50  0001 C CNN
	1    6700 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 5A0F1E4F
P 7150 1900
F 0 "#PWR09" H 7150 1650 50  0001 C CNN
F 1 "GND" H 7150 1750 50  0000 C CNN
F 2 "" H 7150 1900 50  0001 C CNN
F 3 "" H 7150 1900 50  0001 C CNN
	1    7150 1900
	1    0    0    -1  
$EndComp
Text Label 7150 1500 0    60   ~ 0
LED1_G
Text Label 6550 1700 2    60   ~ 0
ar_LED1_G
$Comp
L Q_NMOS_GDS Q5
U 1 1 5A0F1E57
P 5750 1700
F 0 "Q5" H 5950 1750 50  0000 L CNN
F 1 "IRFZ44N" H 5950 1650 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 5950 1800 50  0001 C CNN
F 3 "" H 5750 1700 50  0001 C CNN
	1    5750 1700
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5A0F1E5D
P 5400 1700
F 0 "R5" V 5480 1700 50  0000 C CNN
F 1 "1k" V 5400 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5330 1700 50  0001 C CNN
F 3 "" H 5400 1700 50  0001 C CNN
	1    5400 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 5A0F1E63
P 5850 1900
F 0 "#PWR010" H 5850 1650 50  0001 C CNN
F 1 "GND" H 5850 1750 50  0000 C CNN
F 2 "" H 5850 1900 50  0001 C CNN
F 3 "" H 5850 1900 50  0001 C CNN
	1    5850 1900
	1    0    0    -1  
$EndComp
Text Label 5850 1500 0    60   ~ 0
LED1_B
Text Label 5250 1700 2    60   ~ 0
ar_LED1_B
$Comp
L Q_NMOS_GDS Q4
U 1 1 5A0F1E6B
P 4450 1700
F 0 "Q4" H 4650 1750 50  0000 L CNN
F 1 "IRFZ44N" H 4650 1650 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 4650 1800 50  0001 C CNN
F 3 "" H 4450 1700 50  0001 C CNN
	1    4450 1700
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5A0F1E71
P 4100 1700
F 0 "R4" V 4180 1700 50  0000 C CNN
F 1 "1k" V 4100 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4030 1700 50  0001 C CNN
F 3 "" H 4100 1700 50  0001 C CNN
	1    4100 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 5A0F1E77
P 4550 1900
F 0 "#PWR011" H 4550 1650 50  0001 C CNN
F 1 "GND" H 4550 1750 50  0000 C CNN
F 2 "" H 4550 1900 50  0001 C CNN
F 3 "" H 4550 1900 50  0001 C CNN
	1    4550 1900
	1    0    0    -1  
$EndComp
Text Label 4550 1500 0    60   ~ 0
LED1_R
Text Label 3950 1700 2    60   ~ 0
ar_LED1_R
$Comp
L TSOP45xx U1
U 1 1 5A0F5783
P 7000 3750
F 0 "U1" H 6600 4050 50  0000 L CNN
F 1 "TSOP4838" H 6600 3450 50  0000 L CNN
F 2 "Opto-Devices:IRReceiver_Vishay_MOLD-3pin" H 6950 3375 50  0001 C CNN
F 3 "" H 7650 4050 50  0001 C CNN
	1    7000 3750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR012
U 1 1 5A0F658B
P 2050 1150
F 0 "#PWR012" H 2050 1000 50  0001 C CNN
F 1 "+5V" H 2050 1290 50  0000 C CNN
F 2 "" H 2050 1150 50  0001 C CNN
F 3 "" H 2050 1150 50  0001 C CNN
	1    2050 1150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 5A0F66C5
P 7400 3550
F 0 "#PWR013" H 7400 3400 50  0001 C CNN
F 1 "+5V" H 7400 3690 50  0000 C CNN
F 2 "" H 7400 3550 50  0001 C CNN
F 3 "" H 7400 3550 50  0001 C CNN
	1    7400 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5A0F6914
P 7400 3950
F 0 "#PWR014" H 7400 3700 50  0001 C CNN
F 1 "GND" H 7400 3800 50  0000 C CNN
F 2 "" H 7400 3950 50  0001 C CNN
F 3 "" H 7400 3950 50  0001 C CNN
	1    7400 3950
	0    -1   -1   0   
$EndComp
Text Label 7400 3750 0    60   ~ 0
ar_IR
$Comp
L Conn_01x04_Male J3
U 1 1 5A0F808E
P 7050 2750
F 0 "J3" H 7050 2950 50  0000 C CNN
F 1 "LED0" H 7050 2450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 7050 2750 50  0001 C CNN
F 3 "" H 7050 2750 50  0001 C CNN
	1    7050 2750
	-1   0    0    -1  
$EndComp
Text Label 6850 2850 2    60   ~ 0
LED0_R
Text Label 6850 2750 2    60   ~ 0
LED0_B
Text Label 6850 2950 2    60   ~ 0
LED0_G
$Comp
L Conn_01x04_Male J4
U 1 1 5A0FAFA3
P 7650 2750
F 0 "J4" H 7650 2950 50  0000 C CNN
F 1 "LED1" H 7650 2450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 7650 2750 50  0001 C CNN
F 3 "" H 7650 2750 50  0001 C CNN
	1    7650 2750
	-1   0    0    -1  
$EndComp
Text Label 7450 2850 2    60   ~ 0
LED1_R
Text Label 7450 2750 2    60   ~ 0
LED1_B
Text Label 7450 2950 2    60   ~ 0
LED1_G
Text Label 3850 2650 2    60   ~ 0
ar_IR
Text Label 3850 3050 2    60   ~ 0
ar_Din_LEDWS
Text Label 4850 2950 0    60   ~ 0
ar_LED0_R
Text Label 3850 2850 2    60   ~ 0
ar_LED0_B
Text Label 4850 3050 0    60   ~ 0
ar_LED0_G
Text Label 3850 2950 2    60   ~ 0
ar_LED1_R
Text Label 3850 2750 2    60   ~ 0
ar_LED1_B
Text Label 3850 3150 2    60   ~ 0
ar_LED1_G
$Comp
L GND #PWR015
U 1 1 5A10079A
P 3700 2550
F 0 "#PWR015" H 3700 2300 50  0001 C CNN
F 1 "GND" H 3700 2400 50  0000 C CNN
F 2 "" H 3700 2550 50  0001 C CNN
F 3 "" H 3700 2550 50  0001 C CNN
	1    3700 2550
	-1   0    0    1   
$EndComp
Text Label 4850 2550 0    60   ~ 0
ar_A0_Pot
Text Label 4850 2650 0    60   ~ 0
ar_A1_D15
Text Label 4850 2750 0    60   ~ 0
ar_A2_D16
Text Label 600  5000 1    60   ~ 0
ar_A0_Pot
Text Label 1650 4850 3    51   ~ 0
ar_A2_D16
$Comp
L Conn_01x03_Male J5
U 1 1 5A10D375
P 6350 2800
F 0 "J5" H 6350 3000 50  0000 C CNN
F 1 "LED_WS2812B" H 6350 2600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x03_Pitch2.54mm" H 6350 2800 50  0001 C CNN
F 3 "" H 6350 2800 50  0001 C CNN
	1    6350 2800
	-1   0    0    1   
$EndComp
Text Label 6150 2800 2    60   ~ 0
ar_Din_LEDWS
$Comp
L GND #PWR016
U 1 1 5A10F5EE
P 5950 2900
F 0 "#PWR016" H 5950 2650 50  0001 C CNN
F 1 "GND" H 5950 2750 50  0000 C CNN
F 2 "" H 5950 2900 50  0001 C CNN
F 3 "" H 5950 2900 50  0001 C CNN
	1    5950 2900
	1    0    0    -1  
$EndComp
Text Notes 2300 4300 0    118  ~ 24
Power
Text Notes 500  4300 0    118  ~ 24
Inputs
Text Notes 1500 650  0    118  ~ 24
Arduino
Text Notes 4850 650  0    118  ~ 24
LED Supply
Wire Notes Line
	3150 2150 7800 2150
Wire Notes Line
	3150 500  3150 4100
Wire Notes Line
	2100 4100 2100 5350
Wire Notes Line
	450  4100 3550 4100
Wire Wire Line
	2700 4500 2900 4500
Wire Wire Line
	6150 2900 5950 2900
Wire Wire Line
	6150 2700 5950 2700
Wire Wire Line
	1650 4850 1650 4800
Wire Wire Line
	1700 4850 1650 4850
Wire Wire Line
	3700 2550 3850 2550
Connection ~ 1900 3200
Wire Wire Line
	1950 3200 1950 3150
Wire Wire Line
	1850 3200 1950 3200
Wire Wire Line
	1850 3150 1850 3200
Connection ~ 2750 4650
Wire Wire Line
	2750 4700 2700 4700
Wire Wire Line
	2750 4600 2700 4600
Wire Wire Line
	2750 4600 2750 4700
Wire Wire Line
	2900 4650 2750 4650
Text Notes 6050 2350 0    118  ~ 24
Connectors
Text Notes 6600 3350 0    98   ~ 20
Infrared Sensor
$Comp
L CP C1
U 1 1 5A116536
P 750 3700
F 0 "C1" H 775 3800 50  0000 L CNN
F 1 "10u" H 775 3600 50  0000 L CNN
F 2 "Capacitors_ThroughHole:CP_Radial_D8.0mm_P3.50mm" H 788 3550 50  0001 C CNN
F 3 "" H 750 3700 50  0001 C CNN
	1    750  3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5A1165FC
P 750 3850
F 0 "#PWR017" H 750 3600 50  0001 C CNN
F 1 "GND" H 750 3700 50  0000 C CNN
F 2 "" H 750 3850 50  0001 C CNN
F 3 "" H 750 3850 50  0001 C CNN
	1    750  3850
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG018
U 1 1 5A117857
P 3300 5150
F 0 "#FLG018" H 3300 5225 50  0001 C CNN
F 1 "PWR_FLAG" H 3300 5300 50  0000 C CNN
F 2 "" H 3300 5150 50  0001 C CNN
F 3 "" H 3300 5150 50  0001 C CNN
	1    3300 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5A1178B7
P 3300 5150
F 0 "#PWR019" H 3300 4900 50  0001 C CNN
F 1 "GND" H 3300 5000 50  0000 C CNN
F 2 "" H 3300 5150 50  0001 C CNN
F 3 "" H 3300 5150 50  0001 C CNN
	1    3300 5150
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR020
U 1 1 5A118832
P 3300 4750
F 0 "#PWR020" H 3300 4600 50  0001 C CNN
F 1 "+12V" H 3300 4890 50  0000 C CNN
F 2 "" H 3300 4750 50  0001 C CNN
F 3 "" H 3300 4750 50  0001 C CNN
	1    3300 4750
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG021
U 1 1 5A11888B
P 3300 4750
F 0 "#FLG021" H 3300 4825 50  0001 C CNN
F 1 "PWR_FLAG" H 3300 4900 50  0000 C CNN
F 2 "" H 3300 4750 50  0001 C CNN
F 3 "" H 3300 4750 50  0001 C CNN
	1    3300 4750
	-1   0    0    1   
$EndComp
$Comp
L Screw_Terminal_01x01 J9
U 1 1 5A11E95E
P 1800 3900
F 0 "J9" H 1800 4000 50  0000 C CNN
F 1 "Screw_Terminal_01x01" H 1800 3800 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 1800 3900 50  0001 C CNN
F 3 "" H 1800 3900 50  0001 C CNN
	1    1800 3900
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x01 J7
U 1 1 5A11EA74
P 1800 3650
F 0 "J7" H 1800 3750 50  0000 C CNN
F 1 "Screw_Terminal_01x01" H 1800 3550 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 1800 3650 50  0001 C CNN
F 3 "" H 1800 3650 50  0001 C CNN
	1    1800 3650
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x01 J8
U 1 1 5A11EE66
P 2650 3650
F 0 "J8" H 2650 3750 50  0000 C CNN
F 1 "Screw_Terminal_01x01" H 2650 3550 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 2650 3650 50  0001 C CNN
F 3 "" H 2650 3650 50  0001 C CNN
	1    2650 3650
	1    0    0    -1  
$EndComp
NoConn ~ 1600 3650
NoConn ~ 2450 3650
NoConn ~ 1600 3900
$Comp
L R_Small R10
U 1 1 5A5A585B
P 5950 3600
F 0 "R10" V 5850 3550 50  0000 L CNN
F 1 "0" H 5926 3600 50  0000 L CNN
F 2 "Battery_pads:R_Shunt" H 5950 3600 50  0001 C CNN
F 3 "" H 5950 3600 50  0001 C CNN
F 4 "Shunt if Vin=12V" V 6050 3600 39  0000 C CNN "Info"
	1    5950 3600
	0    1    1    0   
$EndComp
$Comp
L R_Small R11
U 1 1 5A5A6B65
P 5950 3950
F 0 "R11" V 6050 3850 50  0000 L CNN
F 1 "0" H 5926 3950 50  0000 L CNN
F 2 "Battery_pads:R_Shunt" H 5950 3950 50  0001 C CNN
F 3 "" H 5950 3950 50  0001 C CNN
F 4 "Shunt if Vin=5V" V 5850 3950 39  0000 C CNN "Info"
	1    5950 3950
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR022
U 1 1 5A5A73E7
P 6150 3950
F 0 "#PWR022" H 6150 3800 50  0001 C CNN
F 1 "+5V" H 6150 4090 50  0000 C CNN
F 2 "" H 6150 3950 50  0001 C CNN
F 3 "" H 6150 3950 50  0001 C CNN
	1    6150 3950
	1    0    0    -1  
$EndComp
Text Notes 5600 2500 0    35   ~ 0
/!\ The real voltage is 5V
$Comp
L WeMos_mini U3
U 1 1 5A5C5976
P 4350 2800
F 0 "U3" H 4350 3300 60  0000 C CNN
F 1 "WeMos_mini" H 4350 2300 60  0000 C CNN
F 2 "GoInK13:D1_mini_board" H 4900 2100 60  0001 C CNN
F 3 "" H 4900 2100 60  0000 C CNN
	1    4350 2800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR023
U 1 1 5A5C6D41
P 3850 2450
F 0 "#PWR023" H 3850 2300 50  0001 C CNN
F 1 "+5V" H 3850 2590 50  0000 C CNN
F 2 "" H 3850 2450 50  0001 C CNN
F 3 "" H 3850 2450 50  0001 C CNN
	1    3850 2450
	1    0    0    -1  
$EndComp
$Comp
L L7805 U2
U 1 1 5A5C6E35
P 4350 3600
F 0 "U2" H 4200 3725 50  0000 C CNN
F 1 "L7805" H 4350 3725 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 4375 3450 50  0001 L CIN
F 3 "" H 4350 3550 50  0001 C CNN
	1    4350 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3600 4050 3600
$Comp
L GND #PWR024
U 1 1 5A5C7F22
P 4350 3900
F 0 "#PWR024" H 4350 3650 50  0001 C CNN
F 1 "GND" H 4350 3750 50  0000 C CNN
F 2 "" H 4350 3900 50  0001 C CNN
F 3 "" H 4350 3900 50  0001 C CNN
	1    4350 3900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR025
U 1 1 5A5C81B3
P 4700 3600
F 0 "#PWR025" H 4700 3450 50  0001 C CNN
F 1 "+5V" H 4700 3740 50  0000 C CNN
F 2 "" H 4700 3600 50  0001 C CNN
F 3 "" H 4700 3600 50  0001 C CNN
	1    4700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3600 4650 3600
NoConn ~ 4850 3150
Text Label 4850 2850 0    60   ~ 0
ar_A3_D17
$Comp
L VCC #PWR026
U 1 1 5A5D552B
P 2900 4500
F 0 "#PWR026" H 2900 4350 50  0001 C CNN
F 1 "VCC" H 2900 4650 50  0000 C CNN
F 2 "" H 2900 4500 50  0001 C CNN
F 3 "" H 2900 4500 50  0001 C CNN
	1    2900 4500
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR027
U 1 1 5A5D6ED1
P 5750 3950
F 0 "#PWR027" H 5750 3800 50  0001 C CNN
F 1 "VCC" H 5750 4100 50  0000 C CNN
F 2 "" H 5750 3950 50  0001 C CNN
F 3 "" H 5750 3950 50  0001 C CNN
	1    5750 3950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR028
U 1 1 5A5D739C
P 3300 4350
F 0 "#PWR028" H 3300 4200 50  0001 C CNN
F 1 "VCC" H 3300 4500 50  0000 C CNN
F 2 "" H 3300 4350 50  0001 C CNN
F 3 "" H 3300 4350 50  0001 C CNN
	1    3300 4350
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG029
U 1 1 5A5D7404
P 3300 4350
F 0 "#FLG029" H 3300 4425 50  0001 C CNN
F 1 "PWR_FLAG" H 3300 4500 50  0000 C CNN
F 2 "" H 3300 4350 50  0001 C CNN
F 3 "" H 3300 4350 50  0001 C CNN
	1    3300 4350
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR030
U 1 1 5A5D978C
P 5750 3600
F 0 "#PWR030" H 5750 3450 50  0001 C CNN
F 1 "VCC" H 5750 3750 50  0000 C CNN
F 2 "" H 5750 3600 50  0001 C CNN
F 3 "" H 5750 3600 50  0001 C CNN
	1    5750 3600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR031
U 1 1 5A5DB279
P 7450 2650
F 0 "#PWR031" H 7450 2500 50  0001 C CNN
F 1 "VCC" H 7450 2800 50  0000 C CNN
F 2 "" H 7450 2650 50  0001 C CNN
F 3 "" H 7450 2650 50  0001 C CNN
	1    7450 2650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR032
U 1 1 5A5DB9ED
P 6850 2650
F 0 "#PWR032" H 6850 2500 50  0001 C CNN
F 1 "VCC" H 6850 2800 50  0000 C CNN
F 2 "" H 6850 2650 50  0001 C CNN
F 3 "" H 6850 2650 50  0001 C CNN
	1    6850 2650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR033
U 1 1 5A5DBA55
P 5950 2700
F 0 "#PWR033" H 5950 2550 50  0001 C CNN
F 1 "VCC" H 5950 2850 50  0000 C CNN
F 2 "" H 5950 2700 50  0001 C CNN
F 3 "" H 5950 2700 50  0001 C CNN
	1    5950 2700
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR034
U 1 1 5A5DD1D9
P 4050 3600
F 0 "#PWR034" H 4050 3450 50  0001 C CNN
F 1 "+12V" H 4050 3740 50  0000 C CNN
F 2 "" H 4050 3600 50  0001 C CNN
F 3 "" H 4050 3600 50  0001 C CNN
	1    4050 3600
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR035
U 1 1 5A5DD719
P 1750 1150
F 0 "#PWR035" H 1750 1000 50  0001 C CNN
F 1 "+12V" H 1750 1290 50  0000 C CNN
F 2 "" H 1750 1150 50  0001 C CNN
F 3 "" H 1750 1150 50  0001 C CNN
	1    1750 1150
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR036
U 1 1 5A5DE8A0
P 750 3550
F 0 "#PWR036" H 750 3400 50  0001 C CNN
F 1 "VCC" H 750 3700 50  0000 C CNN
F 2 "" H 750 3550 50  0001 C CNN
F 3 "" H 750 3550 50  0001 C CNN
	1    750  3550
	1    0    0    -1  
$EndComp
Wire Notes Line
	5400 2150 5400 4100
Wire Notes Line
	7800 3150 5400 3150
Text Notes 3200 3900 0    118  ~ 24
Wemos
Text Notes 3200 4050 0    79   ~ 16
+LDO 12V→5V
$Comp
L +12V #PWR037
U 1 1 5A5E7881
P 6150 3600
F 0 "#PWR037" H 6150 3450 50  0001 C CNN
F 1 "+12V" H 6150 3740 50  0000 C CNN
F 2 "" H 6150 3600 50  0001 C CNN
F 3 "" H 6150 3600 50  0001 C CNN
	1    6150 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3600 5850 3600
Wire Wire Line
	6050 3600 6150 3600
Wire Wire Line
	6150 3950 6050 3950
Wire Wire Line
	5850 3950 5750 3950
Wire Notes Line
	6450 3150 6450 4100
Text Notes 5650 3350 0    118  ~ 24
Shunts
$Comp
L +3V3 #PWR038
U 1 1 5A5EFC15
P 1950 1050
F 0 "#PWR038" H 1950 900 50  0001 C CNN
F 1 "+3V3" H 1950 1190 50  0000 C CNN
F 2 "" H 1950 1050 50  0001 C CNN
F 3 "" H 1950 1050 50  0001 C CNN
	1    1950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1050 1950 1150
$Comp
L +3V3 #PWR039
U 1 1 5A5F001C
P 4850 2450
F 0 "#PWR039" H 4850 2300 50  0001 C CNN
F 1 "+3V3" H 4850 2590 50  0000 C CNN
F 2 "" H 4850 2450 50  0001 C CNN
F 3 "" H 4850 2450 50  0001 C CNN
	1    4850 2450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR040
U 1 1 5A5F2A9B
P 1650 4200
F 0 "#PWR040" H 1650 4050 50  0001 C CNN
F 1 "+5V" H 1650 4340 50  0000 C CNN
F 2 "" H 1650 4200 50  0001 C CNN
F 3 "" H 1650 4200 50  0001 C CNN
	1    1650 4200
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR041
U 1 1 5A5F31B4
P 1100 4200
F 0 "#PWR041" H 1100 4050 50  0001 C CNN
F 1 "+5V" H 1100 4340 50  0000 C CNN
F 2 "" H 1100 4200 50  0001 C CNN
F 3 "" H 1100 4200 50  0001 C CNN
	1    1100 4200
	0    1    1    0   
$EndComp
$Comp
L +3V3 #PWR042
U 1 1 5A5F4A46
P 2450 1950
F 0 "#PWR042" H 2450 1800 50  0001 C CNN
F 1 "+3V3" H 2450 2090 50  0000 C CNN
F 2 "" H 2450 1950 50  0001 C CNN
F 3 "" H 2450 1950 50  0001 C CNN
	1    2450 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1950 2350 1950
Text Notes 1000 5350 0    31   ~ 0
/!\ Connect 500Ω to 1kΩ if wemos, else 0
$Comp
L R_Small R9
U 1 1 5A5FA1D0
P 1100 4750
F 0 "R9" V 1000 4700 50  0000 L CNN
F 1 "1kor0" V 1100 4700 24  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 1100 4750 50  0001 C CNN
F 3 "" H 1100 4750 50  0001 C CNN
	1    1100 4750
	-1   0    0    1   
$EndComp
$Comp
L R_Small R12
U 1 1 5A5FACB7
P 1650 4700
F 0 "R12" V 1550 4650 50  0000 L CNN
F 1 "1kor0" V 1650 4650 24  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 1650 4700 50  0001 C CNN
F 3 "" H 1650 4700 50  0001 C CNN
	1    1650 4700
	-1   0    0    1   
$EndComp
Text Label 1100 4850 3    51   ~ 0
ar_A1_D15
Wire Wire Line
	1100 4200 1100 4250
$Comp
L +3V3 #PWR043
U 1 1 5A5FD175
P 750 4850
F 0 "#PWR043" H 750 4700 50  0001 C CNN
F 1 "+3V3" H 750 4990 50  0000 C CNN
F 2 "" H 750 4850 50  0001 C CNN
F 3 "" H 750 4850 50  0001 C CNN
	1    750  4850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
