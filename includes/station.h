#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "data.h"

class Station
{
    public:
        //empty constructor to build a station
        Station();
        //main station constructor.  param code = station code, latitude = station latitude, longitude = station longitude
        Station(std::string code, double latitude, double longitude); 
        //function to set the station code to param code
        void set_code(std::string code);
        //functio nthat returns the station code as a string
        std::string get_code();
        //function to set the latitude of the station to param latitude
        void set_lat(double latitude);
        //function to set the longitude of the station to param longitude
        void set_long(double longitude);
        //function that returns the latitude of the station
        double get_lat();
        //function that returns the longitude of the station
        double get_long();
        //function that returns the coordinates of the station as a vector
        std::vector<double> get_coords();
        //checks whether two stations are the same
        bool operator==(Station& rhs);
        //returns the station in a friendly string format
        std::string to_string();
    private:
        //station code
        std::string code_;
        //latitude of station
        double latitude_;
        //longitude of station
        double longitude_;
        //coordinates of station (lat/long)
        std::vector<double> coords_;
};