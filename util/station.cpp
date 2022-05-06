#include <iostream>
#include <string>
#include <vector>

#include "../includes/station.h"


Station::Station(){ 
}

Station::Station(std::string code, double latitude, double longitude){
    code_ = code;
    latitude_ = latitude;
    longitude_ = longitude;
    coords_.push_back(latitude_);
    coords_.push_back(longitude_);
}

void Station::set_code(std::string code){
    code_ = code;
}

std::string Station::get_code(){
    return code_;
}

void Station::set_lat(double latitude){
    latitude_ = latitude;
}

void Station::set_long(double longitude){
    longitude_ = longitude;
}

double Station::get_lat(){
    return latitude_;
}

double Station::get_long(){
    return longitude_;
}

std::vector<double> Station::get_coords(){
    return coords_;
}

bool Station::operator==(Station& rhs){
    //todo
    return false;
}

std::string Station::to_string(){
    return code_;
}
