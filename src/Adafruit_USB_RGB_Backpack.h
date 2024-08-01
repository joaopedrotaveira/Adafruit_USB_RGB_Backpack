/*!
 * @file Adafruit_USB_RGB_Backpack_h
 */
#ifndef Adafruit_USB_RGB_Backpack_h
#define Adafruit_USB_RGB_Backpack_h

#include "Arduino.h"
#include "Print.h"

#define ORBITAL_MATRX_PREFIX    0xFE

#define DISPLAY_ON_CMD          0x42
#define DISPLAY_OFF_CMD         0x46

#define BRIGHTNESS_CMD          0x99
#define BRIGHTNESS_SAVE_CMD     0x98

#define CONTRAST_CMD            0x50
#define CONTRAST_SAVE_CMD       0x91

#define AUTOSCROLL_ON_CMD       0x51
#define AUTOSCROLL_OFF_CMD      0x52

#define CLEAR_SCREEN_CMD        0x58

#define SPLASH_SCREEN_CMD       0x40

#define SET_CURSOR_POSITION_CMD 0x47

#define GO_HOME_CMD             0x48

#define CURSOR_BACK_CMD         0x4C
#define CURSOR_FORWARD          0x4D

#define UNDERLINE_CURSOR_ON_CMD   0x4A
#define UNDERLINE_CURSOR_OFF_CMD  0x4B

#define BLOCK_CURSOR_ON_CMD     0x53
#define BLOCK_CURSOR_OFF_CMD    0x54

#define SET_BAUDRATE_CMD        0x39

#define SET_RGB_BACKLIGHT_COLOR_CMD 0xD0
#define SET_LCD_SIZE_CMD        0xD1

#define CREATE_CUSTOM_CHARACTER_CMD 0x4E
#define SAVE_CUSTOM_CHARACTER_CMD   0xC1
#define LOAD_CUSTOM_CHARACTER_CMD   0xC0

/*!
 * @brief Main LiquidCrystal class
 */
class Adafruit_USB_RGB_Backpack : public Print {
public:

  Adafruit_USB_RGB_Backpack(Print &serial): _serial(&serial){};

  void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
            uint8_t d5, uint8_t d6, uint8_t d7);

  /*!
   * @brief Starts I2C connection with display
   * @param cols Sets the number of columns
   * @param rows Sets the number of rows
   * @param charsize Sets the charactersize
   * @return Returns true when connection was successful
   */
  bool begin(uint8_t cols, uint8_t rows) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(SET_LCD_SIZE_CMD);
    _serial->write(cols);
    _serial->write(rows);
  }

  /*!
   * @brief High-level command to clear the display
   */
  void clear() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(CLEAR_SCREEN_CMD);
  }
  /*!
   * @brief High-level command to set the cursor position to zero
   */
  void home() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(GO_HOME_CMD);
  }
  /*!
   * @brief High-level command to turn the display off quickly
   */
  void noDisplay() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(DISPLAY_OFF_CMD);
  }
  /*!
   * @brief High-level command to turn the display on quickly
   */
  void display() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(DISPLAY_ON_CMD);
  }
  /*!
   * @brief High-level command to turn the blinking cursor off
   */
  void noBlock()  {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(BLOCK_CURSOR_OFF_CMD);
  }
  /*!
   * @brief High-level command to turn the blinking cursor on
   */
  void block() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(BLOCK_CURSOR_ON_CMD);
  }
  /*!
   * @brief High-level command to turn the underline cursor off
   */
  void noCursor() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(UNDERLINE_CURSOR_OFF_CMD);
  }
  /*!
   * @brief High-level command to turn the underline cursor on
   */
  void cursor() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(UNDERLINE_CURSOR_ON_CMD);
  }
  /*!
   * @brief High-level command to scroll display left without changing the RAM
   */
  // void scrollDisplayLeft();
  // /*!
  //  * @brief High-level command to scroll display right without changing the RAM
  //  */
  // void scrollDisplayRight();
  /*!
   * @brief High-level command to make text flow left to right
   */
  // void leftToRight();
  // /*!
  //  * @brief High-level command to make text flow right to left
  //  */
  // void rightToLeft();
  /*!
   * @brief High-level command to 'right justify' text from the cursor
   */
  void autoscroll() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(AUTOSCROLL_ON_CMD);
  }
  /*!
   * @brief High-level command to 'left justify' text from the cursor
   */
  void noAutoscroll() {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(AUTOSCROLL_OFF_CMD);
  }

  /*!
   * @brief High-level command to set the backlight, only if the LCD backpack is
   * used
   * @param value Set the backlight off/on, 0 = off, >0 = on.
   */
  void setContrast(uint8_t value) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(CONTRAST_CMD);
    _serial->write(value);
  }

  void setSaveContrast(uint8_t value) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(CONTRAST_SAVE_CMD);
    _serial->write(value);
  }

  void setBrightness(uint8_t value) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(BRIGHTNESS_CMD);
    _serial->write(value);
  }

  void setSaveBrightness(uint8_t value) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(BRIGHTNESS_SAVE_CMD);
    _serial->write(value);
  }

  void setBacklightRGBColor(uint8_t red, uint8_t green, uint8_t blue) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(SET_RGB_BACKLIGHT_COLOR_CMD);
    _serial->write(red);
    _serial->write(green);
    _serial->write(blue);
  }

  // void setSplashScreen(uint8_t value);

  /*!
   * @brief High-level command that creates custom character in CGRAM
   * @param location Location in cgram to fill
   * @param charmap[] Character map
   */
  void createChar(uint8_t location, uint8_t data[8]) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(CREATE_CUSTOM_CHARACTER_CMD);
    _serial->write(location);
    for(int i = 0; i < 8; i++) {
      _serial->write((uint8_t)data[i]);
    }
  }
  /*!
   * @brief High-level command that sets the location of the cursor
   * @param col Column to set the cursor in
   * @param row Row to set the cursor in
   */
  void setCursor(uint8_t col, uint8_t row) {
    _serial->write(ORBITAL_MATRX_PREFIX);
    _serial->write(SET_CURSOR_POSITION_CMD);
    _serial->write(col);
    _serial->write(row);
  }

#if ARDUINO >= 100
  size_t write(uint8_t value) {
    _serial->write(value);
    return 1;
  }
#else
  /*!
   * @brief Mid-level command that sends data to the display
   * @param value Data to send to the display
   */
  void write(uint8_t value) { 
    _serial->write(value);
  }
#endif

private:
    Print *_serial;

};
#endif /* Adafruit_USB_RGB_Backpack_h */
