#include "weather-codes.h"
#include <stdint.h>

// This enum corresponds to the icons that OpenWeatherMap returns
enum generalWeatherType
{
    CLEAR_SKY,
    FEW_CLOUDS,
    SCATTERED_CLOUDS,
    BROKEN_CLOUDS,
    SHOWER_RAIN,
    RAIN,
    THUNDERSTORM,
    SNOW,
    MIST
};

enum weather_intensity
{
    NO_INTENSITY,
    LOW_INTENSITY,
    MEDIUM_INTENSITY,
    HIGH_INTENSITY
};

typedef struct
{
   uint8_t temperature;
   uint8_t humidity;
   uint8_t condition;
   uint8_t intensity;
} WeatherDataAsPWMValues;
