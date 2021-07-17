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
L Used_testing_SDcard:Micro_SD_Card_DPIkit J1
U 1 1 60D92140
P 7750 5250
F 0 "J1" H 8780 5246 50  0000 L CNN
F 1 "Micro_SD_Card_DPIkit" H 8780 5155 50  0000 L CNN
F 2 "" H 8900 5550 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 7750 5250 50  0001 C CNN
	1    7750 5250
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60DA9692
P 5700 5500
F 0 "#PWR?" H 5700 5250 50  0001 C CNN
F 1 "GND" H 5705 5327 50  0000 C CNN
F 2 "" H 5700 5500 50  0001 C CNN
F 3 "" H 5700 5500 50  0001 C CNN
	1    5700 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 5450 6100 5500
Wire Wire Line
	6000 5450 6000 5500
Wire Wire Line
	6000 5500 6100 5500
$Comp
L power:+5V #PWR?
U 1 1 60DAE105
P 5900 3400
F 0 "#PWR?" H 5900 3250 50  0001 C CNN
F 1 "+5V" H 5915 3573 50  0000 C CNN
F 2 "" H 5900 3400 50  0001 C CNN
F 3 "" H 5900 3400 50  0001 C CNN
	1    5900 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3400 5900 3450
$Comp
L power:+5V #PWR?
U 1 1 60DB1A39
P 6800 5550
F 0 "#PWR?" H 6800 5400 50  0001 C CNN
F 1 "+5V" H 6815 5723 50  0000 C CNN
F 2 "" H 6800 5550 50  0001 C CNN
F 3 "" H 6800 5550 50  0001 C CNN
	1    6800 5550
	1    0    0    1   
$EndComp
Wire Wire Line
	6800 5550 6850 5550
$Comp
L MCU_Module:Arduino_Nano_v2.x A?
U 1 1 60D7665F
P 6100 4450
F 0 "A?" H 6100 3200 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 6100 3300 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6100 4450 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6100 4450 50  0001 C CNN
	1    6100 4450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5700 5500 6000 5500
Connection ~ 6000 5500
$Comp
L power:GND #PWR?
U 1 1 60DCE19F
P 6700 5250
F 0 "#PWR?" H 6700 5000 50  0001 C CNN
F 1 "GND" H 6705 5077 50  0000 C CNN
F 2 "" H 6700 5250 50  0001 C CNN
F 3 "" H 6700 5250 50  0001 C CNN
	1    6700 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 5250 6850 5250
Wire Wire Line
	6600 5150 6850 5150
Wire Wire Line
	6600 5050 6850 5050
Wire Wire Line
	6600 4950 6850 4950
Wire Wire Line
	6600 4850 6850 4850
$EndSCHEMATC
