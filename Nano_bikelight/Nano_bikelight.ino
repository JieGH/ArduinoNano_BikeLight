// Program to exercise the MD_MAX72XX library
//
// Uses most of the functions in the library
#include <MD_MAX72xx.h>
#include <SPI.h>



// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define	MAX_DEVICES	4

#define	CLK_PIN		13  // or SCK
#define	DATA_PIN	11  // or MOSI
#define	CS_PIN		10  // or SS

const int leftbuttonPin = 6;     // the number of the pushbutton pin
int leftbuttonState = 0;         // variable for reading the pushbutton status
const int rightbuttonPin = 4;     // the number of the pushbutton pin
int rightbuttonState = 0;         // variable for reading the pushbutton status
const int nuibuttonPin = 5;     // the number of the pushbutton pin
int nuibuttonState = 0;         // variable for reading the pushbutton status

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
// Arbitrary pins
// MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// We always wait a bit between updates of the display
#define  DELAYTIME  80// in milliseconds

void left()
// Demonstrates the use of setColumn()
{
  mx.clear();
  // col neans where the scroling start
  for (uint8_t col = 0; col < mx.getColumnCount(); col++)
  {
    mx.setColumn(col, 0xff);
    delay(100 / MAX_DEVICES);
    //mx.setColumn(col, 0x00);
  }
}

void right()
// Demonstrates the use of setColumn()
{
  mx.clear();
  // col neans where the scroling start
  for (uint8_t col = 31; col < mx.getColumnCount(); col--)
  {
    mx.setColumn(col, 0xff);
    delay(100 / MAX_DEVICES);
    //mx.setColumn(col, 0x00);
  }
}

void bullseye()
// Demonstrate the use of buffer based repeated patterns
// across all devices.
{

  mx.clear();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  for (uint8_t n = 0; n < 1; n++)
  {
    byte  b = 0xff;
    int   i = 0;
    while (b != 0x00)
    {
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE - 1 - i, b);
        mx.setColumn(j, COL_SIZE - 1 - i, b);
      }
      mx.update();
      delay(DELAYTIME);
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE - 1 - i, 0);
        mx.setColumn(j, COL_SIZE - 1 - i, 0);
      }
      bitClear(b, i);
      bitClear(b, 7 - i);
      i++;
    }

    while (b != 0xff)
    {
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE - 1 - i, b);
        mx.setColumn(j, COL_SIZE - 1 - i, b);
      }
      mx.update();
      delay( DELAYTIME);
      for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE - 1 - i, 0);
        mx.setColumn(j, COL_SIZE - 1 - i, 0);
      }
      i--;
      bitSet(b, i);
      bitSet(b, 7 - i);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setup()
{
  mx.begin();
  pinMode(leftbuttonPin, INPUT);
  pinMode(rightbuttonPin, INPUT);
}

void loop()
{
  rightbuttonState = digitalRead(rightbuttonPin);
  leftbuttonState = digitalRead(leftbuttonPin);
  nuibuttonState = digitalRead(nuibuttonPin);

  if (rightbuttonState == HIGH)
  { right();
    tone(8, 600, 500);
    right();
    tone(8, 600, 500);
    right();
    tone(8, 600, 500);
    right();
    tone(8, 600, 500);
    right();
    tone(8, 600, 500);
    right();
    tone(8, 600, 500);
  }

  else if (leftbuttonState == HIGH)
  { left();
    tone(8, 1200, 500);
    left();
    tone(8, 1200, 500);
    left();
    tone(8, 1200, 500);
    left();
    tone(8, 1200, 500);
    left();
    tone(8, 1200, 500);
    left();
    tone(8, 1200, 500);
  }

  else
    bullseye();
}




