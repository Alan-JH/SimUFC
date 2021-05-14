EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 5300 3850
Wire Wire Line
	5300 3850 4850 3850
Connection ~ 5750 3850
Wire Wire Line
	5750 3850 5300 3850
Connection ~ 6200 3850
Wire Wire Line
	6200 3850 5750 3850
Wire Wire Line
	6650 3850 6200 3850
$Comp
L Switch:SW_SPST SW1
U 1 1 60A18B28
P 4850 3650
AR Path="/60A18B28" Ref="SW1"  Part="1" 
AR Path="/60A14FF3/60A18B28" Ref="SW18"  Part="1" 
F 0 "SW18" H 4850 3885 50  0000 C CNN
F 1 "KeySW" H 4850 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 4850 3650 50  0001 C CNN
F 3 "~" H 4850 3650 50  0001 C CNN
	1    4850 3650
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW2
U 1 1 60A18B2E
P 5300 3650
AR Path="/60A18B2E" Ref="SW2"  Part="1" 
AR Path="/60A14FF3/60A18B2E" Ref="SW19"  Part="1" 
F 0 "SW19" H 5300 3885 50  0000 C CNN
F 1 "KeySW" H 5300 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 5300 3650 50  0001 C CNN
F 3 "~" H 5300 3650 50  0001 C CNN
	1    5300 3650
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW3
U 1 1 60A18B34
P 5750 3650
AR Path="/60A18B34" Ref="SW3"  Part="1" 
AR Path="/60A14FF3/60A18B34" Ref="SW20"  Part="1" 
F 0 "SW20" H 5750 3885 50  0000 C CNN
F 1 "KeySW" H 5750 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 5750 3650 50  0001 C CNN
F 3 "~" H 5750 3650 50  0001 C CNN
	1    5750 3650
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW4
U 1 1 60A18B3A
P 6200 3650
AR Path="/60A18B3A" Ref="SW4"  Part="1" 
AR Path="/60A14FF3/60A18B3A" Ref="SW21"  Part="1" 
F 0 "SW21" H 6200 3885 50  0000 C CNN
F 1 "KeySW" H 6200 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 6200 3650 50  0001 C CNN
F 3 "~" H 6200 3650 50  0001 C CNN
	1    6200 3650
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW5
U 1 1 60A18B40
P 6650 3650
AR Path="/60A18B40" Ref="SW5"  Part="1" 
AR Path="/60A14FF3/60A18B40" Ref="SW22"  Part="1" 
F 0 "SW22" H 6650 3885 50  0000 C CNN
F 1 "KeySW" H 6650 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 6650 3650 50  0001 C CNN
F 3 "~" H 6650 3650 50  0001 C CNN
	1    6650 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 3850 7100 3850
$Comp
L Switch:SW_SPST SW6
U 1 1 60A18B47
P 7100 3650
AR Path="/60A18B47" Ref="SW6"  Part="1" 
AR Path="/60A14FF3/60A18B47" Ref="SW23"  Part="1" 
F 0 "SW23" H 7100 3885 50  0000 C CNN
F 1 "KeySW" H 7100 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 7100 3650 50  0001 C CNN
F 3 "~" H 7100 3650 50  0001 C CNN
	1    7100 3650
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW7
U 1 1 60A18B4D
P 7550 3650
AR Path="/60A18B4D" Ref="SW7"  Part="1" 
AR Path="/60A14FF3/60A18B4D" Ref="SW24"  Part="1" 
F 0 "SW24" H 7550 3885 50  0000 C CNN
F 1 "KeySW" H 7550 3794 50  0000 C CNN
F 2 "Keypad:KailhSW" H 7550 3650 50  0001 C CNN
F 3 "~" H 7550 3650 50  0001 C CNN
	1    7550 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 3850 7100 3850
Connection ~ 6650 3850
Connection ~ 7100 3850
Wire Wire Line
	4850 3450 3850 3450
Wire Wire Line
	5300 3450 5300 3400
Wire Wire Line
	5750 3450 5750 3350
Wire Wire Line
	6200 3450 6200 3300
Wire Wire Line
	6650 3450 6650 3250
Wire Wire Line
	7100 3450 7100 3200
Wire Wire Line
	7550 3450 7550 3150
Connection ~ 4850 3850
Text Label 7300 3150 0    50   ~ 0
SW24
Text Label 6850 3200 0    50   ~ 0
SW23
Text Label 6350 3250 0    50   ~ 0
SW22
Text Label 5800 3300 0    50   ~ 0
SW21
Text Label 5450 3350 0    50   ~ 0
SW20
Text Label 5050 3400 0    50   ~ 0
SW19
Text Label 4650 3450 0    50   ~ 0
SW18
Wire Wire Line
	3550 3300 6200 3300
Wire Wire Line
	3450 3250 6650 3250
Wire Wire Line
	3350 3200 7100 3200
Wire Wire Line
	3150 3150 7550 3150
Text Label 3950 3850 0    50   ~ 0
GND
Text HLabel 3850 3150 1    50   Input ~ 0
SW24
Text HLabel 4050 3200 1    50   Input ~ 0
SW23
Text HLabel 4200 3250 1    50   Input ~ 0
SW22
Text HLabel 4300 3300 1    50   Input ~ 0
SW21
Text HLabel 4450 3350 1    50   Input ~ 0
SW20
Text HLabel 4550 3400 1    50   Input ~ 0
SW19
Text HLabel 4650 3450 1    50   Input ~ 0
SW18
Text HLabel 4350 3850 1    50   Input ~ 0
GND
Wire Wire Line
	2750 3850 3700 3850
Wire Wire Line
	2750 3750 3150 3750
Wire Wire Line
	3150 3750 3150 3150
Wire Wire Line
	2750 3650 3350 3650
Wire Wire Line
	3350 3650 3350 3200
Wire Wire Line
	2750 3550 3450 3550
Wire Wire Line
	3450 3550 3450 3250
Wire Wire Line
	2750 3450 3550 3450
Wire Wire Line
	3550 3450 3550 3300
Wire Wire Line
	2750 3350 5750 3350
Wire Wire Line
	2750 3250 3200 3250
Wire Wire Line
	3200 3250 3200 3400
Wire Wire Line
	3200 3400 5300 3400
Wire Wire Line
	2750 3150 3050 3150
Wire Wire Line
	3050 3150 3050 3500
Wire Wire Line
	3050 3500 3850 3500
Wire Wire Line
	3850 3500 3850 3450
$Comp
L Device:LED D35
U 1 1 60A25224
P 3900 2450
F 0 "D35" V 3939 2332 50  0000 R CNN
F 1 "LED" V 3848 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 2450 50  0001 C CNN
F 3 "~" H 3900 2450 50  0001 C CNN
	1    3900 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D36
U 1 1 60A26034
P 4250 2450
F 0 "D36" V 4289 2332 50  0000 R CNN
F 1 "LED" V 4198 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4250 2450 50  0001 C CNN
F 3 "~" H 4250 2450 50  0001 C CNN
	1    4250 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D37
U 1 1 60A268FA
P 4600 2450
F 0 "D37" V 4639 2332 50  0000 R CNN
F 1 "LED" V 4548 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4600 2450 50  0001 C CNN
F 3 "~" H 4600 2450 50  0001 C CNN
	1    4600 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D38
U 1 1 60A272DB
P 4950 2450
F 0 "D38" V 4989 2332 50  0000 R CNN
F 1 "LED" V 4898 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4950 2450 50  0001 C CNN
F 3 "~" H 4950 2450 50  0001 C CNN
	1    4950 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D39
U 1 1 60A27E76
P 5300 2450
F 0 "D39" V 5339 2332 50  0000 R CNN
F 1 "LED" V 5248 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5300 2450 50  0001 C CNN
F 3 "~" H 5300 2450 50  0001 C CNN
	1    5300 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D40
U 1 1 60A28917
P 5650 2450
F 0 "D40" V 5689 2332 50  0000 R CNN
F 1 "LED" V 5598 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5650 2450 50  0001 C CNN
F 3 "~" H 5650 2450 50  0001 C CNN
	1    5650 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D41
U 1 1 60A29133
P 6000 2450
F 0 "D41" V 6039 2332 50  0000 R CNN
F 1 "LED" V 5948 2332 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6000 2450 50  0001 C CNN
F 3 "~" H 6000 2450 50  0001 C CNN
	1    6000 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6000 2300 5650 2300
Connection ~ 3900 2300
Connection ~ 4250 2300
Wire Wire Line
	4250 2300 3900 2300
Connection ~ 4600 2300
Wire Wire Line
	4600 2300 4250 2300
Connection ~ 4950 2300
Wire Wire Line
	4950 2300 4600 2300
Connection ~ 5300 2300
Wire Wire Line
	5300 2300 4950 2300
Connection ~ 5650 2300
Wire Wire Line
	5650 2300 5300 2300
Wire Wire Line
	6000 2600 5650 2600
Connection ~ 3900 2600
Connection ~ 4250 2600
Wire Wire Line
	4250 2600 3900 2600
Connection ~ 4600 2600
Wire Wire Line
	4600 2600 4250 2600
Connection ~ 4950 2600
Wire Wire Line
	4950 2600 4600 2600
Connection ~ 5300 2600
Wire Wire Line
	5300 2600 4950 2600
Connection ~ 5650 2600
Wire Wire Line
	5650 2600 5300 2600
$Comp
L Connector:Conn_01x09_Male J2
U 1 1 60A2D5EF
P 2550 3450
F 0 "J2" H 2658 4031 50  0000 C CNN
F 1 "9pin" H 2658 3940 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x09_P2.54mm_Vertical" H 2550 3450 50  0001 C CNN
F 3 "~" H 2550 3450 50  0001 C CNN
	1    2550 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3850 3700 2600
Wire Wire Line
	3700 2600 3900 2600
Connection ~ 3700 3850
Wire Wire Line
	3700 3850 4850 3850
Wire Wire Line
	3100 2300 3100 3050
Wire Wire Line
	3100 3050 2750 3050
Wire Wire Line
	3100 2300 3900 2300
Text Label 3250 2300 0    50   ~ 0
LEDPWM
Text HLabel 3100 2800 0    50   Input ~ 0
LED
$EndSCHEMATC
