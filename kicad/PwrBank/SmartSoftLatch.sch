EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 9
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2550 1200 1    50   Input ~ 0
BTN_NO
Text HLabel 2800 2450 2    50   Output ~ 0
MCU_LATCH_BTN
Text HLabel 4950 2600 2    50   Input ~ 0
MCU_LATCH_ENABLE
$Comp
L Device:Q_PMOS_DGS Q2
U 1 1 60F1B941
P 4400 1150
F 0 "Q2" V 4742 1150 50  0000 C CNN
F 1 "SUD50P08-25L" V 4651 1150 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 4600 1250 50  0001 C CNN
F 3 "https://nl.mouser.com/datasheet/2/427/sud50p08-1766022.pdf" H 4400 1150 50  0001 C CNN
	1    4400 1150
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Zener_Small D1
U 1 1 60F1C9B7
P 2950 1950
F 0 "D1" H 2950 2157 50  0000 C CNN
F 1 "3.3vZ" H 2950 2066 50  0000 C CNN
F 2 "" V 2950 1950 50  0001 C CNN
F 3 "~" V 2950 1950 50  0001 C CNN
	1    2950 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1650 2550 1950
Wire Wire Line
	3200 1950 3100 1950
Wire Wire Line
	2550 1200 2550 1300
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q1
U 2 1 60F15F83
P 4350 2600
F 0 "Q1" H 4555 2600 50  0000 L CNN
F 1 "SQ4946CEY" H 4555 2555 50  0001 L CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 4550 2600 50  0001 C CNN
F 3 "https://www.vishay.com/docs/77342/sq4946cey.pdf" H 4550 2600 50  0001 C CNN
	2    4350 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3400 2600 2550 2600
Connection ~ 2550 1950
Wire Wire Line
	2550 1950 2800 1950
Wire Wire Line
	3500 1050 3650 1050
Wire Wire Line
	3700 2400 3900 2400
Wire Wire Line
	4950 2600 4700 2600
$Comp
L Device:R_Small R4
U 1 1 60F518BA
P 4700 2750
F 0 "R4" H 4759 2796 50  0000 L CNN
F 1 "10K" H 4759 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4700 2750 50  0001 C CNN
F 3 "~" H 4700 2750 50  0001 C CNN
	1    4700 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2650 4700 2600
Connection ~ 4700 2600
Wire Wire Line
	4700 2600 4550 2600
$Comp
L Device:C_Small C2
U 1 1 60F52BB7
P 3650 1250
F 0 "C2" H 3559 1204 50  0000 R CNN
F 1 "10nF" H 3559 1295 50  0000 R CNN
F 2 "" H 3650 1250 50  0001 C CNN
F 3 "~" H 3650 1250 50  0001 C CNN
	1    3650 1250
	1    0    0    1   
$EndComp
Wire Wire Line
	3650 1150 3650 1050
Connection ~ 3650 1050
Wire Wire Line
	3650 1050 3900 1050
$Comp
L Device:R_Small R2
U 1 1 60F53F6B
P 3900 1300
F 0 "R2" H 3959 1346 50  0000 L CNN
F 1 "100K" H 3959 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 3900 1300 50  0001 C CNN
F 3 "~" H 3900 1300 50  0001 C CNN
	1    3900 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1200 3900 1050
Connection ~ 3900 1050
Wire Wire Line
	3900 1050 4200 1050
$Comp
L Device:R_Small R3
U 1 1 60F56A0C
P 3900 1650
F 0 "R3" H 3959 1696 50  0000 L CNN
F 1 "100K" H 3959 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 3900 1650 50  0001 C CNN
F 3 "~" H 3900 1650 50  0001 C CNN
	1    3900 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1450 4400 1450
Wire Wire Line
	4400 1450 4400 1350
Wire Wire Line
	3900 1400 3900 1450
Connection ~ 3900 1450
Wire Wire Line
	3900 1450 3900 1550
Wire Wire Line
	3650 1350 3650 1850
Wire Wire Line
	3650 1850 3900 1850
Wire Wire Line
	3900 1850 3900 1750
Wire Wire Line
	3900 1850 3900 2400
Connection ~ 3900 1850
Connection ~ 3900 2400
Wire Wire Line
	3900 2400 4250 2400
Wire Wire Line
	2550 1950 2550 2450
Wire Wire Line
	2800 2450 2550 2450
Connection ~ 2550 2450
Wire Wire Line
	2550 2450 2550 2600
$Comp
L Device:C_Small C1
U 1 1 60F5A9D9
P 2950 2300
F 0 "C1" V 2721 2300 50  0000 C CNN
F 1 "100nF" V 2812 2300 50  0000 C CNN
F 2 "" H 2950 2300 50  0001 C CNN
F 3 "~" H 2950 2300 50  0001 C CNN
	1    2950 2300
	0    -1   1    0   
$EndComp
Connection ~ 2800 1950
Wire Wire Line
	2800 1950 2850 1950
Wire Wire Line
	2850 2300 2800 2300
Wire Wire Line
	2800 1950 2800 2300
Wire Wire Line
	3050 2300 3100 2300
Wire Wire Line
	3100 2300 3100 1950
Connection ~ 3100 1950
Wire Wire Line
	3100 1950 3050 1950
Wire Wire Line
	4600 1050 4900 1050
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q1
U 1 1 60F157B9
P 3600 2600
F 0 "Q1" H 3804 2600 50  0000 L CNN
F 1 "SQ4946CEY" H 3805 2555 50  0001 L CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 3800 2600 50  0001 C CNN
F 3 "https://www.vishay.com/docs/77342/sq4946cey.pdf" H 3800 2600 50  0001 C CNN
	1    3600 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 6100200E
P 3200 1950
F 0 "#PWR016" H 3200 1700 50  0001 C CNN
F 1 "GND" V 3205 1822 50  0000 R CNN
F 2 "" H 3200 1950 50  0001 C CNN
F 3 "" H 3200 1950 50  0001 C CNN
	1    3200 1950
	0    -1   -1   0   
$EndComp
$Comp
L power:+BATT #PWR017
U 1 1 61002D6C
P 3500 1050
F 0 "#PWR017" H 3500 900 50  0001 C CNN
F 1 "+BATT" V 3515 1177 50  0000 L CNN
F 2 "" H 3500 1050 50  0001 C CNN
F 3 "" H 3500 1050 50  0001 C CNN
	1    3500 1050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 61006C10
P 4700 2850
F 0 "#PWR020" H 4700 2600 50  0001 C CNN
F 1 "GND" H 4705 2677 50  0000 C CNN
F 2 "" H 4700 2850 50  0001 C CNN
F 3 "" H 4700 2850 50  0001 C CNN
	1    4700 2850
	1    0    0    -1  
$EndComp
$Comp
L +batt_switched:+BATT_SWITCHED #PWR021
U 1 1 6102417F
P 4900 1050
F 0 "#PWR021" H 4900 900 50  0001 C CNN
F 1 "+BATT_SWITCHED" V 4915 1178 50  0000 L CNN
F 2 "" H 4900 1050 50  0001 C CNN
F 3 "" H 4900 1050 50  0001 C CNN
	1    4900 1050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 6108B83A
P 4250 2800
F 0 "#PWR019" H 4250 2550 50  0001 C CNN
F 1 "GND" H 4255 2627 50  0000 C CNN
F 2 "" H 4250 2800 50  0001 C CNN
F 3 "" H 4250 2800 50  0001 C CNN
	1    4250 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 6108DDC7
P 3700 2800
F 0 "#PWR018" H 3700 2550 50  0001 C CNN
F 1 "GND" H 3705 2627 50  0000 C CNN
F 2 "" H 3700 2800 50  0001 C CNN
F 3 "" H 3700 2800 50  0001 C CNN
	1    3700 2800
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG04
U 1 1 6109154A
P 2550 1300
F 0 "#FLG04" H 2550 1375 50  0001 C CNN
F 1 "PWR_FLAG" V 2550 1428 50  0000 L CNN
F 2 "" H 2550 1300 50  0001 C CNN
F 3 "~" H 2550 1300 50  0001 C CNN
	1    2550 1300
	0    1    1    0   
$EndComp
Connection ~ 2550 1300
Wire Wire Line
	2550 1300 2550 1450
$Comp
L power:PWR_FLAG #FLG05
U 1 1 610980DE
P 3650 1050
F 0 "#FLG05" H 3650 1125 50  0001 C CNN
F 1 "PWR_FLAG" H 3650 1223 50  0000 C CNN
F 2 "" H 3650 1050 50  0001 C CNN
F 3 "~" H 3650 1050 50  0001 C CNN
	1    3650 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 60F1D2F1
P 2550 1550
F 0 "R1" H 2609 1596 50  0000 L CNN
F 1 "10K" H 2609 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 2550 1550 50  0001 C CNN
F 3 "~" H 2550 1550 50  0001 C CNN
	1    2550 1550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
