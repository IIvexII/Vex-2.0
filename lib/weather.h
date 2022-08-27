#include "header.h"

#pragma once

class Weather
{   public:
        string city;
        string country;
        string temprature;
        string feelsLike;
        string description;
        string lon;
        string lat;
        string pressure;
        string humidity;
        string visibility;

        Weather()
        {
            city = "";
            country = "";
            temprature = "";
            feelsLike = "";
            description = "";
            lon = "";
            lat = "";
            pressure = "";
            humidity = "";
            visibility = "";
        }
};