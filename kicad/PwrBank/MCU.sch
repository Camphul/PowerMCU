EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 9
Title "ESP32_Devkit_Addons"
Date "2021-07-17"
Rev ""
Comp "Logic Shift"
Comment1 "ESP32-WROOM32 DevkitC with additional required circuitry"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP32-DEVKITC-32D:ESP32-DEVKITC-32D U2
U 1 1 60F2EDCB
P 6050 2900
F 0 "U2" H 6050 4067 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 6050 3976 50  0000 C CNN
F 2 "ESP32-DEVKITC-32D:MODULE_ESP32-DEVKITC-32D" H 6050 2900 50  0001 L BNN
F 3 "" H 6050 2900 50  0001 L BNN
F 4 "4" H 6050 2900 50  0001 L BNN "PARTREV"
F 5 "Espressif Systems" H 6050 2900 50  0001 L BNN "MANUFACTURER"
	1    6050 2900
	1    0    0    -1  
$EndComp
Text HLabel 8600 3300 2    50   Output ~ 0
BMS_TX
$Comp
L Device:R_Small R12
U 1 1 60F3049F
P 4850 3300
F 0 "R12" V 5046 3300 50  0000 C CNN
F 1 "10K" V 4955 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4850 3300 50  0001 C CNN
F 3 "~" H 4850 3300 50  0001 C CNN
	1    4850 3300
	0    1    -1   0   
$EndComp
Text HLabel 4650 3000 0    50   Input ~ 0
SOFTLATCH_BTN_3v3
Text Notes 3550 3550 0    50   ~ 0
Button input which should be 3.3v\nUse external zener outside this schematic
Wire Wire Line
	8600 2200 8500 2200
Wire Wire Line
	8600 3000 8500 3000
Wire Wire Line
	8600 3100 8500 3100
Wire Wire Line
	8600 2300 8500 2300
$Sheet
S 7950 2900 550  500 
U 60F56C27
F0 "logic_shifter_mcu_TX" 50
F1 "logic_shifters_mcu.sch" 50
F2 "IO_LV" B R 8500 3200 50 
F3 "IO_HV" B R 8500 3300 50 
F4 "HV" I R 8500 3000 50 
F5 "LV" I R 8500 3100 50 
$EndSheet
Text HLabel 8600 2500 2    50   Input ~ 0
BMS_RX
Wire Wire Line
	8600 3300 8500 3300
Wire Wire Line
	8600 2500 8500 2500
Text Label 6950 3000 0    50   ~ 0
U2TXD
Wire Wire Line
	6850 3000 6950 3000
Wire Wire Line
	6850 3100 6950 3100
Text Label 6950 3100 0    50   ~ 0
U2RXD
Text Label 8850 3200 0    50   ~ 0
U2TXD
Wire Wire Line
	8850 2400 8500 2400
Text Label 8850 2400 0    50   ~ 0
U2RXD
Wire Wire Line
	8850 3200 8500 3200
Text Notes 8000 1950 0    50   ~ 0
IMPLIES THAT RX AND TX ARE TWISTED TO\nRX -> TX\nTX -> RX\nIN THE CONNECTOR CABLE\n\nRequired for serial communication.\nWe do not use VCC from BMS as HV since it outputs 10v\naccording to online resources.
Wire Notes Line
	7900 1250 10250 1250
Text Notes 7900 1200 0    50   ~ 10
3.3v - 5v bidirectional logic shifting for BMS communications
Wire Wire Line
	7150 2000 6850 2000
NoConn ~ 6850 2300
NoConn ~ 6850 2400
Text Notes 4800 1500 0    50   ~ 0
TXD0 and RXD0 are connected to the usb serial converter on the module.\nLeave unconnected.
Wire Wire Line
	4650 3000 4750 3000
Wire Wire Line
	5250 3300 5050 3300
Wire Wire Line
	4750 3300 4750 3000
Connection ~ 4750 3000
Wire Wire Line
	4750 3000 5250 3000
$Comp
L Device:LED_Small D3
U 1 1 60F6DAA2
P 1600 2050
F 0 "D3" V 1650 2250 50  0000 R CNN
F 1 "LED_SMD_BLUE" V 1550 2700 50  0000 R CNN
F 2 "" V 1600 2050 50  0001 C CNN
F 3 "~" V 1600 2050 50  0001 C CNN
	1    1600 2050
	0    -1   -1   0   
$EndComp
Text Label 5100 2700 2    50   ~ 0
SHUTDOWN_SIGNAL
Wire Wire Line
	5100 2700 5250 2700
Text Label 2250 1750 0    50   ~ 0
SHUTDOWN_SIGNAL
Wire Wire Line
	2050 1750 2050 1400
Connection ~ 2050 1750
Wire Wire Line
	2050 1750 2250 1750
Text HLabel 2300 1400 2    50   Output ~ 0
SAFE_SHUTDOWN_SIGNAL
Wire Wire Line
	2300 1400 2050 1400
$Comp
L Device:R_Small R10
U 1 1 60F71BF4
P 2050 2000
F 0 "R10" H 1992 1954 50  0000 R CNN
F 1 "10K" H 1992 2045 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 2050 2000 50  0001 C CNN
F 3 "~" H 2050 2000 50  0001 C CNN
	1    2050 2000
	1    0    0    1   
$EndComp
Wire Wire Line
	2050 1750 2050 1900
Wire Wire Line
	2050 2100 2050 2150
Connection ~ 2050 2150
Wire Wire Line
	2050 2150 2250 2150
Wire Wire Line
	1600 2150 2050 2150
$Comp
L Device:R_Small R8
U 1 1 60F80C8C
P 1600 1750
F 0 "R8" H 1542 1704 50  0000 R CNN
F 1 "470R" H 1542 1795 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 1600 1750 50  0001 C CNN
F 3 "~" H 1600 1750 50  0001 C CNN
	1    1600 1750
	1    0    0    1   
$EndComp
Wire Wire Line
	1600 1850 1600 1950
Wire Wire Line
	1600 1650 1600 1400
Wire Wire Line
	1600 1400 2050 1400
Connection ~ 2050 1400
Wire Notes Line
	850  2250 3300 2250
Wire Notes Line
	3300 2250 3300 1250
Wire Notes Line
	3300 1250 850  1250
Wire Notes Line
	850  1250 850  2250
Text Notes 850  1200 0    50   ~ 10
SAFE SHUTDOWN STATUS WITH INDICATOR LED
Text Label 6950 3400 0    50   ~ 0
SOFTLATCH_FET_GATE
Wire Wire Line
	6950 3400 6850 3400
$Comp
L Device:LED_Small D4
U 1 1 60F351C2
P 1600 3250
F 0 "D4" V 1650 3450 50  0000 R CNN
F 1 "LED_SMD_GREEN" V 1550 3900 50  0000 R CNN
F 2 "" V 1600 3250 50  0001 C CNN
F 3 "~" V 1600 3250 50  0001 C CNN
	1    1600 3250
	0    -1   -1   0   
$EndComp
Text Label 2250 2950 0    50   ~ 0
SOFTLATCH_FET_GATE
Wire Wire Line
	2050 2950 2050 2600
Connection ~ 2050 2950
Wire Wire Line
	2050 2950 2250 2950
Text HLabel 2300 2600 2    50   Output ~ 0
SOFTLATCH_GATE_ENABLE
Wire Wire Line
	2300 2600 2050 2600
$Comp
L Device:R_Small R11
U 1 1 60F351CF
P 2050 3200
F 0 "R11" H 1992 3154 50  0000 R CNN
F 1 "10K" H 1992 3245 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 2050 3200 50  0001 C CNN
F 3 "~" H 2050 3200 50  0001 C CNN
	1    2050 3200
	1    0    0    1   
$EndComp
Wire Wire Line
	2050 2950 2050 3100
Wire Wire Line
	2050 3300 2050 3350
Connection ~ 2050 3350
Wire Wire Line
	2050 3350 2250 3350
Wire Wire Line
	1600 3350 2050 3350
$Comp
L Device:R_Small R9
U 1 1 60F351DA
P 1600 2950
F 0 "R9" H 1542 2904 50  0000 R CNN
F 1 "470R" H 1542 2995 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 1600 2950 50  0001 C CNN
F 3 "~" H 1600 2950 50  0001 C CNN
	1    1600 2950
	1    0    0    1   
$EndComp
Wire Wire Line
	1600 3050 1600 3150
Wire Wire Line
	1600 2850 1600 2600
Wire Wire Line
	1600 2600 2050 2600
Connection ~ 2050 2600
Wire Notes Line
	850  3450 3300 3450
Wire Notes Line
	3300 3450 3300 2450
Wire Notes Line
	3300 2450 850  2450
Wire Notes Line
	850  2450 850  3450
Text Notes 850  2400 0    50   ~ 10
SOFTLATCH PIN OUTPUT WITH INDICATOR LED
Wire Wire Line
	6900 2800 6850 2800
Text HLabel 6900 2500 2    50   BiDi ~ 0
SDA1
Wire Wire Line
	6900 2500 6850 2500
Text HLabel 6900 2200 2    50   Output ~ 0
SCL1
Wire Wire Line
	6900 2200 6850 2200
NoConn ~ 6850 3800
NoConn ~ 6850 3700
NoConn ~ 6850 3600
NoConn ~ 6850 3500
NoConn ~ 6850 3300
NoConn ~ 6850 3200
NoConn ~ 6850 2900
NoConn ~ 6850 2600
NoConn ~ 6850 2100
NoConn ~ 5250 2100
NoConn ~ 5250 2200
NoConn ~ 5250 2300
NoConn ~ 5250 2400
NoConn ~ 5250 2500
NoConn ~ 5250 2600
NoConn ~ 5250 2800
NoConn ~ 5250 2900
NoConn ~ 5250 3100
NoConn ~ 5250 3200
NoConn ~ 5250 3400
NoConn ~ 5250 3500
NoConn ~ 5250 3600
NoConn ~ 5250 3700
Wire Notes Line
	7900 1250 7900 3550
Wire Notes Line
	10250 1250 10250 3550
Wire Notes Line
	7900 3550 10250 3550
Wire Notes Line
	3450 4000 7750 4000
Wire Notes Line
	7750 4000 7750 1250
Wire Notes Line
	7750 1250 3450 1250
Wire Notes Line
	3450 1250 3450 4000
Text Notes 3450 1200 0    50   ~ 10
ESP32-WROOM32 DevKitC with additional circuitry\n
Wire Wire Line
	5250 2000 5150 2000
Wire Wire Line
	5150 3800 5250 3800
$Comp
L power:GND #PWR029
U 1 1 61034275
P 7150 2000
F 0 "#PWR029" H 7150 1750 50  0001 C CNN
F 1 "GND" V 7155 1872 50  0000 R CNN
F 2 "" H 7150 2000 50  0001 C CNN
F 3 "" H 7150 2000 50  0001 C CNN
	1    7150 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR025
U 1 1 61035069
P 2250 2150
F 0 "#PWR025" H 2250 1900 50  0001 C CNN
F 1 "GND" V 2255 2022 50  0000 R CNN
F 2 "" H 2250 2150 50  0001 C CNN
F 3 "" H 2250 2150 50  0001 C CNN
	1    2250 2150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR026
U 1 1 61035606
P 2250 3350
F 0 "#PWR026" H 2250 3100 50  0001 C CNN
F 1 "GND" V 2255 3222 50  0000 R CNN
F 2 "" H 2250 3350 50  0001 C CNN
F 3 "" H 2250 3350 50  0001 C CNN
	1    2250 3350
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR027
U 1 1 61037CC9
P 5150 2000
F 0 "#PWR027" H 5150 1850 50  0001 C CNN
F 1 "+3.3V" V 5165 2128 50  0000 L CNN
F 2 "" H 5150 2000 50  0001 C CNN
F 3 "" H 5150 2000 50  0001 C CNN
	1    5150 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR028
U 1 1 61038914
P 5150 3800
F 0 "#PWR028" H 5150 3650 50  0001 C CNN
F 1 "+5V" V 5165 3928 50  0000 L CNN
F 2 "" H 5150 3800 50  0001 C CNN
F 3 "" H 5150 3800 50  0001 C CNN
	1    5150 3800
	0    -1   -1   0   
$EndComp
$Sheet
S 7950 2100 550  500 
U 60F3980E
F0 "logic_shifters_mcu_RX" 50
F1 "logic_shifters_mcu.sch" 50
F2 "IO_LV" B R 8500 2400 50 
F3 "IO_HV" B R 8500 2500 50 
F4 "HV" I R 8500 2200 50 
F5 "LV" I R 8500 2300 50 
$EndSheet
$Comp
L power:+5V #PWR030
U 1 1 61039E33
P 8600 2200
F 0 "#PWR030" H 8600 2050 50  0001 C CNN
F 1 "+5V" V 8615 2328 50  0000 L CNN
F 2 "" H 8600 2200 50  0001 C CNN
F 3 "" H 8600 2200 50  0001 C CNN
	1    8600 2200
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR031
U 1 1 6103A5D9
P 8600 2300
F 0 "#PWR031" H 8600 2150 50  0001 C CNN
F 1 "+3.3V" V 8615 2428 50  0000 L CNN
F 2 "" H 8600 2300 50  0001 C CNN
F 3 "" H 8600 2300 50  0001 C CNN
	1    8600 2300
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR032
U 1 1 6103DF7E
P 8600 3000
F 0 "#PWR032" H 8600 2850 50  0001 C CNN
F 1 "+5V" V 8615 3128 50  0000 L CNN
F 2 "" H 8600 3000 50  0001 C CNN
F 3 "" H 8600 3000 50  0001 C CNN
	1    8600 3000
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR033
U 1 1 6103E675
P 8600 3100
F 0 "#PWR033" H 8600 2950 50  0001 C CNN
F 1 "+3.3V" V 8615 3228 50  0000 L CNN
F 2 "" H 8600 3100 50  0001 C CNN
F 3 "" H 8600 3100 50  0001 C CNN
	1    8600 3100
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG06
U 1 1 6109BF9C
P 2250 2150
F 0 "#FLG06" H 2250 2225 50  0001 C CNN
F 1 "PWR_FLAG" H 2250 2323 50  0000 C CNN
F 2 "" H 2250 2150 50  0001 C CNN
F 3 "~" H 2250 2150 50  0001 C CNN
	1    2250 2150
	1    0    0    -1  
$EndComp
Connection ~ 2250 2150
$Comp
L power:PWR_FLAG #FLG08
U 1 1 6109CF19
P 9050 3000
F 0 "#FLG08" H 9050 3075 50  0001 C CNN
F 1 "PWR_FLAG" V 9050 3128 50  0000 L CNN
F 2 "" H 9050 3000 50  0001 C CNN
F 3 "~" H 9050 3000 50  0001 C CNN
	1    9050 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	9050 3000 9000 3000
Wire Wire Line
	9000 3000 9000 2950
Wire Wire Line
	9000 2950 8600 2950
Wire Wire Line
	8600 2950 8600 3000
Connection ~ 8600 3000
$Comp
L power:PWR_FLAG #FLG07
U 1 1 610A25D9
P 5050 3300
F 0 "#FLG07" H 5050 3375 50  0001 C CNN
F 1 "PWR_FLAG" H 5050 3473 50  0000 C CNN
F 2 "" H 5050 3300 50  0001 C CNN
F 3 "~" H 5050 3300 50  0001 C CNN
	1    5050 3300
	1    0    0    -1  
$EndComp
Connection ~ 5050 3300
Wire Wire Line
	5050 3300 4950 3300
Text HLabel 6900 2800 2    50   Output ~ 0
SCL2
Text HLabel 6850 2700 2    50   BiDi ~ 0
SDA2
$EndSCHEMATC
