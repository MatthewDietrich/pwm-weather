/**************************************************************
Weather condition codes as defined in:
https://openweathermap.org/weather-conditions

The point of including all of these incredibly specific codes
is for the sake of customization. Someone may not agree that
one or more of these codes should necessarily map to a specific
point on the gauge. Someone may think that "freezing rain"
should point to "rain" instead of "snow" for instance.

This allows them to change that.
**************************************************************/
enum weatherConditionCode
{
    // 200 block: Thunderstorm
    WCC_TS_LIGHT_RAIN              = 200,
    WCC_TS_RAIN                    = 201,
    WCC_TS_HEAVY_RAIN              = 202,
    WCC_LIGHT_TS                   = 210,
    WCC_TS                         = 211,
    WCC_HEAVY_TS                   = 212,
    WCC_RAGGED_TS                  = 221,
    WCC_TS_LIGHT_DRIZZLE           = 230,
    WCC_TS_DRIZZLE                 = 231,
    WCC_TS_HEAVY_DRIZZLE           = 232,

    // 300 block: Drizzle
    WCC_LIGHT_DRIZZLE              = 300,
    WCC_DRIZZLE                    = 301,
    WCC_HEAVY_DRIZZLE              = 302,
    WCC_LIGHT_DRIZZLE_RAIN         = 310,
    WCC_DRIZZLE_RAIN               = 311,
    WCC_HEAVY_DRIZZLE_RAIN         = 312,
    WCC_SHOWER_RAIN_DRIZZLE        = 313,
    WCC_HEAVY_SHOWER_RAIN_DRIZZLE  = 314,
    WCC_SHOWER_DRIZZLE             = 321,

    // 500 block: Rain
    WCC_LIGHT_RAIN                 = 500,
    WCC_MODERATE_RAIN              = 501,
    WCC_HEAVY_RAIN                 = 502,
    WCC_VERY_HEAVY_RAIN            = 503,
    WCC_EXTREME_RAIN               = 504,
    WCC_FREEZING_RAIN              = 511,
    WCC_LIGHT_SHOWER_RAIN          = 520,
    WCC_SHOWER_RAIN                = 521,
    WCC_HEAVY_SHOWER_RAIN          = 522,
    WCC_RAGGED_SHOWER_RAIN         = 531,

    // 600 block: Snow
    WCC_LIGHT_SNOW                 = 600,
    WCC_SNOW                       = 601,
    WCC_HEAVY_SNOW                 = 602,
    WCC_SLEET                      = 611,
    WCC_SHOWER_SLEET               = 612,
    WCC_LIGHT_RAIN_SNOW            = 615,
    WCC_RAIN_SNOW                  = 616,
    WCC_LIGHT_SHOWER_SNOW          = 620,
    WCC_SHOWER_SNOW                = 621,
    WCC_HEAVY_SHOWER_SNOW          = 622,

    // 700 block: Atmosphere
    WCC_MIST                       = 701,
    WCC_SMOKE                      = 711,
    WCC_HAZE                       = 721,
    WCC_SAND_DUST_WHIRLS           = 731,
    WCC_FOG                        = 741,
    WCC_SAND                       = 751,
    WCC_DUST                       = 761,
    WCC_VOLCANIC_ASH               = 762,
    WCC_SQUALLS                    = 771,
    WCC_TORNADO                    = 781,

    // 800 block: Clear, clouds
    WCC_CLEAR                      = 800,
    WCC_FEW_CLOUDS                 = 801,
    WCC_SCATTERED_CLOUDS           = 802,
    WCC_BROKEN_CLOUDS              = 803,
    WCC_OVERCAST_CLOUDS            = 804   
};
