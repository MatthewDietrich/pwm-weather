#include "weather-codes.h"
#include <stdlib.h>
#include <stdint.h>

// Corresponds to the weather type icons that OpenWeatherMap returns
enum pwmWeatherType
{
    PWM_NO_CONDITION        = 0,
    PWM_CLEAR_SKY           = 28,
    PWM_FEW_CLOUDS          = 56,
    PWM_SCATTERED_CLOUDS    = 85,
    PWM_BROKEN_CLOUDS       = 113,
    PWM_SHOWER_RAIN         = 142,
    PWM_RAIN                = 170,
    PWM_THUNDERSTORM        = 198,
    PWM_SNOW                = 227,
    PWM_MIST                = 255
};

// Corresponds to the intensity as defined in the weather code (see weather-codes.h)
enum pwmWeatherIntensity
{
    PWM_NO_INTENSITY        = 0,
    PWM_LIGHT_INTENSITY     = 85,
    PWM_MEDIUM_INTENSITY    = 170,
    PWM_HEAVY_INTENSITY     = 255
};

typedef struct
{
   uint8_t temperature;
   uint8_t humidity;
   uint8_t condition;
   uint8_t intensity;
} WeatherDataAsPWMValues;

void parse_weather_condition_code(int wcc, WeatherDataAsPWMValues *wd);
