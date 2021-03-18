#include <Arduino.h>
#include <Mouse.h>

const byte PIN_BUTTON_A = 2;
const byte PIN_BUTTON_B = 3;
const byte PIN_BUTTON_C = 4;
const byte PIN_BUTTON_D = 5;
const byte PIN_BUTTON_E = 6;
const byte PIN_BUTTON_F = 7;
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

const int ledPin = 13;

boolean mouseIsActive = false;
int lastSwitchState = LOW;

int rangePot = 750;
int range = 12;
int responseDelay = 5;
int threshold = range / 4;
int center = 0;

void setup()
{
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(ledPin, OUTPUT);

  Mouse.begin();
}

int readAxis(int thisAxis)
{
  int reading = analogRead(thisAxis);

  if (thisAxis == PIN_ANALOG_X)
  {
    reading = map(reading, 0, rangePot, -1 * range, range);
  }
  else
  {
    reading = map(reading, 0, rangePot, range, -1 * range);
  }

  int distance = reading - center;

  if (abs(distance) < threshold)
  {
    distance = 0;
  }

  return distance;
}

void loop()
{
  int switchState = digitalRead(PIN_BUTTON_A);

  if (switchState != lastSwitchState)
  {
    if (switchState == LOW)
    {
      mouseIsActive = !mouseIsActive;
      digitalWrite(ledPin, mouseIsActive);
    }
  }

  lastSwitchState = switchState;

  int axis_x = readAxis(PIN_ANALOG_X);
  int axis_y = readAxis(PIN_ANALOG_Y);

  if (mouseIsActive)
  {
    Mouse.move(axis_x, axis_y, 0);
  }

  if (digitalRead(PIN_BUTTON_D) == LOW)
  {
    if (!Mouse.isPressed(MOUSE_LEFT))
    {
      Mouse.press(MOUSE_LEFT);
    }
  }
  else
  {
    if (Mouse.isPressed(MOUSE_LEFT))
    {
      Mouse.release(MOUSE_LEFT);
    }
  }
  if (digitalRead(PIN_BUTTON_B) == LOW)
  {
    if (!Mouse.isPressed(MOUSE_RIGHT))
    {
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else
  {
    if (Mouse.isPressed(MOUSE_RIGHT))
    {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  delay(responseDelay);
}