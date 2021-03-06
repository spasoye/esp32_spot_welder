EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR04
U 1 1 5E8FD74C
P 3150 2450
F 0 "#PWR04" H 3150 2300 50  0001 C CNN
F 1 "+5V" H 3165 2623 50  0000 C CNN
F 2 "" H 3150 2450 50  0001 C CNN
F 3 "" H 3150 2450 50  0001 C CNN
	1    3150 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5E906D77
P 2850 2450
F 0 "#PWR03" H 2850 2300 50  0001 C CNN
F 1 "+5V" H 2865 2623 50  0000 C CNN
F 2 "" H 2850 2450 50  0001 C CNN
F 3 "" H 2850 2450 50  0001 C CNN
	1    2850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2450 3150 4700
Wire Wire Line
	3150 4700 3650 4700
$Comp
L power:GND #PWR0101
U 1 1 5E91912E
P 2950 4750
F 0 "#PWR0101" H 2950 4500 50  0001 C CNN
F 1 "GND" H 2955 4577 50  0000 C CNN
F 2 "" H 2950 4750 50  0001 C CNN
F 3 "" H 2950 4750 50  0001 C CNN
	1    2950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 4750 2950 4200
Wire Wire Line
	2950 4200 3650 4200
$Comp
L esp32_spot_welder-rescue:ESP32-DEVKITC-32D-ESP32-DEVKITC-32D U2
U 1 1 5E8F78B8
P 4450 3800
F 0 "U2" H 4450 4967 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 4450 4876 50  0000 C CNN
F 2 "ESP32-DEVKITC-32D:MODULE_ESP32-DEVKITC-32D" H 4450 3800 50  0001 L BNN
F 3 "4" H 4450 3800 50  0001 L BNN
F 4 "Espressif Systems" H 4450 3800 50  0001 L BNN "Field4"
	1    4450 3800
	1    0    0    -1  
$EndComp
NoConn ~ 5250 3000
NoConn ~ 5250 3200
NoConn ~ 5250 3400
NoConn ~ 5250 3500
NoConn ~ 5250 3700
NoConn ~ 5250 3800
NoConn ~ 5250 3900
NoConn ~ 5250 4100
NoConn ~ 5250 4200
NoConn ~ 5250 4300
NoConn ~ 5250 4400
NoConn ~ 5250 4500
NoConn ~ 5250 4600
NoConn ~ 5250 4700
NoConn ~ 3650 3000
NoConn ~ 3650 3100
NoConn ~ 3650 3200
NoConn ~ 3650 3300
NoConn ~ 3650 3400
NoConn ~ 3650 3700
NoConn ~ 3650 3800
NoConn ~ 3650 4000
NoConn ~ 3650 4100
NoConn ~ 3650 4300
NoConn ~ 3650 4400
NoConn ~ 3650 4500
NoConn ~ 3650 4600
Text GLabel 5250 3100 2    50   Input ~ 0
LCD_SCL
Text GLabel 5250 3300 2    50   Input ~ 0
LCD_SDA
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 5E93ACE9
P 7900 2800
F 0 "J2" H 7928 2776 50  0000 L CNN
F 1 "LCD_PINS" H 7928 2685 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x04_P2.00mm_Vertical" H 7900 2800 50  0001 C CNN
F 3 "~" H 7900 2800 50  0001 C CNN
	1    7900 2800
	1    0    0    -1  
$EndComp
Text GLabel 7700 3000 0    50   Input ~ 0
LCD_SCL
Text GLabel 7700 2900 0    50   Input ~ 0
LCD_SDA
$Comp
L Connector:Conn_01x05_Female J3
U 1 1 5E9ED026
P 7900 4050
F 0 "J3" H 7928 4076 50  0000 L CNN
F 1 "ROT_ENCD" H 7928 3985 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x05_P2.00mm_Vertical" H 7900 4050 50  0001 C CNN
F 3 "~" H 7900 4050 50  0001 C CNN
	1    7900 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E9F066C
P 7150 3750
F 0 "#PWR0104" H 7150 3500 50  0001 C CNN
F 1 "GND" H 7155 3577 50  0000 C CNN
F 2 "" H 7150 3750 50  0001 C CNN
F 3 "" H 7150 3750 50  0001 C CNN
	1    7150 3750
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0105
U 1 1 5E9F0FE9
P 7150 3950
F 0 "#PWR0105" H 7150 3800 50  0001 C CNN
F 1 "+3.3V" H 7165 4123 50  0000 C CNN
F 2 "" H 7150 3950 50  0001 C CNN
F 3 "" H 7150 3950 50  0001 C CNN
	1    7150 3950
	-1   0    0    1   
$EndComp
Text GLabel 7700 4250 0    50   Input ~ 0
ENC_CLK
Text GLabel 7700 4150 0    50   Input ~ 0
ENC_DT
Text GLabel 7700 4050 0    50   Input ~ 0
ENC_SW
Text GLabel 3650 3500 0    50   Input ~ 0
ENC_CLK
Text GLabel 3650 3600 0    50   Input ~ 0
ENC_DT
Text GLabel 3650 3900 0    50   Input ~ 0
ENC_SW
Wire Wire Line
	7150 3750 7150 3850
Wire Wire Line
	7150 3850 7700 3850
Wire Wire Line
	7700 3950 7150 3950
$Comp
L power:+5V #PWR0103
U 1 1 5E960B7F
P 7150 2650
F 0 "#PWR0103" H 7150 2500 50  0001 C CNN
F 1 "+5V" H 7165 2823 50  0000 C CNN
F 2 "" H 7150 2650 50  0001 C CNN
F 3 "" H 7150 2650 50  0001 C CNN
	1    7150 2650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5E95EE37
P 7150 2450
F 0 "#PWR0102" H 7150 2200 50  0001 C CNN
F 1 "GND" H 7155 2277 50  0000 C CNN
F 2 "" H 7150 2450 50  0001 C CNN
F 3 "" H 7150 2450 50  0001 C CNN
	1    7150 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	7150 2450 7700 2450
Wire Wire Line
	7700 2450 7700 2700
Wire Wire Line
	7550 2650 7550 2800
Wire Wire Line
	7550 2800 7700 2800
Wire Wire Line
	7150 2650 7550 2650
$Comp
L power:GND #PWR0108
U 1 1 5E93623C
P 7700 4700
F 0 "#PWR0108" H 7700 4450 50  0001 C CNN
F 1 "GND" H 7705 4527 50  0000 C CNN
F 2 "" H 7700 4700 50  0001 C CNN
F 3 "" H 7700 4700 50  0001 C CNN
	1    7700 4700
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J4
U 1 1 5E93570D
P 7900 4800
F 0 "J4" H 7928 4776 50  0000 L CNN
F 1 "SWITCH" H 7928 4685 50  0000 L CNN
F 2 "TerminalBlock_Philmore:TerminalBlock_Philmore_TB132_1x02_P5.00mm_Horizontal" H 7900 4800 50  0001 C CNN
F 3 "~" H 7900 4800 50  0001 C CNN
	1    7900 4800
	1    0    0    -1  
$EndComp
Text GLabel 7700 4900 0    50   Input ~ 0
SW
Text GLabel 5250 4000 2    50   Input ~ 0
SW
Wire Wire Line
	7700 4700 7700 4800
$Comp
L power:GND #PWR0109
U 1 1 5E95360E
P 5250 2450
F 0 "#PWR0109" H 5250 2200 50  0001 C CNN
F 1 "GND" H 5255 2277 50  0000 C CNN
F 2 "" H 5250 2450 50  0001 C CNN
F 3 "" H 5250 2450 50  0001 C CNN
	1    5250 2450
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J5
U 1 1 5F0393A7
P 7900 3250
F 0 "J5" H 7928 3226 50  0000 L CNN
F 1 "SSR_CON" H 7928 3135 50  0000 L CNN
F 2 "TerminalBlock_Philmore:TerminalBlock_Philmore_TB132_1x02_P5.00mm_Horizontal" H 7900 3250 50  0001 C CNN
F 3 "~" H 7900 3250 50  0001 C CNN
	1    7900 3250
	1    0    0    -1  
$EndComp
Text GLabel 7700 3250 0    50   Input ~ 0
SSR_IN
Text GLabel 5250 3600 2    50   Input ~ 0
SSR_IN
Wire Wire Line
	7700 3350 7700 3450
$Comp
L power:GND #PWR05
U 1 1 5F0569FE
P 7700 3450
F 0 "#PWR05" H 7700 3200 50  0001 C CNN
F 1 "GND" H 7705 3277 50  0000 C CNN
F 2 "" H 7700 3450 50  0001 C CNN
F 3 "" H 7700 3450 50  0001 C CNN
	1    7700 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5F1BFEA9
P 2850 2650
F 0 "#PWR0106" H 2850 2400 50  0001 C CNN
F 1 "GND" H 2855 2477 50  0000 C CNN
F 2 "" H 2850 2650 50  0001 C CNN
F 3 "" H 2850 2650 50  0001 C CNN
	1    2850 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2550 2650 2550
Wire Wire Line
	2850 2550 2850 2650
Wire Wire Line
	3650 2900 3650 2650
$Comp
L power:+3.3V #PWR0107
U 1 1 5EA4BC07
P 3650 2450
F 0 "#PWR0107" H 3650 2300 50  0001 C CNN
F 1 "+3.3V" H 3665 2623 50  0000 C CNN
F 2 "" H 3650 2450 50  0001 C CNN
F 3 "" H 3650 2450 50  0001 C CNN
	1    3650 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J6
U 1 1 5F1E3CD6
P 2400 2550
F 0 "J6" H 2292 2225 50  0000 C CNN
F 1 "POWER" H 2292 2316 50  0000 C CNN
F 2 "TerminalBlock_Philmore:TerminalBlock_Philmore_TB132_1x02_P5.00mm_Horizontal" H 2400 2550 50  0001 C CNN
F 3 "~" H 2400 2550 50  0001 C CNN
	1    2400 2550
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F1F7EAB
P 2650 2100
F 0 "#FLG0101" H 2650 2175 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 2273 50  0000 C CNN
F 2 "" H 2650 2100 50  0001 C CNN
F 3 "~" H 2650 2100 50  0001 C CNN
	1    2650 2100
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5F1FA3D3
P 2650 2900
F 0 "#FLG0103" H 2650 2975 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 3073 50  0000 C CNN
F 2 "" H 2650 2900 50  0001 C CNN
F 3 "~" H 2650 2900 50  0001 C CNN
	1    2650 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	2650 2900 2650 2550
Connection ~ 2650 2550
Wire Wire Line
	2650 2550 2850 2550
Wire Wire Line
	2600 2450 2650 2450
Wire Wire Line
	2650 2100 2650 2450
Connection ~ 2650 2450
Wire Wire Line
	2650 2450 2850 2450
Wire Wire Line
	5250 2450 5250 2900
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5F2044C0
P 3650 2650
F 0 "#FLG0102" H 3650 2725 50  0001 C CNN
F 1 "PWR_FLAG" V 3650 2777 50  0000 L CNN
F 2 "" H 3650 2650 50  0001 C CNN
F 3 "~" H 3650 2650 50  0001 C CNN
	1    3650 2650
	0    -1   -1   0   
$EndComp
Connection ~ 3650 2650
Wire Wire Line
	3650 2650 3650 2450
$EndSCHEMATC
