#include <BleKeyboard.h>
#include <Arduino.h>
#include <OneButton.h>

BleKeyboard bleKeyboard;
#define buttonPin 15          // the number of the pushbutton pin
bool buttonState = false;     // variable to hold the button state
bool lastButtonState = false; // variable to hold the last button state
OneButton btn = OneButton(
    buttonPin, // Input pin for the button
    true,      // Button is active LOW
    true       // Enable internal pull-up resistor
);

#define sliderPin 32
int StartingVal = 0;
int TopPos = 0;
int BottomPos = 0;
bool slideInitiated = false;
int previousReading = 0;          // variable to hold the previous reading
int threshold = 1000;             // threshold value to decide when to trigger a swipe
unsigned long swipeStartTime = 0; // initialize swipe start time to 0
unsigned long swipeTimeout = 500; // set a timeout for swipe detection in milliseconds

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
    btn.tick();                                             // check the status of the button
    int softpotReading = analogRead(sliderPin); //current reading
  if ((softpotReading - previousReading) > threshold) { //if the reading increased by more than the threshold
    Serial.println("Swipe up detected!");
  }
  previousReading = softpotReading; //update previous reading
  delay(100); //just here to slow down the output for easier reading
  }
}