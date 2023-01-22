EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 6
Title "TEC Control Board"
Date "2021-05-01"
Rev "1"
Comp "Brian Pepin"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5F97005F
P 750 950
F 0 "#FLG01" H 750 1025 50  0001 C CNN
F 1 "PWR_FLAG" H 750 1123 50  0000 C CNN
F 2 "" H 750 950 50  0001 C CNN
F 3 "~" H 750 950 50  0001 C CNN
	1    750  950 
	-1   0    0    1   
$EndComp
$Comp
L power:+BATT #PWR01
U 1 1 5F971A9F
P 750 850
F 0 "#PWR01" H 750 700 50  0001 C CNN
F 1 "+BATT" H 765 1023 50  0000 C CNN
F 2 "" H 750 850 50  0001 C CNN
F 3 "" H 750 850 50  0001 C CNN
	1    750  850 
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5F9730B8
P 1250 950
F 0 "#FLG02" H 1250 1025 50  0001 C CNN
F 1 "PWR_FLAG" H 1250 1123 50  0000 C CNN
F 2 "" H 1250 950 50  0001 C CNN
F 3 "~" H 1250 950 50  0001 C CNN
	1    1250 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 850  1250 950 
Wire Wire Line
	750  850  750  950 
$Comp
L Device:C C6
U 1 1 5F98B442
P 4250 2150
F 0 "C6" V 3998 2150 50  0000 C CNN
F 1 ".1uF" V 4089 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4288 2000 50  0001 C CNN
F 3 "~" H 4250 2150 50  0001 C CNN
F 4 "VJ0805Y104KXXAT" H 4250 2150 50  0001 C CNN "PartNo"
	1    4250 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 3600 4550 3650
Text Notes 850  7350 0    50   ~ 0
Notes:\n1. In final design ensure GND end of current sense is isolated from rest of ground plane so pours don’t disrupt kelvin connection.\n2. Order thermal interface like TGF20-07870787-039.  \n
$Comp
L Symbols:ADC104S021 U3
U 1 1 5FCD4521
P 7000 3250
F 0 "U3" H 7100 3500 50  0000 C CNN
F 1 "ADC104S021" H 7300 2950 50  0000 C CNN
F 2 "Package_SO:VSSOP-10_3x3mm_P0.5mm" H 6600 3250 50  0001 C CNN
F 3 "" H 6600 3250 50  0001 C CNN
F 4 "ADC104S021CIMMX/NOPB" H 7000 3250 50  0001 C CNN "PartNo"
	1    7000 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5FCE0300
P 6800 2650
F 0 "C8" V 6548 2650 50  0000 C CNN
F 1 ".1uF" V 6639 2650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6838 2500 50  0001 C CNN
F 3 "~" H 6800 2650 50  0001 C CNN
F 4 "VJ0805Y104KXXAT" H 6800 2650 50  0001 C CNN "PartNo"
	1    6800 2650
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR022
U 1 1 5FCE1EEE
P 7000 2000
F 0 "#PWR022" H 7000 1850 50  0001 C CNN
F 1 "+3.3V" H 7015 2173 50  0000 C CNN
F 2 "" H 7000 2000 50  0001 C CNN
F 3 "" H 7000 2000 50  0001 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2750 6600 2650
Wire Wire Line
	6600 2650 6650 2650
Wire Wire Line
	7000 2000 7000 2250
Wire Wire Line
	6950 2650 7000 2650
Connection ~ 7000 2650
Wire Wire Line
	7000 2650 7000 2900
$Comp
L power:+3.3V #PWR02
U 1 1 5FD63329
P 1250 850
F 0 "#PWR02" H 1250 700 50  0001 C CNN
F 1 "+3.3V" H 1265 1023 50  0000 C CNN
F 2 "" H 1250 850 50  0001 C CNN
F 3 "" H 1250 850 50  0001 C CNN
	1    1250 850 
	1    0    0    -1  
$EndComp
$Comp
L pepin_con:DEANS J1
U 1 1 5FDC16FD
P 1450 1750
AR Path="/5FDC16FD" Ref="J1"  Part="1" 
AR Path="/5F992247/5FDC16FD" Ref="J?"  Part="1" 
F 0 "J1" H 1569 1750 50  0000 L CNN
F 1 "DEANS" H 1500 1600 50  0001 C CNN
F 2 "pepin-footprints:Connector_Deans_Male" H 1450 1750 50  0001 C CNN
F 3 "http://cdn.sparkfun.com/datasheets/Prototyping/deans_connector_PRT-11864.pdf" H 1450 1750 50  0001 C CNN
	1    1450 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR03
U 1 1 5FDC1703
P 1250 1600
AR Path="/5FDC1703" Ref="#PWR03"  Part="1" 
AR Path="/5F992247/5FDC1703" Ref="#PWR?"  Part="1" 
F 0 "#PWR03" H 1250 1450 50  0001 C CNN
F 1 "+BATT" H 1265 1773 50  0000 C CNN
F 2 "" H 1250 1600 50  0001 C CNN
F 3 "" H 1250 1600 50  0001 C CNN
	1    1250 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1700 1250 1700
Wire Wire Line
	1250 1700 1250 1600
Wire Wire Line
	1350 1800 1250 1800
Wire Wire Line
	1250 1800 1250 1900
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J2
U 1 1 5FDD64A4
P 3900 5600
F 0 "J2" H 3900 6000 50  0000 C CNN
F 1 "Data" H 3950 6100 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x07_P2.54mm_Horizontal" H 3900 5600 50  0001 C CNN
F 3 "~" H 3900 5600 50  0001 C CNN
F 4 "2-1761605-5" H 3900 5600 50  0001 C CNN "PartNo"
	1    3900 5600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR013
U 1 1 5FDDCA80
P 3600 4500
F 0 "#PWR013" H 3600 4350 50  0001 C CNN
F 1 "+3.3V" H 3615 4673 50  0000 C CNN
F 2 "" H 3600 4500 50  0001 C CNN
F 3 "" H 3600 4500 50  0001 C CNN
	1    3600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5900 4250 5900
Wire Wire Line
	4250 5900 4250 5950
Wire Wire Line
	4350 4600 4350 4050
Text Label 4350 4050 3    50   ~ 0
MOSI
Wire Wire Line
	3200 4600 3200 4000
Text Label 3200 4000 3    50   ~ 0
MISO
Wire Wire Line
	4750 4600 4750 4050
Text Label 4750 4050 3    50   ~ 0
SCK
Wire Wire Line
	3700 5500 3100 5500
Text Label 3100 5500 0    50   ~ 0
CS_LASER
Wire Wire Line
	4200 5500 4750 5500
Text Label 4750 5500 2    50   ~ 0
RST_LASER
Wire Wire Line
	3700 5600 3100 5600
Text Label 3100 5600 0    50   ~ 0
TMP_LASER
Wire Wire Line
	5100 4600 5100 4050
Text Label 5100 4050 3    50   ~ 0
CS_TEC_SET
Wire Wire Line
	2850 4600 2850 4000
Text Label 2850 4000 3    50   ~ 0
CS_TEC_READ
Wire Wire Line
	4050 3050 3500 3050
Text Label 3500 3150 0    50   ~ 0
SCK
Wire Wire Line
	4050 3250 3500 3250
Text Label 3500 3250 0    50   ~ 0
MOSI
Wire Wire Line
	5450 4600 5450 4050
Text Label 5450 4050 3    50   ~ 0
TEC_ENABLE
Wire Wire Line
	4050 3150 3500 3150
Text Label 3500 3050 0    50   ~ 0
CS_TEC_SET
Text Label 3500 2750 0    50   ~ 0
VREF
Wire Wire Line
	5100 2700 5600 2700
Text Label 5600 2700 2    50   ~ 0
TEMPSET1
Wire Wire Line
	7400 3100 7950 3100
Text Label 7950 3100 2    50   ~ 0
TEMPGET1
Wire Wire Line
	6550 3100 5950 3100
Text Label 5950 3100 0    50   ~ 0
CS_TEC_READ
Wire Wire Line
	6550 3200 5950 3200
Text Label 5950 3200 0    50   ~ 0
MOSI
Wire Wire Line
	6550 3300 5950 3300
Text Label 5950 3300 0    50   ~ 0
MISO
Wire Wire Line
	6550 3400 5950 3400
Text Label 5950 3400 0    50   ~ 0
SCK
$Comp
L power:GND #PWR04
U 1 1 5FC5BF55
P 1250 1900
F 0 "#PWR04" H 1250 1650 50  0001 C CNN
F 1 "GND" H 1255 1727 50  0000 C CNN
F 2 "" H 1250 1900 50  0001 C CNN
F 3 "" H 1250 1900 50  0001 C CNN
	1    1250 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5FC5C555
P 4550 3650
F 0 "#PWR016" H 4550 3400 50  0001 C CNN
F 1 "GND" H 4555 3477 50  0000 C CNN
F 2 "" H 4550 3650 50  0001 C CNN
F 3 "" H 4550 3650 50  0001 C CNN
	1    4550 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5FC5CA45
P 4250 5950
F 0 "#PWR015" H 4250 5700 50  0001 C CNN
F 1 "GND" H 4255 5777 50  0000 C CNN
F 2 "" H 4250 5950 50  0001 C CNN
F 3 "" H 4250 5950 50  0001 C CNN
	1    4250 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5FC60F9B
P 7000 3750
F 0 "#PWR023" H 7000 3500 50  0001 C CNN
F 1 "GND" H 7005 3577 50  0000 C CNN
F 2 "" H 7000 3750 50  0001 C CNN
F 3 "" H 7000 3750 50  0001 C CNN
	1    7000 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5FC65353
P 6600 2750
F 0 "#PWR020" H 6600 2500 50  0001 C CNN
F 1 "GND" H 6605 2577 50  0000 C CNN
F 2 "" H 6600 2750 50  0001 C CNN
F 3 "" H 6600 2750 50  0001 C CNN
	1    6600 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5800 4750 5800
Wire Wire Line
	3700 5800 3100 5800
Wire Wire Line
	3700 5900 3100 5900
Text Label 4750 5800 2    50   ~ 0
BAT_VOLT
Text Label 3100 5800 0    50   ~ 0
CHARGE
Text Label 3100 5900 0    50   ~ 0
DATA_13
$Comp
L Device:C C7
U 1 1 5FAA783F
P 6800 2250
F 0 "C7" V 6548 2250 50  0000 C CNN
F 1 "1uF" V 6639 2250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6838 2100 50  0001 C CNN
F 3 "~" H 6800 2250 50  0001 C CNN
F 4 "UMF212B7105KGHT" H 6800 2250 50  0001 C CNN "PartNo"
	1    6800 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 2250 7000 2250
Connection ~ 7000 2250
Wire Wire Line
	7000 2250 7000 2650
Wire Wire Line
	6650 2250 6600 2250
Wire Wire Line
	6600 2250 6600 2650
Connection ~ 6600 2650
$Sheet
S 9000 950  950  900 
U 603D1C0C
F0 "LTC1923Channel" 50
F1 "LTC1923Channel.sch" 50
F2 "VREF" I L 9000 1100 50 
F3 "TEMPSET" I L 9000 1400 50 
F4 "TEMPGET" I L 9000 1550 50 
F5 "ENABLE" I L 9000 1250 50 
F6 "ITECLIM" I L 9000 1700 50 
$EndSheet
Wire Wire Line
	9000 1100 8500 1100
Text Label 8500 1100 0    50   ~ 0
VREF
Wire Wire Line
	9000 1250 8500 1250
Wire Wire Line
	9000 1400 8500 1400
Wire Wire Line
	8500 1550 9000 1550
Text Label 8500 1250 0    50   ~ 0
ENABLE
Text Label 8500 1400 0    50   ~ 0
TEMPSET1
Text Label 8500 1550 0    50   ~ 0
TEMPGET1
$Sheet
S 2600 750  1650 650 
U 6072B10A
F0 "PowerSupply" 50
F1 "PowerSupply.sch" 50
$EndSheet
$Comp
L Symbols:DAC108S085CISQ U2
U 1 1 6078879C
P 4550 3050
F 0 "U2" H 4650 3550 50  0000 C CNN
F 1 "DAC108S085CISQ" H 4950 2550 50  0000 C CNN
F 2 "Package_DFN_QFN:WQFN-16-1EP_4x4mm_P0.5mm_EP2.6x2.6mm_ThermalVias" H 4300 2900 50  0001 C CNN
F 3 "" H 4300 2900 50  0001 C CNN
F 4 "DAC108S085CISQ/NOPB" H 4550 3050 50  0001 C CNN "PartNo"
	1    4550 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2850 3500 2850
Wire Wire Line
	5100 3100 5600 3100
Text Label 5600 3100 2    50   ~ 0
ITECSET1
Wire Wire Line
	9000 1700 8500 1700
Text Label 8500 1700 0    50   ~ 0
ITECSET1
NoConn ~ 4050 3350
$Comp
L Device:C C5
U 1 1 607C8017
P 3850 2150
F 0 "C5" V 3598 2150 50  0000 C CNN
F 1 "1uF" V 3689 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3888 2000 50  0001 C CNN
F 3 "~" H 3850 2150 50  0001 C CNN
F 4 "UMF212B7105KGHT" H 3850 2150 50  0001 C CNN "PartNo"
	1    3850 2150
	-1   0    0    1   
$EndComp
$Comp
L Regulator_Linear:LP2985-3.0 U1
U 1 1 607CCD82
P 2900 1950
F 0 "U1" H 2900 2292 50  0000 C CNN
F 1 "LP3985-3.0" H 2900 2201 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 2900 2275 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lp2985.pdf" H 2900 1950 50  0001 C CNN
F 4 "LP3985IM5X-3.0/NOPB" H 2900 1950 50  0001 C CNN "PartNo"
	1    2900 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 607DC292
P 2400 2150
F 0 "C2" V 2148 2150 50  0000 C CNN
F 1 "1uF" V 2239 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2438 2000 50  0001 C CNN
F 3 "~" H 2400 2150 50  0001 C CNN
F 4 "UMF212B7105KGHT" H 2400 2150 50  0001 C CNN "PartNo"
	1    2400 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 607DD7DB
P 3400 2150
F 0 "C4" V 3148 2150 50  0000 C CNN
F 1 "1uF" V 3239 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3438 2000 50  0001 C CNN
F 3 "~" H 3400 2150 50  0001 C CNN
F 4 "UMF212B7105KGHT" H 3400 2150 50  0001 C CNN "PartNo"
	1    3400 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	3300 1950 3400 1950
Wire Wire Line
	3400 1950 3400 2000
Wire Wire Line
	2900 2250 2900 2350
$Comp
L power:GND #PWR09
U 1 1 607E746F
P 2900 2400
F 0 "#PWR09" H 2900 2150 50  0001 C CNN
F 1 "GND" H 2905 2227 50  0000 C CNN
F 2 "" H 2900 2400 50  0001 C CNN
F 3 "" H 2900 2400 50  0001 C CNN
	1    2900 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2300 3400 2350
Wire Wire Line
	3400 2350 2900 2350
Connection ~ 2900 2350
Wire Wire Line
	2900 2350 2900 2400
Wire Wire Line
	2900 2350 2400 2350
Wire Wire Line
	2400 2350 2400 2300
Wire Wire Line
	2400 2000 2400 1950
Wire Wire Line
	2400 1850 2500 1850
Wire Wire Line
	2500 1950 2400 1950
Connection ~ 2400 1950
Wire Wire Line
	2400 1950 2400 1850
Wire Wire Line
	2400 1850 2400 1550
Connection ~ 2400 1850
$Comp
L power:+5V #PWR07
U 1 1 607F2EAC
P 2400 1550
F 0 "#PWR07" H 2400 1400 50  0001 C CNN
F 1 "+5V" H 2415 1723 50  0000 C CNN
F 2 "" H 2400 1550 50  0001 C CNN
F 3 "" H 2400 1550 50  0001 C CNN
	1    2400 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2350 3850 2350
Wire Wire Line
	4250 2350 4250 2300
Connection ~ 3400 2350
Wire Wire Line
	3850 2300 3850 2350
Connection ~ 3850 2350
Wire Wire Line
	3850 2350 4250 2350
Wire Wire Line
	4550 1850 4550 2500
Wire Wire Line
	3300 1850 3850 1850
Wire Wire Line
	4250 2000 4250 1850
Connection ~ 4250 1850
Wire Wire Line
	4250 1850 4550 1850
Wire Wire Line
	3850 2000 3850 1850
Connection ~ 3850 1850
Wire Wire Line
	3850 1850 4250 1850
NoConn ~ 4750 5800
NoConn ~ 4750 5500
NoConn ~ 3100 5500
NoConn ~ 3100 5600
NoConn ~ 3100 5800
NoConn ~ 3100 5900
$Comp
L power:PWR_FLAG #FLG03
U 1 1 613286F4
P 1700 850
F 0 "#FLG03" H 1700 925 50  0001 C CNN
F 1 "PWR_FLAG" H 1700 1023 50  0000 C CNN
F 2 "" H 1700 850 50  0001 C CNN
F 3 "~" H 1700 850 50  0001 C CNN
	1    1700 850 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 61328E7F
P 1700 950
F 0 "#PWR05" H 1700 700 50  0001 C CNN
F 1 "GND" H 1705 777 50  0000 C CNN
F 2 "" H 1700 950 50  0001 C CNN
F 3 "" H 1700 950 50  0001 C CNN
	1    1700 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 850  1700 950 
$Comp
L Device:EMI_Filter_CLC FL3
U 1 1 61B80F03
P 3500 4900
F 0 "FL3" H 3350 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 3500 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 3500 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 3500 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 3500 4900 50  0001 C CNN "PartNo"
	1    3500 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	3700 5300 3600 5300
Wire Wire Line
	3600 5300 3600 5200
$Comp
L power:GND #PWR012
U 1 1 61C0538B
P 3400 4900
F 0 "#PWR012" H 3400 4650 50  0001 C CNN
F 1 "GND" H 3405 4727 50  0000 C CNN
F 2 "" H 3400 4900 50  0001 C CNN
F 3 "" H 3400 4900 50  0001 C CNN
	1    3400 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:EMI_Filter_CLC FL2
U 1 1 61C0787E
P 3100 4900
F 0 "FL2" H 2950 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 3100 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 3100 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 3100 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 3100 4900 50  0001 C CNN "PartNo"
	1    3100 4900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 61C078E8
P 3000 4900
F 0 "#PWR010" H 3000 4650 50  0001 C CNN
F 1 "GND" H 3005 4727 50  0000 C CNN
F 2 "" H 3000 4900 50  0001 C CNN
F 3 "" H 3000 4900 50  0001 C CNN
	1    3000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5400 3200 5400
Wire Wire Line
	3200 5400 3200 5200
$Comp
L Device:EMI_Filter_CLC FL1
U 1 1 61C1A92A
P 2750 4900
F 0 "FL1" H 2600 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 2750 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 2750 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 2750 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 2750 4900 50  0001 C CNN "PartNo"
	1    2750 4900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 61C1A964
P 2650 4900
F 0 "#PWR08" H 2650 4650 50  0001 C CNN
F 1 "GND" H 2655 4727 50  0000 C CNN
F 2 "" H 2650 4900 50  0001 C CNN
F 3 "" H 2650 4900 50  0001 C CNN
	1    2650 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5700 2850 5700
Wire Wire Line
	2850 5200 2850 5700
$Comp
L Device:EMI_Filter_CLC FL4
U 1 1 61C39439
P 4250 4900
F 0 "FL4" H 4100 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 4250 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 4250 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 4250 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 4250 4900 50  0001 C CNN "PartNo"
	1    4250 4900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 61C39473
P 4150 4900
F 0 "#PWR014" H 4150 4650 50  0001 C CNN
F 1 "GND" H 4155 4727 50  0000 C CNN
F 2 "" H 4150 4900 50  0001 C CNN
F 3 "" H 4150 4900 50  0001 C CNN
	1    4150 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5300 4350 5300
Wire Wire Line
	4350 5300 4350 5200
$Comp
L Device:EMI_Filter_CLC FL5
U 1 1 61C48D7D
P 4650 4900
F 0 "FL5" H 4500 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 4650 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 4650 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 4650 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 4650 4900 50  0001 C CNN "PartNo"
	1    4650 4900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 61C48DE7
P 4550 4900
F 0 "#PWR017" H 4550 4650 50  0001 C CNN
F 1 "GND" H 4555 4727 50  0000 C CNN
F 2 "" H 4550 4900 50  0001 C CNN
F 3 "" H 4550 4900 50  0001 C CNN
	1    4550 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5400 4750 5400
Wire Wire Line
	4750 5400 4750 5200
$Comp
L Device:EMI_Filter_CLC FL6
U 1 1 61C543CF
P 5000 4900
F 0 "FL6" H 4850 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 5000 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 5000 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 5000 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 5000 4900 50  0001 C CNN "PartNo"
	1    5000 4900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 61C54439
P 4900 4900
F 0 "#PWR018" H 4900 4650 50  0001 C CNN
F 1 "GND" H 4905 4727 50  0000 C CNN
F 2 "" H 4900 4900 50  0001 C CNN
F 3 "" H 4900 4900 50  0001 C CNN
	1    4900 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5600 5100 5600
Wire Wire Line
	5100 5600 5100 5200
$Comp
L Device:EMI_Filter_CLC FL7
U 1 1 61C60B92
P 5350 4900
F 0 "FL7" H 5200 4800 50  0000 C CNN
F 1 "NFL21SP206X1C7D" H 5350 5126 50  0001 C CNN
F 2 "pepin-footprints:EMI_805" V 5350 4900 50  0001 C CNN
F 3 "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb" V 5350 4900 50  0001 C CNN
F 4 "NFL21SP206X1C7D" H 5350 4900 50  0001 C CNN "PartNo"
	1    5350 4900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 61C60BFC
P 5250 4900
F 0 "#PWR019" H 5250 4650 50  0001 C CNN
F 1 "GND" H 5255 4727 50  0000 C CNN
F 2 "" H 5250 4900 50  0001 C CNN
F 3 "" H 5250 4900 50  0001 C CNN
	1    5250 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 5700 5450 5700
Wire Wire Line
	5450 5700 5450 5200
$Comp
L Device:R R?
U 1 1 620A8395
P 2800 3150
AR Path="/603D1C0C/620A8395" Ref="R?"  Part="1" 
AR Path="/620A8395" Ref="R2"  Part="1" 
F 0 "R2" V 2593 3150 50  0000 C CNN
F 1 "10k" V 2684 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2730 3150 50  0001 C CNN
F 3 "~" H 2800 3150 50  0001 C CNN
F 4 "AC0805FR-0710KL" H 2800 3150 50  0001 C CNN "PartNo"
	1    2800 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 620A839B
P 2400 3150
AR Path="/603D1C0C/620A839B" Ref="R?"  Part="1" 
AR Path="/620A839B" Ref="R1"  Part="1" 
F 0 "R1" V 2193 3150 50  0000 C CNN
F 1 "10k" V 2284 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2330 3150 50  0001 C CNN
F 3 "~" H 2400 3150 50  0001 C CNN
F 4 "AC0805FR-0710KL" H 2400 3150 50  0001 C CNN "PartNo"
	1    2400 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2550 3150 2600 3150
Wire Wire Line
	2600 2800 2600 3150
Connection ~ 2600 3150
Wire Wire Line
	2600 3150 2650 3150
Wire Wire Line
	2950 3150 3100 3150
Wire Wire Line
	3100 3150 3100 3200
$Comp
L power:GND #PWR?
U 1 1 620A83A7
P 3100 3200
AR Path="/603D1C0C/620A83A7" Ref="#PWR?"  Part="1" 
AR Path="/620A83A7" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 3100 2950 50  0001 C CNN
F 1 "GND" H 3105 3027 50  0000 C CNN
F 2 "" H 3100 3200 50  0001 C CNN
F 3 "" H 3100 3200 50  0001 C CNN
	1    3100 3200
	1    0    0    -1  
$EndComp
Text Label 2050 3150 0    50   ~ 0
VREF
Wire Wire Line
	2600 2800 3100 2800
Text Label 2800 2800 2    50   ~ 0
VREF2
Wire Wire Line
	3500 2750 4050 2750
Text Label 3500 2850 0    50   ~ 0
VREF2
$Comp
L Device:C C3
U 1 1 620CBE3D
P 3100 2950
F 0 "C3" V 2848 2950 50  0000 C CNN
F 1 ".1uF" V 2939 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3138 2800 50  0001 C CNN
F 3 "~" H 3100 2950 50  0001 C CNN
F 4 "VJ0805Y104KXXAT" H 3100 2950 50  0001 C CNN "PartNo"
	1    3100 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 3100 3100 3150
Connection ~ 3100 3150
$Comp
L Device:C C1
U 1 1 620DE60C
P 2000 3350
F 0 "C1" V 1748 3350 50  0000 C CNN
F 1 ".1uF" V 1839 3350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2038 3200 50  0001 C CNN
F 3 "~" H 2000 3350 50  0001 C CNN
F 4 "VJ0805Y104KXXAT" H 2000 3350 50  0001 C CNN "PartNo"
	1    2000 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 3150 2000 3200
Wire Wire Line
	2000 3150 2250 3150
Wire Wire Line
	2000 3500 2000 3550
$Comp
L power:GND #PWR?
U 1 1 620E845D
P 2000 3550
AR Path="/603D1C0C/620E845D" Ref="#PWR?"  Part="1" 
AR Path="/620E845D" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 2000 3300 50  0001 C CNN
F 1 "GND" H 2005 3377 50  0000 C CNN
F 2 "" H 2000 3550 50  0001 C CNN
F 3 "" H 2000 3550 50  0001 C CNN
	1    2000 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 62169ED9
P 7000 4500
AR Path="/603D1C0C/62169ED9" Ref="R?"  Part="1" 
AR Path="/62169ED9" Ref="R4"  Part="1" 
F 0 "R4" V 6793 4500 50  0000 C CNN
F 1 "100k" V 6884 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6930 4500 50  0001 C CNN
F 3 "~" H 7000 4500 50  0001 C CNN
F 4 "RC0805FR-07100KL" H 7000 4500 50  0001 C CNN "PartNo"
	1    7000 4500
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62169EDF
P 7000 4250
AR Path="/603D1C0C/62169EDF" Ref="#PWR?"  Part="1" 
AR Path="/62169EDF" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 7000 4100 50  0001 C CNN
F 1 "+5V" H 7015 4423 50  0000 C CNN
F 2 "" H 7000 4250 50  0001 C CNN
F 3 "" H 7000 4250 50  0001 C CNN
	1    7000 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62169EE5
P 7550 5400
AR Path="/603D1C0C/62169EE5" Ref="#PWR?"  Part="1" 
AR Path="/62169EE5" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 7550 5150 50  0001 C CNN
F 1 "GND" H 7555 5227 50  0000 C CNN
F 2 "" H 7550 5400 50  0001 C CNN
F 3 "" H 7550 5400 50  0001 C CNN
	1    7550 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 62169EEC
P 7550 4500
AR Path="/603D1C0C/62169EEC" Ref="R?"  Part="1" 
AR Path="/62169EEC" Ref="R5"  Part="1" 
F 0 "R5" V 7343 4500 50  0000 C CNN
F 1 "100k" V 7434 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7480 4500 50  0001 C CNN
F 3 "~" H 7550 4500 50  0001 C CNN
F 4 "RC0805FR-07100KL" H 7550 4500 50  0001 C CNN "PartNo"
	1    7550 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7550 4800 7550 4750
Wire Wire Line
	7550 4750 7950 4750
Connection ~ 7550 4750
Wire Wire Line
	7550 4750 7550 4650
Text Label 7950 4750 2    50   ~ 0
ENABLE
Wire Wire Line
	7550 4350 7550 4300
Wire Wire Line
	7550 4300 7000 4300
Wire Wire Line
	7000 4300 7000 4250
Wire Wire Line
	7000 4300 7000 4350
Connection ~ 7000 4300
Wire Wire Line
	7000 4650 7000 4750
Wire Wire Line
	6700 5200 6700 5400
$Comp
L power:GND #PWR?
U 1 1 62169EFF
P 6700 5450
AR Path="/603D1C0C/62169EFF" Ref="#PWR?"  Part="1" 
AR Path="/62169EFF" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 6700 5200 50  0001 C CNN
F 1 "GND" H 6705 5277 50  0000 C CNN
F 2 "" H 6700 5450 50  0001 C CNN
F 3 "" H 6700 5450 50  0001 C CNN
	1    6700 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 4800 6700 4750
Wire Wire Line
	6700 4750 7000 4750
Connection ~ 7000 4750
Wire Wire Line
	7000 4750 7000 5000
$Comp
L Device:R R?
U 1 1 62169F09
P 6300 5200
AR Path="/603D1C0C/62169F09" Ref="R?"  Part="1" 
AR Path="/62169F09" Ref="R3"  Part="1" 
F 0 "R3" V 6093 5200 50  0000 C CNN
F 1 "100k" V 6184 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6230 5200 50  0001 C CNN
F 3 "~" H 6300 5200 50  0001 C CNN
F 4 "RC0805FR-07100KL" H 6300 5200 50  0001 C CNN "PartNo"
	1    6300 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 5000 6300 5000
Wire Wire Line
	6300 5000 6300 5050
Wire Wire Line
	6300 5350 6300 5400
Wire Wire Line
	6300 5400 6700 5400
Connection ~ 6700 5400
Wire Wire Line
	6700 5400 6700 5450
Wire Wire Line
	6300 5000 5900 5000
Connection ~ 6300 5000
Text Label 5900 5000 0    50   ~ 0
TEC_ENABLE
$Comp
L Transistor_FET:2N7002 Q?
U 1 1 62169F18
P 6600 5000
AR Path="/603D1C0C/62169F18" Ref="Q?"  Part="1" 
AR Path="/62169F18" Ref="Q1"  Part="1" 
F 0 "Q1" H 6804 5046 50  0000 L CNN
F 1 "2N7002PW" H 6804 4955 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 6800 4925 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 6600 5000 50  0001 L CNN
F 4 "2N7002PW,115" H 6600 5000 50  0001 C CNN "PartNo"
	1    6600 5000
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7002 Q?
U 1 1 62169F1E
P 7450 5000
AR Path="/603D1C0C/62169F1E" Ref="Q?"  Part="1" 
AR Path="/62169F1E" Ref="Q2"  Part="1" 
F 0 "Q2" H 7654 5046 50  0000 L CNN
F 1 "2N7002PW" H 7654 4955 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 7650 4925 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 7450 5000 50  0001 L CNN
F 4 "2N7002PW,115" H 7450 5000 50  0001 C CNN "PartNo"
	1    7450 5000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 607B2808
P 9250 6450
F 0 "H1" H 9350 6453 50  0000 L CNN
F 1 "MountingHole_Pad" H 9350 6408 50  0001 L CNN
F 2 "MountingHole:MountingHole_3mm_Pad_Via" H 9250 6450 50  0001 C CNN
F 3 "~" H 9250 6450 50  0001 C CNN
	1    9250 6450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 607B2F7E
P 9550 6450
F 0 "H2" H 9650 6453 50  0000 L CNN
F 1 "MountingHole_Pad" H 9650 6408 50  0001 L CNN
F 2 "MountingHole:MountingHole_3mm_Pad_Via" H 9550 6450 50  0001 C CNN
F 3 "~" H 9550 6450 50  0001 C CNN
	1    9550 6450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 607B32D7
P 9850 6450
F 0 "H3" H 9950 6453 50  0000 L CNN
F 1 "MountingHole_Pad" H 9950 6408 50  0001 L CNN
F 2 "MountingHole:MountingHole_3mm_Pad_Via" H 9850 6450 50  0001 C CNN
F 3 "~" H 9850 6450 50  0001 C CNN
	1    9850 6450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 607B3773
P 10150 6450
F 0 "H4" H 10250 6453 50  0000 L CNN
F 1 "MountingHole_Pad" H 10250 6408 50  0001 L CNN
F 2 "MountingHole:MountingHole_3mm_Pad_Via" H 10150 6450 50  0001 C CNN
F 3 "~" H 10150 6450 50  0001 C CNN
	1    10150 6450
	1    0    0    -1  
$EndComp
NoConn ~ 9250 6550
NoConn ~ 9550 6550
NoConn ~ 9850 6550
NoConn ~ 10150 6550
Wire Wire Line
	7000 5000 7250 5000
Wire Wire Line
	7550 5200 7550 5400
Wire Wire Line
	3600 4600 3600 4500
$Sheet
S 9000 2100 950  900 
U 609B3708
F0 "sheet609B3708" 50
F1 "LTC1923Channel.sch" 50
F2 "VREF" I L 9000 2250 50 
F3 "TEMPSET" I L 9000 2550 50 
F4 "TEMPGET" I L 9000 2700 50 
F5 "ENABLE" I L 9000 2400 50 
F6 "ITECLIM" I L 9000 2850 50 
$EndSheet
Wire Wire Line
	9000 2400 8500 2400
Wire Wire Line
	9000 2550 8500 2550
Wire Wire Line
	8500 2700 9000 2700
Text Label 8500 2400 0    50   ~ 0
ENABLE
Text Label 8500 2550 0    50   ~ 0
TEMPSET2
Text Label 8500 2700 0    50   ~ 0
TEMPGET2
Wire Wire Line
	9000 2850 8500 2850
Text Label 8500 2850 0    50   ~ 0
ITECSET2
$Sheet
S 9000 3250 950  900 
U 609BE7FC
F0 "sheet609BE7FC" 50
F1 "LTC1923Channel.sch" 50
F2 "VREF" I L 9000 3400 50 
F3 "TEMPSET" I L 9000 3700 50 
F4 "TEMPGET" I L 9000 3850 50 
F5 "ENABLE" I L 9000 3550 50 
F6 "ITECLIM" I L 9000 4000 50 
$EndSheet
Wire Wire Line
	9000 3550 8500 3550
Wire Wire Line
	9000 3700 8500 3700
Wire Wire Line
	8500 3850 9000 3850
Text Label 8500 3550 0    50   ~ 0
ENABLE
Text Label 8500 3700 0    50   ~ 0
TEMPSET3
Text Label 8500 3850 0    50   ~ 0
TEMPGET3
Wire Wire Line
	9000 4000 8500 4000
Text Label 8500 4000 0    50   ~ 0
ITECSET3
$Sheet
S 9000 4400 950  900 
U 609C9431
F0 "sheet609C9431" 50
F1 "LTC1923Channel.sch" 50
F2 "VREF" I L 9000 4550 50 
F3 "TEMPSET" I L 9000 4850 50 
F4 "TEMPGET" I L 9000 5000 50 
F5 "ENABLE" I L 9000 4700 50 
F6 "ITECLIM" I L 9000 5150 50 
$EndSheet
Wire Wire Line
	9000 4700 8500 4700
Wire Wire Line
	9000 4850 8500 4850
Wire Wire Line
	8500 5000 9000 5000
Text Label 8500 4700 0    50   ~ 0
ENABLE
Text Label 8500 4850 0    50   ~ 0
TEMPSET4
Text Label 8500 5000 0    50   ~ 0
TEMPGET4
Wire Wire Line
	9000 5150 8500 5150
Text Label 8500 5150 0    50   ~ 0
ITECSET4
Wire Wire Line
	7000 3600 7000 3750
Wire Wire Line
	7400 3200 7950 3200
Text Label 7950 3200 2    50   ~ 0
TEMPGET2
Wire Wire Line
	7400 3300 7950 3300
Text Label 7950 3300 2    50   ~ 0
TEMPGET3
Wire Wire Line
	7400 3400 7950 3400
Text Label 7950 3400 2    50   ~ 0
TEMPGET4
Wire Wire Line
	5100 2800 5600 2800
Text Label 5600 2800 2    50   ~ 0
TEMPSET2
Wire Wire Line
	5100 2900 5600 2900
Text Label 5600 2900 2    50   ~ 0
TEMPSET3
Wire Wire Line
	5100 3000 5600 3000
Text Label 5600 3000 2    50   ~ 0
TEMPSET4
Wire Wire Line
	5100 3200 5600 3200
Text Label 5600 3200 2    50   ~ 0
ITECSET2
Wire Wire Line
	5100 3300 5600 3300
Text Label 5600 3300 2    50   ~ 0
ITECSET3
Wire Wire Line
	5100 3400 5600 3400
Text Label 5600 3400 2    50   ~ 0
ITECSET4
$EndSCHEMATC