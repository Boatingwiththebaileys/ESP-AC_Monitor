// Code as of May 2024
//boating with the baileys

#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>
#include "sensesp/signalk/signalk_output.h"
#include "sensesp_app_builder.h"

#define SDA 21
#define SCL 22

using namespace sensesp;

reactesp::ReactESP app;

Adafruit_ADS1115 ads;

unsigned long delayTime = 1000;

SKOutput<float>* ac_amp_output;

const float FACTOR = 20; //20A/1V from teh CT

const float multiplier = 0.00005;

float getcurrent()
{
  float voltage;
  float current;
  float sum = 0;
  long time_check = millis();
  int counter = 0;

  while (millis() - time_check < 1000)
  {
    voltage = ads.readADC_Differential_0_1() * multiplier;
    current = voltage * FACTOR;
    //current /= 1000.0;

    sum += sq(current);
    counter = counter + 1;
  }

  current = sqrt(sum / counter);
  return (current);
}

void printValues()
{
  float currentRMS = getcurrent();
  ac_amp_output->set_input(currentRMS);
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println(F("AC Monitor test"));

  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    ->set_hostname("sensesp-AC_monitor")
                    ->get_app();


  Wire.begin(SDA, SCL);

  ads.setGain(GAIN_FOUR);      // +/- 1.024V 1bit = 0.5mV
  ads.begin();  

  ac_amp_output = new SKOutput<float>(
    "ac.current.amps",
    "/sensors/ADS1151/ac",
    new SKMetadata("A", "AC Amps")
  );

  sensesp_app->start();

}

void loop() {
  static unsigned long last_run = millis();

  if (millis() - last_run >= delayTime) {
    printValues();
    last_run = millis();
  }

  app.tick();
}
