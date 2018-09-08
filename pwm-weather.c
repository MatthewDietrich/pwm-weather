/**************************************************************
pwm-weather.c

Author: Matthew Dietrich
        https://github.com/MatthewDietrich/pwm-weather

Includes functionality to turn json weather data from the
OpenWeatherMap API into PWM values.
**************************************************************/

#include "pwm-weather.h"

/**************************************************************
- convert_temperature_to_pwm

- Given a temperature, convert to a value between 0 and 255,
  with 0 corresponding to MIN_TEMPERATURE and 255 corresponding
  to MAX_TEMPERATURE.

- The units of temperature don't matter. This is just mapping
  one numeric range onto another.

- https://stackoverflow.com/questions/5731863/#5732390
**************************************************************/
void convert_temperature_to_pwm(float temperature, WeatherDataAsPWMValues *wd)
{
    if (wd == NULL) return;

    // Boundary check
    if (temperature > MAX_TEMPERATURE) temperature = MAX_TEMPERATURE;
    else if (temperature < MIN_TEMPERATURE) temperature = MIN_TEMPERATURE;

    double slope = 1.0 * (PWM_MAX - PWM_MIN) / (MAX_TEMPERATURE - MIN_TEMPERATURE);
    wd->temperature = (uint8_t)floor((PWM_MIN + slope * (temperature - MIN_TEMPERATURE)) + 0.5);
}

/**************************************************************
- parse_weather_condition_code

- Given a weather code corresponding to a specific type of
  weather, store a PWM value corresponding to the general type
  of weather condition and the intensity of the weather
  condition if applicable
**************************************************************/
void parse_weather_condition_code(int wcc, WeatherDataAsPWMValues *wd)
{
    if (wd == NULL) return;;

    /***
    - Store weather condition
    - The reasons I've implemented this as a switch statement
      rather than as a series of if-else statements that compare
      ranges of values is that it's more readable like this, and
      therefore easier to customize
    */

    switch (wcc)
    {
        // Thunderstorms
        case WCC_TS_LIGHT_RAIN:
        case WCC_LIGHT_TS:
        case WCC_TS_LIGHT_DRIZZLE:
        case WCC_TS_DRIZZLE:
        case WCC_TS_RAIN:
        case WCC_TS:
        case WCC_RAGGED_TS:
        case WCC_TS_HEAVY_RAIN:
        case WCC_HEAVY_TS:
        case WCC_TS_HEAVY_DRIZZLE:
            wd->condition = PWM_THUNDERSTORM;
            break;

        // Drizzle (a.k.a. "Shower Rain" apparently)
        case WCC_LIGHT_DRIZZLE:
        case WCC_LIGHT_DRIZZLE_RAIN:
        case WCC_DRIZZLE:
        case WCC_DRIZZLE_RAIN:
        case WCC_SHOWER_RAIN_DRIZZLE:
        case WCC_SHOWER_DRIZZLE:
        case WCC_HEAVY_DRIZZLE:
        case WCC_HEAVY_DRIZZLE_RAIN:
            wd->condition = PWM_SHOWER_RAIN;
            break;

        // Rain
        case WCC_LIGHT_RAIN:
        case WCC_MODERATE_RAIN:
        case WCC_HEAVY_RAIN:
        case WCC_VERY_HEAVY_RAIN:
        case WCC_EXTREME_RAIN:
        case WCC_FREEZING_RAIN:
        case WCC_LIGHT_SHOWER_RAIN:
        case WCC_SHOWER_RAIN:
        case WCC_HEAVY_SHOWER_RAIN:
        case WCC_RAGGED_SHOWER_RAIN:
            wd->condition = PWM_RAIN;
            break;

        
        // Snow and other winter weather
        case WCC_LIGHT_SNOW:
        case WCC_SNOW:
        case WCC_HEAVY_SNOW:
        case WCC_SLEET:
        case WCC_SHOWER_SLEET:
        case WCC_LIGHT_RAIN_SNOW:
        case WCC_RAIN_SNOW:
        case WCC_LIGHT_SHOWER_SNOW:
        case WCC_SHOWER_SNOW:
        case WCC_HEAVY_SHOWER_SNOW:
            wd->condition = PWM_SNOW;
            break;

        // Atmospheric conditions
        case WCC_MIST:
        case WCC_SMOKE:
        case WCC_HAZE:
        case WCC_SAND_DUST_WHIRLS:
        case WCC_FOG:
        case WCC_SAND:
        case WCC_DUST:
        case WCC_VOLCANIC_ASH:
        case WCC_SQUALLS:
        case WCC_TORNADO:
            wd->condition = PWM_MIST;
            break;

        // Clear or cloudy
        case WCC_CLEAR:
            wd->condition = PWM_CLEAR_SKY;
            break;

        case WCC_FEW_CLOUDS:
            wd->condition = PWM_FEW_CLOUDS;
            break;

        case WCC_SCATTERED_CLOUDS:
            wd->condition = PWM_SCATTERED_CLOUDS;
            break;

        case WCC_BROKEN_CLOUDS:
        case WCC_OVERCAST_CLOUDS:
            wd->condition = PWM_BROKEN_CLOUDS;
            break;
    }

    // Store intensity
    switch (wcc)
    {
        case WCC_TS_LIGHT_RAIN:
        case WCC_LIGHT_TS:
        case WCC_TS_LIGHT_DRIZZLE:
        case WCC_LIGHT_DRIZZLE:
        case WCC_LIGHT_DRIZZLE_RAIN:
        case WCC_LIGHT_RAIN:
        case WCC_LIGHT_SHOWER_RAIN:
        case WCC_LIGHT_SNOW:
        case WCC_LIGHT_RAIN_SNOW:
        case WCC_LIGHT_SHOWER_SNOW:
            wd->intensity = PWM_LIGHT_INTENSITY;
            break;

        case WCC_TS_RAIN:
        case WCC_TS:
        case WCC_RAGGED_TS:
        case WCC_TS_DRIZZLE:
        case WCC_DRIZZLE:
        case WCC_DRIZZLE_RAIN:
        case WCC_SHOWER_RAIN_DRIZZLE:
        case WCC_SHOWER_DRIZZLE:
        case WCC_MODERATE_RAIN:
        case WCC_FREEZING_RAIN:
        case WCC_SHOWER_RAIN:
        case WCC_RAGGED_SHOWER_RAIN:
        case WCC_SNOW:
        case WCC_SLEET:
        case WCC_SHOWER_SLEET:
        case WCC_RAIN_SNOW:
        case WCC_SHOWER_SNOW:
            wd->intensity = PWM_MEDIUM_INTENSITY;
            break;

        case WCC_TS_HEAVY_RAIN:
        case WCC_HEAVY_TS:
        case WCC_TS_HEAVY_DRIZZLE:
        case WCC_HEAVY_DRIZZLE:
        case WCC_HEAVY_DRIZZLE_RAIN:
        case WCC_HEAVY_SHOWER_RAIN_DRIZZLE:
        case WCC_HEAVY_RAIN:
        case WCC_VERY_HEAVY_RAIN:
        case WCC_EXTREME_RAIN:
        case WCC_HEAVY_SHOWER_RAIN:
        case WCC_HEAVY_SNOW:
        case WCC_HEAVY_SHOWER_SNOW:
            wd->intensity = PWM_HEAVY_INTENSITY;

        default: wd->intensity = PWM_NO_INTENSITY;

    }
}
