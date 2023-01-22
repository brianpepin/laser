EESchema Schematic File Version 5
EELAYER 36 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 6
Title "Batterty Charger"
Date "2021-11-07"
Rev "1.5"
Comp "Brian Pepin"
Comment1 "4A charge current to 2S LiPo pack."
Comment2 "CHARGE signal goes low when charging."
Comment3 "BAT_VOLT is pack voltage / 3 for insertion to A/D."
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 3750 2850
Connection ~ 4100 2350
Connection ~ 4100 2850
Connection ~ 4600 2850
Connection ~ 5200 2550
Connection ~ 5200 3500
Connection ~ 5200 3750
Connection ~ 5550 2550
Connection ~ 5950 3150
Connection ~ 6400 2550
Connection ~ 6400 3150
Connection ~ 6400 3600
Connection ~ 6400 4000
Connection ~ 6850 3150
Connection ~ 7350 3300
Wire Wire Line
	3750 2350 4100 2350
Wire Wire Line
	3750 2450 3750 2350
Wire Wire Line
	3750 2750 3750 2850
Wire Wire Line
	3750 2850 3400 2850
Wire Wire Line
	4100 1850 4100 1950
Wire Wire Line
	4100 2250 4100 2350
Wire Wire Line
	4100 2350 4100 2450
Wire Wire Line
	4100 2750 4100 2850
Wire Wire Line
	4100 2850 3750 2850
Wire Wire Line
	4300 3050 4700 3050
Wire Wire Line
	4300 3750 4300 3050
Wire Wire Line
	4350 3750 4300 3750
Wire Wire Line
	4600 1950 4600 1850
Wire Wire Line
	4600 2250 4600 2850
Wire Wire Line
	4600 2850 4100 2850
Wire Wire Line
	4600 2850 4700 2850
Wire Wire Line
	4600 3250 4600 3500
Wire Wire Line
	4600 3500 5200 3500
Wire Wire Line
	4700 2550 4800 2550
Wire Wire Line
	4700 2600 4700 2550
Wire Wire Line
	4700 3250 4600 3250
Wire Wire Line
	4750 3750 4650 3750
Wire Wire Line
	5050 3750 5200 3750
Wire Wire Line
	5100 2550 5200 2550
Wire Wire Line
	5200 1950 5200 1850
Wire Wire Line
	5200 2250 5200 2550
Wire Wire Line
	5200 2650 5200 2550
Wire Wire Line
	5200 3500 5200 3450
Wire Wire Line
	5200 3500 5200 3750
Wire Wire Line
	5200 3750 5200 3850
Wire Wire Line
	5550 2550 5200 2550
Wire Wire Line
	5700 2850 6100 2850
Wire Wire Line
	5700 3150 5950 3150
Wire Wire Line
	5950 3150 6200 3150
Wire Wire Line
	5950 3450 5950 3150
Wire Wire Line
	5950 3850 5950 3750
Wire Wire Line
	6200 3150 6200 4000
Wire Wire Line
	6200 4000 6400 4000
Wire Wire Line
	6300 3050 5700 3050
Wire Wire Line
	6300 3600 6300 3050
Wire Wire Line
	6400 2550 5550 2550
Wire Wire Line
	6400 2650 6400 2550
Wire Wire Line
	6400 3150 6400 3050
Wire Wire Line
	6400 3250 6400 3150
Wire Wire Line
	6400 3600 6300 3600
Wire Wire Line
	6400 3600 6400 3550
Wire Wire Line
	6400 3650 6400 3600
Wire Wire Line
	6400 4000 6400 3950
Wire Wire Line
	6400 4000 6850 4000
Wire Wire Line
	6500 2550 6400 2550
Wire Wire Line
	6500 3150 6400 3150
Wire Wire Line
	6800 2550 6850 2550
Wire Wire Line
	6800 3150 6850 3150
Wire Wire Line
	6850 2550 6850 3150
Wire Wire Line
	6850 3150 6850 3300
Wire Wire Line
	6850 4000 6850 3800
Wire Wire Line
	7350 2550 7350 2400
Wire Wire Line
	7350 2850 7350 2950
Wire Wire Line
	7350 3300 7350 3250
Wire Wire Line
	7350 3300 7650 3300
Wire Wire Line
	7350 3350 7350 3300
Wire Wire Line
	7350 3750 7350 3650
Text GLabel 3400 2850 0    50   Input ~ 0
~{CHARGE}
Text GLabel 7350 2400 1    50   Input ~ 0
BATT_SW
Text GLabel 7650 3300 2    50   Input ~ 0
BAT_VOLT
$Comp
L power:+3.3V #PWR067
U 1 1 610CB130
P 4100 1850
F 0 "#PWR067" H 4100 1700 50  0001 C CNN
F 1 "+3.3V" H 4115 2023 50  0000 C CNN
F 2 "" H 4100 1850 50  0001 C CNN
F 3 "" H 4100 1850 50  0001 C CNN
	1    4100 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR068
U 1 1 611BB0B6
P 4600 1850
F 0 "#PWR068" H 4600 1700 50  0001 C CNN
F 1 "+3.3V" H 4615 2023 50  0000 C CNN
F 2 "" H 4600 1850 50  0001 C CNN
F 3 "" H 4600 1850 50  0001 C CNN
	1    4600 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR070
U 1 1 611BD9DC
P 5200 1850
F 0 "#PWR070" H 5200 1700 50  0001 C CNN
F 1 "+12V" H 5215 2023 50  0000 C CNN
F 2 "" H 5200 1850 50  0001 C CNN
F 3 "" H 5200 1850 50  0001 C CNN
	1    5200 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR074
U 1 1 611B029C
P 6850 3800
F 0 "#PWR074" H 6850 3650 50  0001 C CNN
F 1 "+BATT" H 6865 3973 50  0000 C CNN
F 2 "" H 6850 3800 50  0001 C CNN
F 3 "" H 6850 3800 50  0001 C CNN
	1    6850 3800
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6148ADFA
P 5550 2550
F 0 "#FLG0101" H 5550 2625 50  0001 C CNN
F 1 "PWR_FLAG" H 5550 2723 50  0000 C CNN
F 2 "" H 5550 2550 50  0001 C CNN
F 3 "~" H 5550 2550 50  0001 C CNN
	1    5550 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR069
U 1 1 611C1819
P 4700 2600
F 0 "#PWR069" H 4700 2350 50  0001 C CNN
F 1 "GND" H 4705 2427 50  0000 C CNN
F 2 "" H 4700 2600 50  0001 C CNN
F 3 "" H 4700 2600 50  0001 C CNN
	1    4700 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR071
U 1 1 611B3A1C
P 5200 3850
F 0 "#PWR071" H 5200 3600 50  0001 C CNN
F 1 "GND" H 5205 3677 50  0000 C CNN
F 2 "" H 5200 3850 50  0001 C CNN
F 3 "" H 5200 3850 50  0001 C CNN
	1    5200 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR072
U 1 1 611B1740
P 5950 3850
F 0 "#PWR072" H 5950 3600 50  0001 C CNN
F 1 "GND" H 5955 3677 50  0000 C CNN
F 2 "" H 5950 3850 50  0001 C CNN
F 3 "" H 5950 3850 50  0001 C CNN
	1    5950 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR073
U 1 1 611ACC8A
P 6850 3300
F 0 "#PWR073" H 6850 3050 50  0001 C CNN
F 1 "GND" H 6855 3127 50  0000 C CNN
F 2 "" H 6850 3300 50  0001 C CNN
F 3 "" H 6850 3300 50  0001 C CNN
	1    6850 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR075
U 1 1 611C5C45
P 7350 3750
F 0 "#PWR075" H 7350 3500 50  0001 C CNN
F 1 "GND" H 7355 3577 50  0000 C CNN
F 2 "" H 7350 3750 50  0001 C CNN
F 3 "" H 7350 3750 50  0001 C CNN
	1    7350 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:L L5
U 1 1 611AA173
P 6400 3400
F 0 "L5" H 6453 3446 50  0000 L CNN
F 1 "2.5uH" H 6453 3355 50  0000 L CNN
F 2 "PowerSupplyFootprints:Inductor_Pulse_PA4341" H 6400 3400 50  0001 C CNN
F 3 "~" H 6400 3400 50  0001 C CNN
F 4 "PA4341.252NLT" H 6400 3400 50  0001 C CNN "PartNo"
	1    6400 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R27
U 1 1 610C8300
P 4100 2100
F 0 "R27" H 4170 2146 50  0000 L CNN
F 1 "560" H 4170 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4030 2100 50  0001 C CNN
F 3 "~" H 4100 2100 50  0001 C CNN
F 4 "ERJ-6ENF5600V" H 4100 2100 50  0001 C CNN "PartNo"
	1    4100 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R28
U 1 1 611B9C04
P 4600 2100
F 0 "R28" H 4670 2146 50  0000 L CNN
F 1 "10k" H 4670 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4530 2100 50  0001 C CNN
F 3 "~" H 4600 2100 50  0001 C CNN
F 4 "ERJ-6ENF1002V" H 4600 2100 50  0001 C CNN "PartNo"
	1    4600 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R29
U 1 1 611B4192
P 4900 3750
F 0 "R29" V 5107 3750 50  0000 C CNN
F 1 "2.2k" V 5016 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4830 3750 50  0001 C CNN
F 3 "~" H 4900 3750 50  0001 C CNN
F 4 "ERJ-PB6B2201V" H 4900 3750 50  0001 C CNN "PartNo"
	1    4900 3750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R30
U 1 1 611ADC4F
P 6400 3800
F 0 "R30" H 6330 3754 50  0000 R CNN
F 1 ".025" H 6330 3845 50  0000 R CNN
F 2 "Resistor_SMD:R_2010_5025Metric" V 6330 3800 50  0001 C CNN
F 3 "~" H 6400 3800 50  0001 C CNN
F 4 "WSL2010R0250FEA" H 6400 3800 50  0001 C CNN "PartNo"
	1    6400 3800
	-1   0    0    1   
$EndComp
$Comp
L Device:R R31
U 1 1 611C3776
P 7350 2700
F 0 "R31" H 7420 2746 50  0000 L CNN
F 1 "10k" H 7420 2655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7280 2700 50  0001 C CNN
F 3 "~" H 7350 2700 50  0001 C CNN
F 4 "ERJ-6ENF1002V" H 7350 2700 50  0001 C CNN "PartNo"
	1    7350 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R32
U 1 1 611C4CE6
P 7350 3100
F 0 "R32" H 7420 3146 50  0000 L CNN
F 1 "10k" H 7420 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7280 3100 50  0001 C CNN
F 3 "~" H 7350 3100 50  0001 C CNN
F 4 "ERJ-6ENF1002V" H 7350 3100 50  0001 C CNN "PartNo"
	1    7350 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R33
U 1 1 611C533B
P 7350 3500
F 0 "R33" H 7420 3546 50  0000 L CNN
F 1 "10k" H 7420 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7280 3500 50  0001 C CNN
F 3 "~" H 7350 3500 50  0001 C CNN
F 4 "ERJ-6ENF1002V" H 7350 3500 50  0001 C CNN "PartNo"
	1    7350 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky_ALT D20
U 1 1 6141F139
P 5200 2100
F 0 "D20" H 5200 1975 50  0000 C CNN
F 1 "CDBA540-HF" H 5200 1974 50  0001 C CNN
F 2 "Diode_SMD:D_SMA" H 5200 2100 50  0001 C CNN
F 3 "~" H 5200 2100 50  0001 C CNN
F 4 "CDBA540-HF" H 5200 2100 50  0001 C CNN "PartNo"
	1    5200 2100
	0    1    -1   0   
$EndComp
$Comp
L Device:D_Schottky_ALT D17
U 1 1 611A8DCA
P 6650 3150
F 0 "D17" H 6650 3025 50  0000 C CNN
F 1 "CDBA540-HF" H 6650 3024 50  0001 C CNN
F 2 "Diode_SMD:D_SMA" H 6650 3150 50  0001 C CNN
F 3 "~" H 6650 3150 50  0001 C CNN
F 4 "CDBA540-HF" H 6650 3150 50  0001 C CNN "PartNo"
	1    6650 3150
	1    0    0    1   
$EndComp
$Comp
L Device:LED_ALT D16
U 1 1 610C678E
P 4100 2600
F 0 "D16" V 4139 2482 50  0000 R CNN
F 1 "SM0805GCL" V 4048 2482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Castellated" H 4100 2600 50  0001 C CNN
F 3 "~" H 4100 2600 50  0001 C CNN
F 4 "SM0805GCL" H 4100 2600 50  0001 C CNN "PartNo"
	1    4100 2600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C64
U 1 1 615A4088
P 3750 2600
F 0 "C64" V 3498 2600 50  0000 C CNN
F 1 "4.7uF" V 3589 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3788 2450 50  0001 C CNN
F 3 "~" H 3750 2600 50  0001 C CNN
F 4 "JMK212B7475KGHT" H 3750 2600 50  0001 C CNN "PartNo"
	1    3750 2600
	-1   0    0    1   
$EndComp
$Comp
L Device:C C37
U 1 1 611B57DB
P 4500 3750
F 0 "C37" V 4248 3750 50  0000 C CNN
F 1 ".47uF" V 4339 3750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4538 3600 50  0001 C CNN
F 3 "~" H 4500 3750 50  0001 C CNN
F 4 "C2012X7R1E474K125AA" H 4500 3750 50  0001 C CNN "PartNo"
	1    4500 3750
	0    1    1    0   
$EndComp
$Comp
L Device:C C38
U 1 1 611C0FB8
P 4950 2550
F 0 "C38" V 4698 2550 50  0000 C CNN
F 1 ".1uF" V 4789 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4988 2400 50  0001 C CNN
F 3 "~" H 4950 2550 50  0001 C CNN
F 4 "C0805X104M5RACTU" H 4950 2550 50  0001 C CNN "PartNo"
	1    4950 2550
	0    1    1    0   
$EndComp
$Comp
L Device:C C39
U 1 1 611B08FC
P 5950 3600
F 0 "C39" H 6065 3646 50  0000 L CNN
F 1 "22uF" H 6065 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5988 3450 50  0001 C CNN
F 3 "~" H 5950 3600 50  0001 C CNN
F 4 "C3216X5R1V226M160AC" H 5950 3600 50  0001 C CNN "PartNo"
	1    5950 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C40
U 1 1 611AB45C
P 6650 2550
F 0 "C40" V 6398 2550 50  0000 C CNN
F 1 "10uF" V 6489 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6688 2400 50  0001 C CNN
F 3 "~" H 6650 2550 50  0001 C CNN
F 4 "GMK316AB7106KL-TR" H 6650 2550 50  0001 C CNN "PartNo"
	1    6650 2550
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:Si7141DP Q9
U 1 1 611A2E12
P 6300 2850
F 0 "Q9" H 6505 2850 50  0000 L CNN
F 1 "Si7141DP" H 6504 2895 50  0001 L CNN
F 2 "Package_SO:PowerPAK_SO-8_Single" H 6500 2775 50  0001 L CIN
F 3 "https://www.vishay.com/docs/65596/si7141dp.pdf" H 6300 2850 50  0001 L CNN
F 4 "SI7141DP-T1-GE3" H 6300 2850 50  0001 C CNN "PartNo"
	1    6300 2850
	1    0    0    1   
$EndComp
$Comp
L Battery_Management:LTC4002ES8-8.4 U6
U 1 1 6119CDF1
P 5200 3050
F 0 "U6" H 5300 3400 50  0000 C CNN
F 1 "LTC4002ES8-8.4" H 5500 2700 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5200 2600 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/4002f.pdf" H 4800 3400 50  0001 C CNN
F 4 "LTC4002ES8-8.4#PBF" H 5200 3050 50  0001 C CNN "PartNo"
	1    5200 3050
	1    0    0    -1  
$EndComp
$EndSCHEMATC