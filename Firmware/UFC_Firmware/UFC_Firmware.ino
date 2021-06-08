//UFC Firmware
//Alan H.
//6-8-21

#define DCSBIOS_FOR_STM32
#define DCSBIOS_DEFAULT_SERIAL

#include <Wire.h>
#include "Adafruit_HT1632.h" //Adafruit HT1632C library, intended for their 24x16 display. https://github.com/adafruit/HT1632
#include "DcsBios.h" //DCS Bios arduino  library, 0.35 branch. https://github.com/talbotmcinnis/dcs-bios-arduino-library
#include "SegmentMap.h" //Contains data about which digit and segment corresponds to which hardware x,y
#include "CharacterMap.h" //Contains data about which segments are to be lit for each character

#define HT_DATA PA8
#define HT_WR PB15
#define HT_CS1 PB12
#define HT_CS2 PB13
#define BACKLIGHT PA0

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS1, HT_CS2);

void setup() {
  DcsBios::setup();
  
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.fillScreen();
  delay(2000);
  matrix.clearScreen();
  matrix.setTextWrap(false);
  matrix.setRotation(0);

  pinMode(BACKLIGHT, OUTPUT);
  DisplayChar(ScratchPad16[0], Map16[SearchIndex("H")], 16);
  DisplayChar(ScratchPad16[1], Map16[SearchIndex("E")], 16);
  DisplayChar(ScratchPad7[0], Map7[SearchIndex("L")], 7);
  DisplayChar(ScratchPad7[1], Map7[SearchIndex("L")], 7);
  DisplayChar(ScratchPad7[2], Map7[SearchIndex("O")], 7);
  DisplayChar(OPT1Disp[0], Map16[SearchIndex("W")], 16);
  DisplayChar(OPT2Disp[0], Map16[SearchIndex("O")], 16);
  DisplayChar(OPT3Disp[0], Map16[SearchIndex("R")], 16);
  DisplayChar(OPT4Disp[0], Map16[SearchIndex("L")], 16);
  DisplayChar(OPT5Disp[0], Map16[SearchIndex("D")], 16);
  matrix.writeScreen();
  delay(2000);
  matrix.clearScreen();
}

int SearchIndex(String goal){
  int result = -1;
  for (int i = 0; i < lenChars; i++){
    if (characters[i].equals(goal)) result = i;
  }
  return result;
}

void DisplayChar(uint8_t segs[][2], uint8_t characterSegs[], int len){ //array of segment coordinates, array of segment light/dark, and length (7, or 16)
  for (int i = 0; i < len; i++){
    matrix.drawPixel(int(segs[i][0]), int(segs[i][1]), int(characterSegs[i]));
  }
}

//DCS-BIOS F-18 Functions:
void onUfcScratchpadString1DisplayChange(char* newValue) {
  String newString = String(newValue);
  newString.trim();
  if (newString.length() == 0){
    newString = " ";
  }
  int check = SearchIndex(newString);
  if (check == -1) return;
  DisplayChar(ScratchPad16[0], Map16[check], 16);
  matrix.writeScreen();
}
DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);
void onUfcScratchpadString2DisplayChange(char* newValue) {
  String newString = String(newValue);
  newString.trim();
  if (newString.length() == 0){
    newString = " ";
  }
  int check = SearchIndex(newString);
  if (check == -1) return;
  DisplayChar(ScratchPad16[1], Map16[check], 16);
  matrix.writeScreen();
}
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);
void onUfcScratchpadNumberDisplayChange(char* newValue) {
  String newString = String(newValue);
  for (int i = 1; i < newString.length(); i++){
    int check = SearchIndex(newString.substring(i, i+1));
    if (check == -1) return;
    DisplayChar(ScratchPad7[i-1], Map7[check], 7);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

//OPT
void onUfcOptionDisplay1Change(char* newValue) {
  String newString = String(newValue);
  for (int i = 0; i < newString.length(); i++){
    int check = SearchIndex(newString.substring(i, i+1));
    if (check == -1) return;
    DisplayChar(OPT1Disp[i], Map16[check], 16);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);
void onUfcOptionDisplay2Change(char* newValue) {
  String newString = String(newValue);
  for (int i = 0; i < newString.length(); i++){
    int check = SearchIndex(newString.substring(i, i+1));
    if (check == -1) return;
    DisplayChar(OPT2Disp[i], Map16[check], 16);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<4> ufcOptionDisplay2Buffer(0x7436, onUfcOptionDisplay2Change);
void onUfcOptionDisplay3Change(char* newValue) {
  String newString = String(newValue);
  for (int i = 0; i < newString.length(); i++){
    int check = SearchIndex(newString.substring(i, i+1));
    if (check == -1) return;
    DisplayChar(OPT3Disp[i], Map16[check], 16);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<4> ufcOptionDisplay3Buffer(0x743a, onUfcOptionDisplay3Change);
void onUfcOptionDisplay4Change(char* newValue) {
  String newString = String(newValue);
  for (int i = 0; i < newString.length(); i++){
    int check = SearchIndex(newString.substring(i, i+1));
    if (check == -1) return;
    DisplayChar(OPT4Disp[i], Map16[check], 16);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<4> ufcOptionDisplay4Buffer(0x743e, onUfcOptionDisplay4Change);
void onUfcOptionDisplay5Change(char* newValue) {
  String newString = String(newValue);
  for (int i = 0; i < newString.length(); i++){
    int check = SearchIndex(newString.substring(i, i+1));
    if (check == -1) return;
    DisplayChar(OPT5Disp[i], Map16[check], 16);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<4> ufcOptionDisplay5Buffer(0x7442, onUfcOptionDisplay5Change);

void onUfcOptionCueing1Change(char* newValue) {
  if (String(newValue).equals(" ")){
    matrix.clrPixel(OPT1Dot[0][0][0], OPT1Dot[0][0][1]);
  }else{
    matrix.setPixel(OPT1Dot[0][0][0], OPT1Dot[0][0][1]);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<1> ufcOptionCueing1Buffer(0x7428, onUfcOptionCueing1Change);

void onUfcOptionCueing2Change(char* newValue) {
  if (String(newValue).equals(" ")){
    matrix.clrPixel(OPT2Dot[0][0][0], OPT2Dot[0][0][1]);
  }else{
    matrix.setPixel(OPT2Dot[0][0][0], OPT2Dot[0][0][1]);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<1> ufcOptionCueing2Buffer(0x742a, onUfcOptionCueing2Change);

void onUfcOptionCueing3Change(char* newValue) {
  if (String(newValue).equals(" ")){
    matrix.clrPixel(OPT3Dot[0][0][0], OPT3Dot[0][0][1]);
  }else{
    matrix.setPixel(OPT3Dot[0][0][0], OPT3Dot[0][0][1]);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<1> ufcOptionCueing3Buffer(0x742c, onUfcOptionCueing3Change);

void onUfcOptionCueing4Change(char* newValue) {
  if (String(newValue).equals(" ")){
    matrix.clrPixel(OPT4Dot[0][0][0], OPT4Dot[0][0][1]);
  }else{
    matrix.setPixel(OPT4Dot[0][0][0], OPT4Dot[0][0][1]);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<1> ufcOptionCueing4Buffer(0x742e, onUfcOptionCueing4Change);

void onUfcOptionCueing5Change(char* newValue) {
  if (String(newValue).equals(" ")){
    matrix.clrPixel(OPT5Dot[0][0][0], OPT5Dot[0][0][1]);
  }else{
    matrix.setPixel(OPT5Dot[0][0][0], OPT5Dot[0][0][1]);
  }
  matrix.writeScreen();
}
DcsBios::StringBuffer<1> ufcOptionCueing5Buffer(0x7430, onUfcOptionCueing5Change);

//COMM
void onUfcComm1DisplayChange(char* newValue) {
  String newString = String(newValue);
  newString.trim();
  if (newString.length() == 0){
    newString = " ";
  }
  int check = SearchIndex(newString);
  if (check == -1) return;
  DisplayChar(COMM1[0], Map16[check], 16);
  matrix.writeScreen();
}
DcsBios::StringBuffer<2> ufcComm1DisplayBuffer(0x7424, onUfcComm1DisplayChange);
void onUfcComm2DisplayChange(char* newValue) {
  String newString = String(newValue);
  newString.trim();
  if (newString.length() == 0){
    newString = " ";
  }
  int check = SearchIndex(newString);
  if (check == -1) return;
  DisplayChar(COMM2[0], Map16[check], 16);
  matrix.writeScreen();
}
DcsBios::StringBuffer<2> ufcComm2DisplayBuffer(0x7426, onUfcComm2DisplayChange);


//Brightness control via cockpit
void onInstPnlDimmerChange(unsigned int newValue) {
  analogWrite(BACKLIGHT, map(newValue, 0, 65535, 0, 255));
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(0x7536, 0xffff, 0, onInstPnlDimmerChange);
//End DCS-BIOS


void loop() {
  DcsBios::loop();
  matrix.setCursor(0, 0);
  delay(1);
}
