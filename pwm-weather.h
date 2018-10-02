#ifndef PWM_WEATHER_H
#define PWM_WEATHER_H

#include <cstdlib>
#include <stdint.h>
#include <cmath>
#include <iostream>
#include "weather-codes.h"
#include "custom-ranges.h"
#include "dependencies/tinyxml2.h"

/**************************************************************
- Minimum and maximum PWM values
- These should not be changed. PWM values should always range
  from 0 to 255.
**************************************************************/
#define PWM_MIN 0
#define PWM_MAX 255

// Corresponds to the weather type icons that OpenWeatherMap returns
enum pwmWeatherType
{
    PWM_NO_CONDITION        = PWM_MIN,
    PWM_CLEAR_SKY           = 28,
    PWM_FEW_CLOUDS          = 56,
    PWM_SCATTERED_CLOUDS    = 85,
    PWM_BROKEN_CLOUDS       = 113,
    PWM_SHOWER_RAIN         = 142,
    PWM_RAIN                = 170,
    PWM_THUNDERSTORM        = 198,
    PWM_SNOW                = 227,
    PWM_MIST                = PWM_MAX
};

// Corresponds to the intensity as defined in the weather code (see weather-codes.h)
enum pwmWeatherIntensity
{
    PWM_NO_INTENSITY        = PWM_MIN,
    PWM_LIGHT_INTENSITY     = 85,
    PWM_MEDIUM_INTENSITY    = 170,
    PWM_HEAVY_INTENSITY     = PWM_MAX
};

typedef struct
{
public:
   uint8_t temperature;
   uint8_t humidity;
   uint8_t condition;
   uint8_t intensity;
} WeatherDataAsPWMValues;

void convert_temperature_to_pwm(const float temperature, WeatherDataAsPWMValues *wd);
void convert_humidity_to_pwm(const float humidity, WeatherDataAsPWMValues *wd);
uint8_t convert_value_in_range_to_pwm(float value, const float minValue, const float maxValue);
void parse_weather_condition_code(const int wcc, WeatherDataAsPWMValues *wd);
void parse_weather_file(const char* fileName, WeatherDataAsPWMValues *wd);
float get_temperature(tinyxml2::XMLElement *xmlRoot);
int get_humidity(tinyxml2::XMLElement *xmlRoot);
int get_condition_code(tinyxml2::XMLElement *xmlRoot);

#endif
