#include <BleKeyboard.h>
#include <Arduino.h>
#include <OneButton.h>

BleKeyboard bleKeyboard;
#define buttonPin 15 // the number of the pushbutton pin
bool buttonState = false; // variable to hold the button state
bool lastButtonState = false; // variable to hold the last button state
OneButton btn = OneButton(
  buttonPin,  // Input pin for the button
  true,        // Button is active LOW
  true         // Enable internal pull-up resistor
);

#define sliderPin 32

void PlayPause()
{
  Serial.println("Sending Play/Pause media key...");
  bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}

void NextTrack()
{
  Serial.println("Sending Next Track media key...");
  bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}

void PreviousTrack()
{
  Serial.println("Sending Previous Track media key...");
  bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}

void VolumeUp()
{
  Serial.println("Sending Volume Up media key...");
  bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}

void VolumeDown()
{
  Serial.println("Sending Volume Down media key...");
  bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  btn.attachClick(PlayPause);
  btn.attachDoubleClick(NextTrack);
  btn.attachLongPressStart(PreviousTrack);
  pinMode(sliderPin, INPUT);
}

void loop()
{
  if (bleKeyboard.isConnected())
  {
    btn.tick(); // check the status of the button
    Serial.println(analogRead(sliderPin));
  }
}