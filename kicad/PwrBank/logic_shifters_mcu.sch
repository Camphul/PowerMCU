EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
Title "Logic Shifters MCU"
Date "2021-07-17"
Rev "1"
Comp "Logic Shift"
Comment1 "Logic Shifters required for second UART(5v) to be readable by MCU's 3.3v logic"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3750 2300 1    50   Input ~ 0
HV
Text HLabel 3250 2300 1    50   Input ~ 0
LV
$Comp
L Device:R_Small R18
U 1 1 60F399FD
P 3250 2500
AR Path="/60F2D9E7/60F3980E/60F399FD" Ref="R18"  Part="1" 
AR Path="/60F2D9E7/60F56C27/60F399FD" Ref="R16"  Part="1" 
F 0 "R18" H 3192 2454 50  0000 R CNN
F 1 "10K" H 3192 2545 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 3250 2500 50  0001 C CNN
F 3 "~" H 3250 2500 50  0001 C CNN
	1    3250 2500
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R19
U 1 1 60F39B1A
P 3750 2500
AR Path="/60F2D9E7/60F3980E/60F39B1A" Ref="R19"  Part="1" 
AR Path="/60F2D9E7/60F56C27/60F39B1A" Ref="R17"  Part="1" 
F 0 "R19" H 3809 2546 50  0000 L CNN
F 1 "10K" H 3809 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 3750 2500 50  0001 C CNN
F 3 "~" H 3750 2500 50  0001 C CNN
	1    3750 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2300 3250 2350
Wire Wire Line
	3750 2300 3750 2400
Text HLabel 3200 2850 0    50   BiDi ~ 0
IO_LV
Text HLabel 3800 2850 2    50   BiDi ~ 0
IO_HV
Text Notes 2700 1800 0    50   ~ 0
LV = low voltage/3.3v\nHV = high voltage/5v\n\nIO_LV = bidirectional side of low io capable device\nIO_HV = bidrectional side of high io capable device\n\nAs circuit reference see: https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide/all
$Comp
L Transistor_FET:BSS138 Q4
U 1 1 60F3AB7E
P 3500 2750
AR Path="/60F2D9E7/60F3980E/60F3AB7E" Ref="Q4"  Part="1" 
AR Path="/60F2D9E7/60F56C27/60F3AB7E" Ref="Q3"  Part="1" 
F 0 "Q4" V 3749 2750 50  0000 C CNN
F 1 "BSS138" V 3840 2750 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3700 2675 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 3500 2750 50  0001 L CNN
	1    3500 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 2850 3250 2850
Wire Wire Line
	3250 2850 3250 2600
Wire Wire Line
	3250 2350 3500 2350
Wire Wire Line
	3500 2350 3500 2550
Connection ~ 3250 2350
Wire Wire Line
	3250 2350 3250 2400
Wire Wire Line
	3750 2600 3750 2850
Wire Wire Line
	3750 2850 3700 2850
Wire Wire Line
	3200 2850 3250 2850
Connection ~ 3250 2850
Wire Wire Line
	3800 2850 3750 2850
Connection ~ 3750 2850
$EndSCHEMATC
