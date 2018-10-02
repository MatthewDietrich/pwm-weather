/**************************************************************
- pwm-weather -  Convert weather data to PWM values
- Copyright (C) 2018  Matthew Dietrich

- This program is free software: you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation, either version
  3 of the License, or (at your option) any later version.

- This program is distributed in the hope that it will be
  useful, but WITHOUT ANY WARRANTY; without even the implied
  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the GNU General Public License for more details.

- You should have received a copy of the GNU General Public
  License along with this program. If not, see
  <http://www.gnu.org/licenses/>

- Contact: <http://github.com/MatthewDietrich>
**************************************************************/

#include "pwm-weather.h"

void convert_temperature_to_pwm(const float temperature, WeatherDataAsPWMValues *wd)
{
    if (wd == NULL) return;
    wd->temperature = convert_value_in_range_to_pwm(temperature, MIN_TEMPERATURE, MAX_TEMPERATURE);
}

void convert_humidity_to_pwm(const float humidity, WeatherDataAsPWMValues *wd)
{
    if (wd == NULL) return;
    wd->temperature = convert_value_in_range_to_pwm(humidity, MIN_HUMIDITY, MAX_HUMIDITY);
}

/**************************************************************
- convert_value_in_range_to_pwm

- Given a floating point value and a range of possible values,
  convert the value to an integer between 0 and 255

- https://stackoverflow.com/questions/573186
**************************************************************/
uint8_t convert_value_in_range_to_pwm(float value, const float minValue, const float maxValue)
{
    // Prevent divide by zero error. There's probably a better way to do this but this will work for now.
    if (minValue >= maxValue) return 0;

    // Boundary check
    if (value > maxValue) value = maxValue;
    else if (value < minValue) value = minValue;
    
    double slope = 1.0 * (PWM_MAX - PWM_MIN) / (maxValue - minValue);
    return (uint8_t)floor((PWM_MIN + slope * (value - minValue)) + 0.5);
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
    if (wd == NULL) return;

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

/**************************************************************
- parse_weather_file

- Given an XML file returned by the OpenWeatherMap API, use
  Tinyxml2 to parse the data and store the values of the
  relevant tags in the WeatherDataAsPWMValues file.

- https://stackoverflow.com/a/52543743/10425938
  Thanks to Remy Lebeau for pointing out some critical errors
**************************************************************/
void parse_weather_file(const char* weatherFileName, WeatherDataAsPWMValues *wd)
{
    if (wd == NULL) return;

    std::cout << weatherFileName << std::endl;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError err = doc.LoadFile(weatherFileName);
    if (err != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error " << (int)err << ": Could not load " << weatherFileName << std::endl;
    }

    tinyxml2::XMLElement *root = doc.RootElement();
    if (root == NULL)
    {
      std::cerr << "Error parsing " << weatherFileName << std::endl;
    }

    float temperature = get_temperature(root);
    int humidity = get_humidity(root);
    int conditionCode = get_condition_code(root);

    convert_temperature_to_pwm(temperature, wd);
    convert_humidity_to_pwm(humidity, wd);
    parse_weather_condition_code(conditionCode, wd);
}

float get_temperature(tinyxml2::XMLElement *xmlRoot)
{
    if (xmlRoot == NULL)
    {
        std::cerr << "get_temperature: Error - null root element" << std::endl;
        return 0.0;
    }

    tinyxml2::XMLElement *temperatureElement = xmlRoot->FirstChildElement("temperature");
    if (temperatureElement == NULL)
    {
        std::cerr << "get_temperature: Error - could not find <temperature> tag" << std::endl;
        return 0.0;
    }

    return temperatureElement->FloatAttribute("value");
}

int get_humidity(tinyxml2::XMLElement *xmlRoot)
{
    if (xmlRoot == NULL)
    {
        std::cerr << "get_humidity: Error - null root element" << std::endl;
        return 0.0;
    }

    tinyxml2::XMLElement *humidityElement = xmlRoot->FirstChildElement("humidity");
    if (humidityElement == NULL)
    {
        std::cerr << "get_humidity: Error - could not find <humidity> tag" << std::endl;
        return 0.0;
    }

    return humidityElement->IntAttribute("value");
}

int get_condition_code(tinyxml2::XMLElement *xmlRoot)
{
    if (xmlRoot == NULL)
    {
        std::cerr << "get_condition_code: Error - null root element" << std::endl;
        return 0.0;
    }

    tinyxml2::XMLElement *weatherElement = xmlRoot->FirstChildElement("weather");
    if (weatherElement == NULL)
    {
        std::cerr << "get_condition_code: Error - could not find <weather> tag" << std::endl;
        return 0.0;
    }

    return weatherElement->IntAttribute("number");
}
