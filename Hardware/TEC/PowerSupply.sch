EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 3 6
Title "TEC Controller Power Supply"
Date "2021-05-01"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Transistor_FET:2N7002 Q9
U 1 1 60745F1B
P 6500 3400
F 0 "Q9" H 6704 3446 50  0000 L CNN
F 1 "2N7002PW" H 6704 3355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 6700 3325 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 6500 3400 50  0001 L CNN
F 4 "2N7002PW,115" H 6500 3400 50  0001 C CNN "PartNo"
	1    6500 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R29
U 1 1 6075110B
P 6200 2950
F 0 "R29" V 6150 2800 50  0000 C CNN
F 1 "100k" V 6300 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6130 2950 50  0001 C CNN
F 3 "~" H 6200 2950 50  0001 C CNN
F 4 "RC0805FR-07100KL" H 6200 2950 50  0001 C CNN "PartNo"
	1    6200 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	6200 3100 6200 3250
Wire Wire Line
	6200 3400 6300 3400
Wire Wire Line
	6600 3600 6600 3700
$Comp
L power:GND #PWR059
U 1 1 60754966
P 6600 3700
F 0 "#PWR059" H 6600 3450 50  0001 C CNN
F 1 "GND" H 6605 3527 50  0000 C CNN
F 2 "" H 6600 3700 50  0001 C CNN
F 3 "" H 6600 3700 50  0001 C CNN
	1    6600 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2800 6200 2650
$Comp
L power:+BATT #PWR058
U 1 1 6075537A
P 6200 2500
F 0 "#PWR058" H 6200 2350 50  0001 C CNN
F 1 "+BATT" H 6215 2673 50  0000 C CNN
F 2 "" H 6200 2500 50  0001 C CNN
F 3 "" H 6200 2500 50  0001 C CNN
	1    6200 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R30
U 1 1 60756EB0
P 6600 2950
F 0 "R30" V 6550 2800 50  0000 C CNN
F 1 "100k" V 6700 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6530 2950 50  0001 C CNN
F 3 "~" H 6600 2950 50  0001 C CNN
F 4 "RC0805FR-07100KL" H 6600 2950 50  0001 C CNN "PartNo"
	1    6600 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	6600 3200 6600 3150
Wire Wire Line
	6600 2800 6600 2650
Wire Wire Line
	6600 2650 6200 2650
Connection ~ 6200 2650
Wire Wire Line
	6200 2650 6200 2500
$Comp
L Transistor_FET:Si7141DP Q10
U 1 1 6075D40D
P 7050 2850
F 0 "Q10" V 7392 2850 50  0000 C CNN
F 1 "Si7141DP" V 7301 2850 50  0000 C CNN
F 2 "Package_SO:PowerPAK_SO-8_Single" H 7250 2775 50  0001 L CIN
F 3 "https://www.vishay.com/docs/65596/si7141dp.pdf" H 7050 2850 50  0001 L CNN
F 4 "SI7141DP-T1-GE3" H 7050 2850 50  0001 C CNN "PartNo"
	1    7050 2850
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_FET:Si7141DP Q11
U 1 1 60761BC8
P 8250 2850
F 0 "Q11" V 8592 2850 50  0000 C CNN
F 1 "Si7141DP" V 8501 2850 50  0000 C CNN
F 2 "Package_SO:PowerPAK_SO-8_Single" H 8450 2775 50  0001 L CIN
F 3 "https://www.vishay.com/docs/65596/si7141dp.pdf" H 8250 2850 50  0001 L CNN
F 4 "SI7141DP-T1-GE3" H 8250 2850 50  0001 C CNN "PartNo"
	1    8250 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 3150 7050 3150
Wire Wire Line
	8250 3150 8250 3050
Connection ~ 6600 3150
Wire Wire Line
	6600 3150 6600 3100
Wire Wire Line
	7050 3050 7050 3150
Connection ~ 7050 3150
Wire Wire Line
	7050 3150 8250 3150
Wire Wire Line
	7250 2750 7300 2750
Wire Wire Line
	7300 2750 7300 2500
Wire Wire Line
	8450 2750 8500 2750
Wire Wire Line
	8500 2750 8500 2500
$Comp
L power:+BATT #PWR061
U 1 1 60764871
P 7300 2500
F 0 "#PWR061" H 7300 2350 50  0001 C CNN
F 1 "+BATT" H 7315 2673 50  0000 C CNN
F 2 "" H 7300 2500 50  0001 C CNN
F 3 "" H 7300 2500 50  0001 C CNN
	1    7300 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR063
U 1 1 60764E0C
P 8500 2500
F 0 "#PWR063" H 8500 2350 50  0001 C CNN
F 1 "+BATT" H 8515 2673 50  0000 C CNN
F 2 "" H 8500 2500 50  0001 C CNN
F 3 "" H 8500 2500 50  0001 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2750 8000 2750
Wire Wire Line
	8000 2750 8000 2600
Wire Wire Line
	6850 2750 6800 2750
$Comp
L power:+VDC #PWR062
U 1 1 60766B4A
P 8000 2600
F 0 "#PWR062" H 8000 2500 50  0001 C CNN
F 1 "+VDC" H 8000 2875 50  0000 C CNN
F 2 "" H 8000 2600 50  0001 C CNN
F 3 "" H 8000 2600 50  0001 C CNN
	1    8000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2750 6800 2600
$Comp
L power:+VDC #PWR060
U 1 1 60767D18
P 6800 2600
F 0 "#PWR060" H 6800 2500 50  0001 C CNN
F 1 "+VDC" H 6800 2875 50  0000 C CNN
F 2 "" H 6800 2600 50  0001 C CNN
F 3 "" H 6800 2600 50  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG05
U 1 1 607758DF
P 7650 2700
F 0 "#FLG05" H 7650 2775 50  0001 C CNN
F 1 "PWR_FLAG" H 7650 2873 50  0000 C CNN
F 2 "" H 7650 2700 50  0001 C CNN
F 3 "~" H 7650 2700 50  0001 C CNN
	1    7650 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2700 7650 2750
Wire Wire Line
	7650 2750 8000 2750
Connection ~ 8000 2750
$Comp
L Symbols:TPS7A26 U8
U 1 1 60FF4DAF
P 5000 2950
F 0 "U8" H 5000 3365 50  0000 C CNN
F 1 "TPS7A26" H 5000 3274 50  0000 C CNN
F 2 "Package_SON:WSON-6-1EP_2x2mm_P0.65mm_EP1x1.6mm_ThermalVias" H 5000 2950 50  0001 C CNN
F 3 "" H 5000 2950 50  0001 C CNN
F 4 "TPS7A2650DRVR" H 5000 2950 50  0001 C CNN "PartNo"
	1    5000 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C34
U 1 1 60FFA895
P 4300 2800
F 0 "C34" V 4250 2700 50  0000 C CNN
F 1 "10uF" V 4250 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4338 2650 50  0001 C CNN
F 3 "~" H 4300 2800 50  0001 C CNN
F 4 "C2012X7S1E106K125AE" H 4300 2800 50  0001 C CNN "PartNo"
	1    4300 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C C35
U 1 1 60FFB928
P 5650 2800
F 0 "C35" V 5600 2700 50  0000 C CNN
F 1 "22uF" V 5600 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5688 2650 50  0001 C CNN
F 3 "~" H 5650 2800 50  0001 C CNN
F 4 "12063D226MAT2A" H 5650 2800 50  0001 C CNN "PartNo"
	1    5650 2800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR056
U 1 1 60FFC192
P 5000 3700
F 0 "#PWR056" H 5000 3450 50  0001 C CNN
F 1 "GND" H 5005 3527 50  0000 C CNN
F 2 "" H 5000 3700 50  0001 C CNN
F 3 "" H 5000 3700 50  0001 C CNN
	1    5000 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2800 4550 2800
Wire Wire Line
	4650 2950 4550 2950
Wire Wire Line
	4550 2950 4550 2800
Connection ~ 4550 2800
Wire Wire Line
	4550 2800 4650 2800
Wire Wire Line
	4150 2800 4050 2800
Wire Wire Line
	4050 2800 4050 3400
Wire Wire Line
	4050 3400 5000 3400
Wire Wire Line
	5000 3400 5000 3300
Connection ~ 5000 3400
Wire Wire Line
	5000 3400 5450 3400
Wire Wire Line
	5450 3400 5450 3100
Wire Wire Line
	5450 3100 5350 3100
Wire Wire Line
	5350 2800 5450 2800
Wire Wire Line
	5450 3400 5950 3400
Wire Wire Line
	5950 3400 5950 2800
Connection ~ 5450 3400
Wire Wire Line
	5800 2800 5950 2800
Connection ~ 5450 2800
Wire Wire Line
	5450 2800 5500 2800
$Comp
L power:+5V #PWR057
U 1 1 6100B423
P 5450 2500
F 0 "#PWR057" H 5450 2350 50  0001 C CNN
F 1 "+5V" H 5465 2673 50  0000 C CNN
F 2 "" H 5450 2500 50  0001 C CNN
F 3 "" H 5450 2500 50  0001 C CNN
	1    5450 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3400 5000 3700
Wire Wire Line
	5350 2950 5750 2950
Wire Wire Line
	5750 2950 5750 3250
Wire Wire Line
	5750 3250 6200 3250
Connection ~ 6200 3250
Wire Wire Line
	6200 3250 6200 3400
Wire Wire Line
	5450 2500 5450 2800
$Comp
L power:+BATT #PWR0154
U 1 1 6109C60B
P 4550 2500
F 0 "#PWR0154" H 4550 2350 50  0001 C CNN
F 1 "+BATT" H 4565 2673 50  0000 C CNN
F 2 "" H 4550 2500 50  0001 C CNN
F 3 "" H 4550 2500 50  0001 C CNN
	1    4550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2800 4550 2500
$EndSCHEMATC
