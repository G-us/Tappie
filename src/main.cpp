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

#define sliderPin 33
int StartingVal = 0;
int EndingVal = 0;    
int diff = 0;    // variable to hold the previous reading
int threshold = 1000;             // threshold value to decide when to trigger a swipe
unsigned long swipeStartTime = 0; // initialize swipe start time to 0
unsigned long swipeTimeout = 500; // set a timeout for swipe detection in milliseconds
bool SwipeInitiated = false;      // variable to hold the swipe state

#define reedSwitchPin 26

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

int GetSliderDiff()
{
  StartingVal = analogRead(sliderPin);
  delay(500);
  EndingVal = analogRead(sliderPin);
  diff = EndingVal - StartingVal;
  return diff;
}


void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  Serial.println("sup bitch");
  bleKeyboard.begin();
  btn.attachClick(PlayPause);
  btn.attachDoubleClick(NextTrack);
  btn.attachLongPressStart(PreviousTrack);
  pinMode(sliderPin, INPUT);
  pinMode(reedSwitchPin, INPUT_PULLUP);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 1); //1 = High, 0 = Low
}

int previousValue = 0;

void loop()
{
  if (digitalRead(reedSwitchPin) == LOW)
  {
      Serial.println("i sleep ");
      esp_deep_sleep_start();                // if the button state has changed,
  }
  if (bleKeyboard.isConnected())
  { //stfu get start value and then wait a few seconds or like half a second and then get the end
    btn.tick();                                             // check the status of the button
    
      
    if (analogRead(sliderPin) > 0)
    {
      if (GetSliderDiff() > 500)
      {
        VolumeUp();
        Serial.println("Volume Up");
        Serial.println(diff);
        Serial.println(EndingVal);
        Serial.println(StartingVal);
        StartingVal = 0;
        EndingVal = 0;
      }
      else if (GetSliderDiff() < -500)
      {
        VolumeDown();
        Serial.println("Volume Down");
        Serial.println(diff);
        Serial.println(EndingVal);
        Serial.println(StartingVal);
        StartingVal = 0;
        EndingVal = 0;
      }
    }
  }
}


