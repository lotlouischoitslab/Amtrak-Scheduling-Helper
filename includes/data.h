#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;


class Data {
    public:
        Data();
        ~Data() = default;

        //Constructor Takes 2 files first one having conections, and other one having Cordinates station code
        Data(std::string file1, std::string file2);
        //copy constructor
        Data(const Data& other);
        Data& operator=(const Data& other);

        //returns vector of all codes
        std::vector<std::string> getCodes();

        //returns vector of all connected stations to given codes
        std::vector<std::string> getConnections(std::string stn);

        //returns vector of all latitudes of all stations in order
        std::vector<double> getLats();
        //returns vector of all longitude of all stations in order
        std::vector<double> getLongs();

        //returns latitude of given station
        double getLat(std::string code);
        //returns longitude of given station
        double getLong(std::string code);

        //returns latitude of given station idx
        double getLat(int i);
        //returns longitude of given station idx
        double getLong(int i);

        //returns idx of given station
        int    getIdx(std::string stn) {return code_idx_[stn];}

        //returns how many trains are there at a given station
        std::map<std::string, int>::iterator get_num_train(std::string stn) {return num_trains.find(stn);}

    private:
        std::string connections_file_;
        std::string data_file_;
        std::vector<double> lat_;
        std::vector<double> long_;
        std::vector<std::string> code_;
        std::map<std::string, int> code_idx_;
        std::map<std::string, std::vector<std::string>> stations_;
        std::map<std::string, int> num_trains;
};