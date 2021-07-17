EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
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
L ESP32-DEVKITC-32D:ESP32-DEVKITC-32D U?
U 1 1 60F2EDCB
P 5100 3650
F 0 "U?" H 5100 4817 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 5100 4726 50  0000 C CNN
F 2 "MODULE_ESP32-DEVKITC-32D" H 5100 3650 50  0001 L BNN
F 3 "" H 5100 3650 50  0001 L BNN
F 4 "4" H 5100 3650 50  0001 L BNN "PARTREV"
F 5 "Espressif Systems" H 5100 3650 50  0001 L BNN "MANUFACTURER"
	1    5100 3650
	1    0    0    -1  
$EndComp
Text HLabel 5850 5550 2    50   Input ~ 0
U2RXD
Wire Wire Line
	5900 3750 5950 3750
Wire Wire Line
	5900 3850 5950 3850
Text HLabel 5850 5400 2    50   Output ~ 0
U2TXD
$Comp
L Device:R_Small R?
U 1 1 60F3049F
P 3900 3750
F 0 "R?" H 3842 3704 50  0000 R CNN
F 1 "10K" H 3842 3795 50  0000 R CNN
F 2 "" H 3900 3750 50  0001 C CNN
F 3 "~" H 3900 3750 50  0001 C CNN
	1    3900 3750
	1    0    0    1   
$EndComp
Wire Wire Line
	3900 3450 4300 3450
Wire Wire Line
	4300 4050 3900 4050
Wire Wire Line
	3900 3450 3900 3650
Wire Wire Line
	3900 3850 3900 4050
Text HLabel 3550 3450 0    50   Output ~ 0
BTN_3v3
Wire Wire Line
	3550 3450 3900 3450
Connection ~ 3900 3450
Text Notes 2500 3400 0    50   ~ 0
Button input which should be 3.3v\nUse external zener outside this schematic
Text HLabel 4300 4550 0    50   Output ~ 0
5V
Text HLabel 4300 2750 0    50   Output ~ 0
3V3
$Sheet
S 3050 5000 1250 800 
U 60F3980E
F0 "logic_shifters_mcu" 50
F1 "logic_shifters_mcu.sch" 50
$EndSheet
$EndSCHEMATC
