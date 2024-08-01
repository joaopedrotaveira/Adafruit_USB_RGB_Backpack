#include "Arduino.h"

#include "Adafruit_USB_RGB_Backpack.h"

// #if defined(ARDUINO_ARCH_SAMD) || defined(__SAM3X8E__)
//   // use pin 18 with Due, pin 1 with Zero or M0 Pro 
//   #define lcd Serial1 
// #else
  // #include <SoftwareSerial.h>
//   // Create a software serial port!
  // SoftwareSerial lcd = SoftwareSerial(22,23);
// #endif

// for ESP8266 use this SoftwareSerial library: https://github.com/plerup/espsoftwareserial

Adafruit_USB_RGB_Backpack lcd(Serial2);

void setup() {
  Serial0.begin(57600);
  Serial2.begin(57600, SERIAL_8N1, 16, 17);
  
  // lcd.begin(16, 2);
  // delay(10);       
  // we suggest putting delays after each command to make sure the data 
  // is sent and the LCD is updated.

  // set the contrast, 200 is a good place to start, adjust as desired
  lcd.setContrast(200);
  delay(10);       
  
  // set the brightness - we'll max it (255 is max brightness)
  lcd.setBrightness(255);
  delay(10);       
  
  // turn off cursors
  lcd.noCursor();
  lcd.noBlock();
  
  // create a custom character
  uint8_t heart[] = {0x00, 0x0A, 0x15, 0x11, 0x11, 0x0A, 0x04, 0x00};
  lcd.createChar(0, heart);
  delay(10);   // we suggest putting delays after each command 
  
  // clear screen
  lcd.clear();
  delay(10);   // we suggest putting delays after each command 
  
  // go 'home'
  lcd.home();
  delay(10);   // we suggest putting delays after each command 

  lcd.print("We ");
  lcd.write((uint8_t)0);            // to print the custom character, 'write' the location
  lcd.println(" Arduino!");
  lcd.print("     - Adafruit");
  
  delay(1000);
}

uint8_t red, green, blue;
void loop() {
 // adjust colors 
 for (red = 0; red < 255; red++) {
  lcd.setBacklightRGBColor(red, 0, 255-red);
  delay(10);  // give it some time to adjust the backlight!
 }   

 for (green = 0; green < 255; green++) {
  lcd.setBacklightRGBColor(255-green, green, 0);
  delay(10);  // give it some time to adjust the backlight!
 }   

 for (blue = 0; blue < 255; blue++) {
  lcd.setBacklightRGBColor(0, 255-blue, blue);
  delay(10);  // give it some time to adjust the backlight!
 }   
}
