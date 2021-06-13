//UFC Firmware
//Alan H.
//6-12-21

#define DCSBIOS_FOR_STM32
#define DCSBIOS_DEFAULT_SERIAL


#include <SPI.h> //rogerclarkmelbourne STM32 SPI lib, comes with Arduino_STM32 core
#include <Wire.h>
#include <USBComposite.h> //Arduino_STM32 USB Composite library for HID reporting
#include "Adafruit_HT1632.h" //Adafruit HT1632C library, intended for their 24x16 display. https://github.com/adafruit/HT1632
#include "DcsBios.h" //DCS Bios arduino  library, 0.35 branch. https://github.com/talbotmcinnis/dcs-bios-arduino-library MUST MODIFY LIBRARY FILES BEFORE USING.
#include "SegmentMap.h" //Contains data about which digit and segment corresponds to which hardware x,y
#include "CharacterMap.h" //Contains data about which segments are to be lit for each character

#define HT_DATA PA8
#define HT_WR PB15
#define HT_CS1 PB12
#define HT_CS2 PB13
#define BACKLIGHT PA0 //Backlight PWM out
#define SRLATCH PA15
#define NUMSRS 3

#define NUMROWS 5
#define NUMCOLS 4
#define NUMMATRIX 17

uint64_t buttonState = 0;

int rows[NUMROWS] = {PB9, PB8, PB7, PB6, PB5}; //Row and Column pins
int cols[NUMCOLS] = {PB0, PB1, PB10, PB11};

int buttonIDs[NUMROWS][NUMCOLS] = { //Matrix button IDs
  {-1, -1, -1, 12},
  { 0,  1,  2, 13},
  { 3,  4,  5, 14},
  { 6,  7,  8, 15}, 
  { 9, 10, 11, 16}
};

int SRButtons[8*NUMSRS] = { //Shift register button IDs
  17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40
};

bool prevCodes[NUMROWS][NUMCOLS]; //Previous matrix state

#define HID_SIGNED_JOYSTICK_REPORT_DESCRIPTOR(...) \
  0x05, 0x01,           /*  Usage Page (Generic Desktop) */ \
  0x09, 0x04,           /*  Usage (Joystick) */ \
  0xA1, 0x01,           /*  Collection (Application) */ \
  0x85, MACRO_GET_ARGUMENT_1_WITH_DEFAULT(HID_JOYSTICK_REPORT_ID, ## __VA_ARGS__),  /*    REPORT_ID */ \
  0x15, 0x00,           /*   Logical Minimum (0) */ \
  0x25, 0x01,           /*    Logical Maximum (1) */ \
  0x75, 0x01,           /*    Report Size (1) */ \
  0x95, 0x40,           /*    Report Count (64) */ \
  0x05, 0x09,           /*    Usage Page (Button) */ \
  0x19, 0x01,           /*    Usage Minimum (Button #1) */ \
  0x29, 0x40,           /*    Usage Maximum (Button #64) */ \
  0x81, 0x02,           /*    Input (variable,absolute) */ \
  0x15, 0x00,           /*    Logical Minimum (0) */ \
  0x25, 0x07,           /*    Logical Maximum (7) */ \
  0x35, 0x00,           /*    Physical Minimum (0) */ \
  0x46, 0x3B, 0x01,       /*    Physical Maximum (315) */ \
  0x75, 0x04,           /*    Report Size (4) */ \
  0x95, 0x01,           /*    Report Count (1) */ \
  0x65, 0x14,           /*    Unit (20) */ \
    0x05, 0x01,                     /*    Usage Page (Generic Desktop) */ \
  0x09, 0x39,           /*    Usage (Hat switch) */ \
  0x81, 0x42,           /*    Input (variable,absolute,null_state) */ \
    0x05, 0x01,                     /* Usage Page (Generic Desktop) */ \
  0x09, 0x01,           /* Usage (Pointer) */ \
    0xA1, 0x00,                     /* Collection () */ \
  0x16, 0x00, 0xFC,           /*    Logical Minimum (-1024) */ \
  0x26, 0xFF, 0x03,       /*    Logical Maximum (1023) */ \
  0x75, 0x0B,           /*    Report Size (11) */ \
  0x95, 0x04,           /*    Report Count (4) */ \
  0x09, 0x30,           /*    Usage (X) */ \
  0x09, 0x31,           /*    Usage (Y) */ \
  0x09, 0x33,           /*    Usage (Rx) */ \
  0x09, 0x34,           /*    Usage (Ry) */ \
  0x81, 0x02,           /*    Input (variable,absolute) */ \
    0xC0,                           /*  End Collection */ \
  0x15, 0x00,           /*  Logical Minimum (0) */ \
  0x26, 0xFF, 0x03,       /*  Logical Maximum (1023) */ \
  0x75, 0x0A,           /*  Report Size (10) */ \
  0x95, 0x02,           /*  Report Count (2) */ \
  0x09, 0x36,           /*  Usage (Slider) */ \
  0x09, 0x36,           /*  Usage (Slider) */ \
  0x81, 0x02,           /*  Input (variable,absolute) */ \
  0x75, 0x04,                    /*   REPORT_SIZE (4) */ \
  0x95, 0x01,                    /*   REPORT_COUNT (1) */ \
  0x81, 0x03,                    /*   OUTPUT (Cnst,Var,Abs) */ \  
  MACRO_ARGUMENT_2_TO_END(__VA_ARGS__)  \
  0xC0

typedef struct {
    uint8_t reportID;
    uint64_t buttons;
    unsigned hat:4;
    int x:11;
    int y:11;
    int rx:11;
    int ry:11;
    unsigned sliderLeft:10;
    unsigned sliderRight:10;
    unsigned unused:4;
} __packed SignedJoystickReport_t;

class HIDSignedJoystick : public HIDReporter {
public:
  SignedJoystickReport_t joyReport; 
  void begin(void) {};
  void end(void) {};
  HIDSignedJoystick(USBHID& HID, uint8_t reportID=HID_JOYSTICK_REPORT_ID) 
            : HIDReporter(HID, NULL, (uint8_t*)&joyReport, sizeof(joyReport), reportID) {
        joyReport.buttons = 0;
        joyReport.hat = 15;
        joyReport.x = 0;
        joyReport.y = 0;
        joyReport.rx = 0;
        joyReport.ry = 0;
        joyReport.sliderLeft = 0;
        joyReport.sliderRight = 0;
    }
};

USBHID HID;
USBCompositeSerial CompositeSerial;
HIDSignedJoystick joy(HID);

uint8 signedJoyReportDescriptor[] = {
  HID_SIGNED_JOYSTICK_REPORT_DESCRIPTOR()
};

  
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS1, HT_CS2); //Adafruit HT1632 matrix

void setup() {

    // Remap SPI 1
  // Source: https://community.platformio.org/t/pio-arduino-stm32f103cbt6-remap/6786/5
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY); // PB3 free
  afio_remap(AFIO_REMAP_SPI1);

  gpio_set_mode (GPIOB, 3, GPIO_AF_OUTPUT_PP);
  gpio_set_mode (GPIOB, 4, GPIO_INPUT_FLOATING);
  gpio_set_mode (GPIOB, 5, GPIO_AF_OUTPUT_PP);
  
  // Setup SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(SRLATCH, OUTPUT); //initialize srlatch and set high
  digitalWrite(SRLATCH, HIGH);

  //Configure matrix pins
  for (int i = 0; i < NUMCOLS; i++){
    pinMode(cols[i], INPUT_PULLUP);
  }
  for (int i = 0; i < NUMROWS; i++){
    pinMode(rows[i], INPUT);
  }
  
  //HID stuff
  HID.begin(CompositeSerial, signedJoyReportDescriptor, sizeof(signedJoyReportDescriptor));
  HID.registerComponent();
  //USBComposite.begin();  
  while (!USBComposite);

  
  
  //Start matrix
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.fillScreen();
  delay(2000);
  matrix.clearScreen();
  matrix.setTextWrap(false);
  matrix.setRotation(0);

  pinMode(BACKLIGHT, OUTPUT);
  analogWrite(BACKLIGHT, 255);
}

void checkMatrix(){
  for (int row = 0; row < NUMROWS; row++){ //Iterate through each row, set pin to output, LOW
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);
    for (int col = 0; col < NUMCOLS; col++){ //Check which column pins are now LOW (on)
      if (buttonIDs[row][col] != -1){
        if (digitalRead(cols[col]) == LOW){ //ON
          if (!prevCodes[row][col]){
            buttonState = buttonState | (1 << buttonIDs[row][col]);
          }
          prevCodes[row][col] = true;
        }else{                              //OFF
          if (prevCodes[row][col]){ 
            buttonState = buttonState & (~ (1 << buttonIDs[row][col]));
          }
          prevCodes[row][col] = false;
        }
      }
    }
    pinMode(rows[row], INPUT);
  }
}

uint64_t SRDATA = 0;

void checkSRs(){ //Read from Shift Registers using SPI
  digitalWrite(SRLATCH, LOW); //Pulse load latch
  digitalWrite(SRLATCH, HIGH);
  SRDATA = SPI.transfer(0); //Read first bank
  for (int i = 1; i < NUMSRS; i++){ //For the rest of the banks, bitshift data left 8, then set bits to next bank
    SRDATA = SRDATA << 8;
    SRDATA = SRDATA | SPI.transfer(0);
  }
  SRDATA = ~ SRDATA; //Invert data, assumes shift registers are pulled up
  SRDATA = SRDATA & (uint32_t)(pow(2, NUMSRS*8) - 1);     //clear data after last shift register
  buttonState = buttonState & ((uint32_t)(pow(2, 17))-1); //clear shift registers in button data
  buttonState = buttonState | (SRDATA << NUMMATRIX); //Set new button data
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
  checkMatrix();
  checkSRs();

  joy.joyReport.buttons = buttonState;
  joy.sendReport();
  delay(1);
}
