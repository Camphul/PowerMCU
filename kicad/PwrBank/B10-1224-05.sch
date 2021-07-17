EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 9
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3950 2100 2    50   Input ~ 0
GND_IN_BUCK
Text HLabel 3950 1950 2    50   Input ~ 0
V_IN_BUCK
Text HLabel 3950 2250 2    50   Output ~ 0
5V
Text HLabel 3950 2400 2    50   Output ~ 0
5V_GND
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 60ECABDF
P 3450 2200
F 0 "J?" H 3342 1775 50  0000 C CNN
F 1 "SCREW_TERMINALS_DCDC_MODULE" H 3342 1866 50  0000 C CNN
F 2 "" H 3450 2200 50  0001 C CNN
F 3 "~" H 3450 2200 50  0001 C CNN
	1    3450 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3650 2000 3800 2000
Wire Wire Line
	3800 2000 3800 1950
Wire Wire Line
	3800 1950 3950 1950
Wire Wire Line
	3950 2100 3650 2100
Wire Wire Line
	3650 2200 3850 2200
Wire Wire Line
	3850 2200 3850 2250
Wire Wire Line
	3850 2250 3950 2250
Wire Wire Line
	3700 2300 3700 2400
Wire Wire Line
	3700 2400 3950 2400
Wire Wire Line
	3700 2300 3650 2300
$EndSCHEMATC
