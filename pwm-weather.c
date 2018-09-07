#include "pwm-weather.h"

parse_weather_condition_code(weatherConditionCode wcc, WeatherDataAsPWMValues wd)
{
    wd.condition = PWM_NO_CONDITION;
    wd.intensity = PWM_NO_INTENSITY;

    switch (wcc)
    {
        // 200 block: Thunderstorms
        case WCC_TS_LIGHT_RAIN:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_LIGHT_INTENSITY;
            break;

        case WCC_TS_RAIN:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_MEDIUM_INTENSITY;
            break;

        case WCC_TS_HEAVY_RAIN:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_HEAVY_INTENSITY;
            break;

        case WCC_LIGHT_TS:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_LIGHT_INTENSITY;
            break;

        case WCC_TS:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_MEDIUM_INTENSITY;
            break;

        case WCC_HEAVY_TS:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_HEAVY_INTENSITY;
            break;

        case WCC_RAGGED_TS:
            wd.condition = PWM_THUNDERSTORM;
            wd.intensity = PWM_MEDIUM_INTENSITY;
            break;

        case WCC_TS_LIGHT_DRIZZLE:
    }
}
