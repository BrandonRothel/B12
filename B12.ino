#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN 5
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 23
CRGB leds[NUM_LEDS];
CRGB targetRGB[NUM_LEDS];

#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

int frame = 0;
long unsigned int lastUpdate = 0;

int eyesState = 0;
long unsigned int eyesNextUpdate = 0;
int antennaState = 0;
long unsigned int antennaNextUpdate = 0;
int engineState = 0;
long unsigned int engineNextUpdate = 0;

void setup()
{
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  // Set all leds to off
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB(0, 0, 0); // Set Color HERE!!!
    leds[i].fadeLightBy(BRIGHTNESS);
  }
  Serial.begin(9600);
  randomSeed(69);
}

void loop()
{
  delay(10);
  updateLeds(10);
  if (millis() > eyesNextUpdate)
  {
    updateEyes();
  }
  if (millis() > antennaNextUpdate)
  {
    updateAntenna();
  }
    if (millis() > engineNextUpdate)
  {
    updateEngine();
  }
  FastLED.show();
}

void updateEyes()
{
  switch (eyesState)
  {
  case 0:
    targetRGB[6].setRGB(255, 0, 0);
    targetRGB[1].setRGB(255, 0, 0);

    targetRGB[5].setRGB(0, 0, 0);
    targetRGB[0].setRGB(0, 0, 0);
    targetRGB[2].setRGB(0, 0, 0);

    targetRGB[4].setRGB(0, 255, 0);
    targetRGB[3].setRGB(0, 255, 0);

    targetRGB[13].setRGB(255, 0, 0);
    targetRGB[8].setRGB(255, 0, 0);

    targetRGB[12].setRGB(0, 0, 0);
    targetRGB[7].setRGB(0, 0, 0);
    targetRGB[9].setRGB(0, 0, 0);

    targetRGB[11].setRGB(0, 255, 0);
    targetRGB[10].setRGB(0, 255, 0);
    eyesNextUpdate += 4000;
    eyesState = 1;
    break;

  case 1:
    targetRGB[6].setRGB(0, 0, 0);
    targetRGB[1].setRGB(0, 0, 0);

    targetRGB[5].setRGB(64, 64, 0);
    targetRGB[0].setRGB(64, 64, 0);
    targetRGB[2].setRGB(64, 64, 0);

    targetRGB[4].setRGB(0, 0, 0);
    targetRGB[3].setRGB(0, 0, 0);

    targetRGB[13].setRGB(0, 0, 0);
    targetRGB[8].setRGB(0, 0, 0);

    targetRGB[12].setRGB(64, 64, 0);
    targetRGB[7].setRGB(64, 64, 0);
    targetRGB[9].setRGB(64, 64, 0);

    targetRGB[11].setRGB(0, 0, 0);
    targetRGB[10].setRGB(0, 0, 0);
    eyesNextUpdate += 250;
    eyesState = 2;
    break;

  case 2:
    targetRGB[6].setRGB(0, 0, 0);
    targetRGB[1].setRGB(0, 0, 0);

    targetRGB[5].setRGB(0, 0, 0);
    targetRGB[0].setRGB(0, 0, 0);
    targetRGB[2].setRGB(0, 0, 0);

    targetRGB[4].setRGB(0, 0, 0);
    targetRGB[3].setRGB(0, 0, 0);

    targetRGB[13].setRGB(0, 0, 0);
    targetRGB[8].setRGB(0, 0, 0);

    targetRGB[12].setRGB(0, 0, 0);
    targetRGB[7].setRGB(0, 0, 0);
    targetRGB[9].setRGB(0, 0, 0);

    targetRGB[11].setRGB(0, 0, 0);
    targetRGB[10].setRGB(0, 0, 0);
    eyesNextUpdate += 500;
    eyesState = 3;
    break;

  case 3:
    targetRGB[6].setRGB(0, 0, 0);
    targetRGB[1].setRGB(0, 0, 0);

    targetRGB[5].setRGB(64, 64, 0);
    targetRGB[0].setRGB(64, 64, 0);
    targetRGB[2].setRGB(64, 64, 0);

    targetRGB[4].setRGB(0, 0, 0);
    targetRGB[3].setRGB(0, 0, 0);

    targetRGB[13].setRGB(0, 0, 0);
    targetRGB[8].setRGB(0, 0, 0);

    targetRGB[12].setRGB(64, 64, 0);
    targetRGB[7].setRGB(64, 64, 0);
    targetRGB[9].setRGB(64, 64, 0);

    targetRGB[11].setRGB(0, 0, 0);
    targetRGB[10].setRGB(0, 0, 0);
    eyesNextUpdate += 30;
    eyesState = 0;
    break;

  default:
    eyesNextUpdate += 250;
    eyesState = 0;
    break;
  }
}

void updateLeds(int speed)
{
  for (int ledNum = 0; ledNum < NUM_LEDS; ledNum++)
  {
    if (abs(targetRGB[ledNum].r - leds[ledNum].r) > 0)
    {
      if (abs(targetRGB[ledNum].r - leds[ledNum].r) < speed)
      {
        speed = abs(targetRGB[ledNum].r - leds[ledNum].r);
      }
      if (targetRGB[ledNum].r > leds[ledNum].r)
      {
        leds[ledNum].r += speed;
      }
      else
      {
        leds[ledNum].r -= speed;
      }
    }
    if (abs(targetRGB[ledNum].g - leds[ledNum].g) > 0)
    {
      if (abs(targetRGB[ledNum].g - leds[ledNum].g) < speed)
      {
        speed = abs(targetRGB[ledNum].g - leds[ledNum].g);
      }
      if (targetRGB[ledNum].g > leds[ledNum].g)
      {
        leds[ledNum].g += speed;
      }
      else
      {
        leds[ledNum].g -= speed;
      }
    }
    if (abs(targetRGB[ledNum].b - leds[ledNum].b) > 0)
    {
      if (abs(targetRGB[ledNum].b - leds[ledNum].b) < speed)
      {
        speed = abs(targetRGB[ledNum].b - leds[ledNum].b);
      }
      if (targetRGB[ledNum].b > leds[ledNum].b)
      {
        leds[ledNum].b += speed;
      }
      else
      {
        leds[ledNum].b -= speed;
      }
    }
  }
}

void updateEngine()
{
  for (int i = 15; i < 21; i++)
  {
    targetRGB[i].setRGB(0, 128, 128);
  }
  engineState++;
  if(engineState>20){
    engineState = 15;
  }
  targetRGB[14].setRGB(0,0,0);
  targetRGB[engineState].setRGB(0,0,0);
  engineNextUpdate += 128;
}

void updateAntenna()
{
  switch (antennaState)
  {
  case 0:
    targetRGB[21].setRGB(0, 200, 255);
    targetRGB[22].setRGB(0, 200, 255);
    antennaState = 1;
    antennaNextUpdate += 3000;
    break;
  case 1:
    targetRGB[21].setRGB(0, 0, 0);
    targetRGB[22].setRGB(0, 0, 0);
    antennaState = 0;
    antennaNextUpdate += 500;
    break;
  }
}
