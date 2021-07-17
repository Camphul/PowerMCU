EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 9
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2050 1750 2    50   Output ~ 0
LED_R
Text HLabel 2050 2050 2    50   Output ~ 0
LED_G
Text HLabel 2050 2350 2    50   Output ~ 0
LED_B
$Comp
L Device:R_Small R?
U 1 1 60EB2D44
P 1800 1750
F 0 "R?" H 1650 1700 50  0000 C CNN
F 1 "47R" H 1650 1800 50  0000 C CNN
F 2 "" H 1800 1750 50  0001 C CNN
F 3 "~" H 1800 1750 50  0001 C CNN
	1    1800 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60EB3111
P 1800 2050
F 0 "R?" H 1650 2000 50  0000 C CNN
F 1 "47R" H 1650 2100 50  0000 C CNN
F 2 "" H 1800 2050 50  0001 C CNN
F 3 "~" H 1800 2050 50  0001 C CNN
	1    1800 2050
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60EB346C
P 1800 2350
F 0 "R?" H 1650 2300 50  0000 C CNN
F 1 "47R" H 1650 2400 50  0000 C CNN
F 2 "" H 1800 2350 50  0001 C CNN
F 3 "~" H 1800 2350 50  0001 C CNN
	1    1800 2350
	0    1    1    0   
$EndComp
Text HLabel 2050 2550 2    50   Input ~ 0
LED_GND
Wire Wire Line
	1550 1750 1700 1750
Wire Wire Line
	1900 2350 2050 2350
Wire Wire Line
	1900 2050 2050 2050
Wire Wire Line
	2050 1750 1900 1750
Text HLabel 1850 1400 2    50   Input ~ 0
BUTTON_VCC
Text HLabel 1850 1300 2    50   Output ~ 0
BUTTON_NC
Text HLabel 1850 1200 2    50   Output ~ 0
BUTTON_NO
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 60ECD1C9
P 1650 1300
F 0 "J?" H 1542 975 50  0000 C CNN
F 1 "BTN_CONNECTOR" H 1542 1066 50  0000 C CNN
F 2 "" H 1650 1300 50  0001 C CNN
F 3 "~" H 1650 1300 50  0001 C CNN
	1    1650 1300
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 60EC404A
P 1000 2200
F 0 "J?" H 892 1775 50  0000 C CNN
F 1 "RGB_LED_CONNECTOR" H 892 1866 50  0000 C CNN
F 2 "" H 1000 2200 50  0001 C CNN
F 3 "~" H 1000 2200 50  0001 C CNN
	1    1000 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 2000 1550 2000
Wire Wire Line
	1550 1750 1550 2000
Wire Wire Line
	1700 2050 1200 2050
Wire Wire Line
	1200 2050 1200 2100
Wire Wire Line
	1700 2350 1700 2200
Wire Wire Line
	1700 2200 1200 2200
Wire Wire Line
	2050 2550 1200 2550
Wire Wire Line
	1200 2550 1200 2300
Text Notes 2500 1900 0    50   ~ 0
Nog niet zeker of de aliexpress RGB momentary switches hun LED's shakelen op GND of op Vin.\nWaarschijnlijk JST XH connector gebruiken\n
$EndSCHEMATC
