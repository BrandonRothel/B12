#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    5
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    23
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

int frame = 0;
long unsigned int lastUpdate = 0;
int antenna = 0;

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i].setRGB(0, 0, 0); // Set Color HERE!!!
    leds[i].fadeLightBy(BRIGHTNESS);
  }
  Serial.begin(9600);
}

void loop()
{
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
    frame++;
    if (frame > 100) {
      frame = 0;
    }
    //Serial.println(frame);
  }
  updateEyes();
  updateEngine();
  updateAnntenna();
  FastLED.show();
}

void updateEyes() {
  //for (int i = 0; i < 14; i++ )
  //  {
  //    leds[i].setRGB(0, 0, 255); // Set Color HERE!!!
  //  }
  leds[6].setRGB(255, 0, 0);
  leds[1].setRGB(255, 0, 0);

  leds[5].setRGB(0, 0, 0);
  leds[0].setRGB(0, 0, 0);
  leds[2].setRGB(0, 0, 0);

  leds[4].setRGB(0, 255, 0);
  leds[3].setRGB(0, 255, 0);

  leds[13].setRGB(255, 0, 0);
  leds[8].setRGB(255, 0, 0);

  leds[12].setRGB(0, 0, 0);
  leds[7].setRGB(0, 0, 0);
  leds[9].setRGB(0, 0, 0);

  leds[11].setRGB(0, 255, 0);
  leds[10].setRGB(0, 255, 0);
}

void updateEngine() {
  for (int i = 14; i < 21; i++ )
  {
    leds[i].setRGB(0, 255, 255); // Set Color HERE!!!
  }
}

void updateAnntenna() {
  if (((frame % 25) < 18) && (antenna < 255)) {
    antenna += 4;
    Serial.println(antenna);
  } else {
    if (antenna > 0) {
      antenna -= 4;
    }
  }
  leds[21].setRGB(0, antenna, antenna);
  leds[22].setRGB(0, antenna, antenna);
}
