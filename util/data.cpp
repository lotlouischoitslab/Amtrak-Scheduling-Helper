#include "../includes/data.h"

using namespace std;

Data::Data() {
    
}
Data::Data(std::string file1, std::string file2)
: connections_file_(file1), data_file_(file2)
{
    std::vector<std::string> row;
    std::string line;
    std::string word;
    fstream file(connections_file_, ios::in);
    if(file.is_open()) {
        while(getline(file, line)) {
            row.clear();
            stringstream ss(line);
            int count = 0;

            std::string temp_station;
            std::vector<std::string> temp_connections;
            while(getline(ss, word, ',')) {
                if(count == 0) {
                    temp_station = word;
                } else if(word != "None") {
                    temp_connections.push_back(word);
                } else {
                    break;
                }
                count++;
            }
            if(!temp_connections.empty()) {
                stations_[temp_station] = temp_connections;
                num_trains[temp_station] = 1;
            } else {
                stations_[temp_station] = temp_connections;
            }
            
        }
    } else {
        std::cout << "file not found!" << std::endl;
    }
    

    fstream data_file(data_file_, ios::in);
    if (data_file.is_open()) {
        int idx = 0;
        while (getline(data_file, line)) {
            row.clear();
            stringstream ss(line);
            int count = 0;

            std::string temp_station;
            std::vector<std::string> temp_connections;
            while(getline(ss, word, ',')) {
                if(count == 0) {
                    lat_.push_back(std::stod(word));
                } else if(count == 1) {
                    long_.push_back(std::stod(word));
                } else if (count == 2) {
                    code_.push_back(word);
                    code_idx_.insert(std::pair<std::string, int>(word, idx));
                    idx++;
                }
                count++;
            }
        }
    }


}

std::vector<std::string> Data::getCodes(){
    return code_;
}
std::vector<double> Data::getLats(){
    return lat_;
}
std::vector<double> Data::getLongs(){
    return long_;
}
double Data::getLat(std::string code){
    return getLat(code_idx_[code]);
}
double Data::getLong(std::string code){
    return getLong(code_idx_[code]);
}
double Data::getLat(int i){
    return lat_.at(i);
}
double Data::getLong(int i){
    return long_.at(i);
}

std::vector<std::string> Data::getConnections(std::string stn){
    return stations_[stn];
}