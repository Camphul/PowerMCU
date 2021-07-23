EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 9
Title "RGB Momentary switch"
Date "2021-07-22"
Rev "1"
Comp "Logic Shift"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1300 2100 2    50   Output ~ 0
LED_G
Text HLabel 1300 2200 2    50   Output ~ 0
LED_B
Text HLabel 1150 1200 2    50   Output ~ 0
BUTTON_NC
Text HLabel 1600 1100 2    50   Output ~ 0
BUTTON_NO
$Comp
L Connector:Conn_01x03_Female J6
U 1 1 60ECD1C9
P 950 1200
F 0 "J6" H 842 875 50  0000 C CNN
F 1 "BTN_CONNECTOR" H 842 966 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B3B-XH-A_1x03_P2.50mm_Vertical" H 950 1200 50  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/eXH.pdf" H 950 1200 50  0001 C CNN
	1    950  1200
	-1   0    0    1   
$EndComp
Text Notes 750  2750 0    50   ~ 0
RGB Leds schakelen op ground
$Comp
L Connector:Conn_01x05_Female J7
U 1 1 60EC404A
P 1000 2100
F 0 "J7" V 1150 2100 50  0000 C CNN
F 1 "RGB_LED_CONNECTOR" V 1050 1850 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x05_P2.50mm_Vertical" H 1000 2100 50  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/eXH.pdf" H 1000 2100 50  0001 C CNN
	1    1000 2100
	-1   0    0    1   
$EndComp
Text HLabel 1300 2000 2    50   Output ~ 0
LED_R
$Comp
L power:+BATT #PWR015
U 1 1 61051377
P 1150 1300
F 0 "#PWR015" H 1150 1150 50  0001 C CNN
F 1 "+BATT" V 1165 1428 50  0000 L CNN
F 2 "" H 1150 1300 50  0001 C CNN
F 3 "" H 1150 1300 50  0001 C CNN
	1    1150 1300
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR016
U 1 1 61051BE7
P 1200 2300
F 0 "#PWR016" H 1200 2150 50  0001 C CNN
F 1 "+3.3V" V 1215 2428 50  0000 L CNN
F 2 "" H 1200 2300 50  0001 C CNN
F 3 "" H 1200 2300 50  0001 C CNN
	1    1200 2300
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG03
U 1 1 610A3A67
P 1200 2300
F 0 "#FLG03" H 1200 2375 50  0001 C CNN
F 1 "PWR_FLAG" H 1200 2473 50  0000 C CNN
F 2 "" H 1200 2300 50  0001 C CNN
F 3 "~" H 1200 2300 50  0001 C CNN
	1    1200 2300
	-1   0    0    1   
$EndComp
Connection ~ 1200 2300
Wire Wire Line
	1200 2000 1300 2000
Wire Wire Line
	1200 2100 1300 2100
Wire Wire Line
	1200 2200 1300 2200
Wire Wire Line
	1600 1100 1500 1100
$Comp
L power:GND #PWR017
U 1 1 60FCF850
P 1500 750
F 0 "#PWR017" H 1500 500 50  0001 C CNN
F 1 "GND" H 1505 577 50  0000 C CNN
F 2 "" H 1500 750 50  0001 C CNN
F 3 "" H 1500 750 50  0001 C CNN
	1    1500 750 
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R1
U 1 1 60FD03CB
P 1500 950
F 0 "R1" H 1559 996 50  0000 L CNN
F 1 "10k" H 1559 905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 1500 950 50  0001 C CNN
F 3 "~" H 1500 950 50  0001 C CNN
	1    1500 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 750  1500 850 
Wire Wire Line
	1500 1050 1500 1100
Connection ~ 1500 1100
Wire Wire Line
	1500 1100 1150 1100
Text HLabel 1300 1900 2    50   Output ~ 0
CAPACITIVE_SENSE
Wire Wire Line
	1300 1900 1200 1900
$EndSCHEMATC
