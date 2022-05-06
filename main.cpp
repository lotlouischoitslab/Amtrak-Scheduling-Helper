#include "includes/data.h"
#include "includes/graph.h"
#include "includes/image.h"
#include "includes/station.h"
#include "includes/train.h"
#include <iostream>

void  UserGuide();
void  PrintVector(std::vector<std::string> vec);
bool isNumber(const std::string& str, bool integer);

int main(int argc, char* argv[]) {
    Graph* graph = new Graph("data/train_connections.csv", "data/train_data.csv");

    // for (int i = 0; i < 10; i++) {
    //     Train t0 = Train("DRT", "SMC", graph);
    //     std::cout << t0;
    // }

    if (argc < 3) {
        UserGuide();
        return 0;
    }

    std::string sub = argv[1];
    if (argc > 5 || sub == "-trains") {
        std::string sub_func = argv[1];
        if (sub_func == "-trains") {
            std::string out = argv[argc - 1];
            if (out.size() < 5 || out[out.size() - 1] != 'g' || out[out.size() - 2] != 'n' || out[out.size() - 3] != 'p' || out[out.size() - 4] != '.') {
                UserGuide();
                return 0;
            }
            std::vector<std::string> stations;
            for (int i = 2; i < argc - 1; i++) {
                std::string stn = argv[i];
                if (!graph->isValidStation(stn)) {
                    UserGuide();
                    return 0;
                }
                stations.push_back(stn);
            }

            if (stations.size() % 2 != 0) {
                UserGuide();
                return 0;
            }
            std::vector<Train> trains;
            for (int i = 0; i < (int) stations.size(); i+=2) {
                std::string stn1 = stations[i];
                std::string stn2 = stations[i+1];
                Train train(stn1, stn2, graph);
                std::cout << "Path from " << stn1 << " to " << stn2 << ": ";
                std::cout << train;
                trains.push_back(train);
            }

            std::cout << "Loading Image now. It takes roughly 14 seconds for entire process... " << std::endl; 
            Image img("static/usmap.png", "static/worldmap.png", graph);
            img.plot_paths(9,240);
            img.PlotTrains(trains);
            img.plot_stations(9, 0);
            std::cout << "Writing Image to your given path now. It takes roughly 14 seconds for entire process... " << std::endl; 
            img.SaveImg(out);
            return 0;
        }
        // TODO: trains command 
    }
    //./amtrak [stn1] [stn2]: This command will print out path between given two stations
    // TODO: to check valid station
    if (argc == 3) {
        std::string one = argv[1];
        if (one == "-mst") {
            std::string out = argv[2];
            if (out.size() < 5 || out[out.size() - 1] != 'g' || out[out.size() - 2] != 'n' || out[out.size() - 3] != 'p' || out[out.size() - 4] != '.') {
                UserGuide();
                return 0;
            }
            std::vector<std::vector<std::string>> edges = graph->SpanAllStation();
            std::cout << "Loading Image now. It takes roughly 14 seconds for entire process... " << std::endl; 
            Image img("static/usmap.png", "static/worldmap.png", graph);
            img.plot_paths(9,240);
            img.plot_paths(edges, 2, 80);
            img.plot_stations(9, 0);
            std::cout << "Writing Image to your given path now. It takes roughly 14 seconds for entire process... " << std::endl; 
            img.SaveImg(out);
            return 0;
        }

        std::string stn1 = argv[1];
        std::string stn2 = argv[2];
        if (!graph->isValidStation(stn1) || !graph->isValidStation(stn2)) {
            UserGuide();
            return 0;
        }
        std::vector<std::string> path = graph->AStar(stn1, stn2);
        PrintVector(path);
        return 0;
    }
    // ./amtrak [stn1] [stn2] [out.png]
    if (argc == 4) {
        std::string stn1 = argv[1];
        std::string stn2 = argv[2];
        std::string out = argv[3];
        if (!graph->isValidStation(stn1) || !graph->isValidStation(stn2)) {
            UserGuide();
            return 0;
        }
        if (out.size() < 5 || out[out.size() - 1] != 'g' || out[out.size() - 2] != 'n' || out[out.size() - 3] != 'p' || out[out.size() - 4] != '.') {
            UserGuide();
            return 0;
        }
        std::vector<std::string> path = graph->AStar(stn1, stn2);
        PrintVector(path);
        //TODO: plot [path] on image and save it at address stored at [out]
        std::vector<std::vector<std::string>> edges;
        for (int i = 1; i < (int) path.size(); i++) {
            std::vector<std::string> temp;
            temp.push_back(path[i - 1]);
            temp.push_back(path[i]);
            edges.push_back(temp);
        }
        std::cout << "Loading Image now. It takes roughly 14 seconds for entire process... " << std::endl; 
        Image img("static/usmap.png", "static/worldmap.png", graph);
        img.plot_paths(9,240);
        img.plot_paths(edges, 8, 89);
        img.plot_stations(9, 0);
        std::cout << "Writing Image to your given path now. It takes roughly 14 seconds for entire process... " << std::endl; 
        img.SaveImg(out);
        return 0;
    }

    if (argc == 5) {
        std::string sub_func = argv[1];
        if (sub_func == "-n") {
            std::string stn1 = argv[2];
            std::string stn2 = argv[3];
            std::string num_stations_str = argv[4];
            if (!graph->isValidStation(stn1) || !graph->isValidStation(stn2) || !isNumber(num_stations_str, true)) {
                UserGuide();
                return 0;
            }
            int num_stations = std::stoi(num_stations_str);
            bool valid = graph->BFS_stations(stn1, stn2, num_stations);
            if (valid) {
                std::vector<std::string> path = graph->AStar(stn1, stn2);
                PrintVector(path);
                std::cout << "Path is possible with " <<  num_stations << " stations" << std::endl;
            }
            else {
                std::cout << "Path is not possible with " <<  num_stations << " stations" << std::endl;
            }
            return 0;
        }
        if (sub_func == "-t") {
            std::string stn1 = argv[2];
            std::string stn2 = argv[3];
            std::string time_str = argv[4];
            if (!graph->isValidStation(stn1) || !graph->isValidStation(stn2) || !isNumber(time_str, false)) {
                UserGuide();
                return 0;
            }
            double time = std::stod(time_str);
            bool valid = graph->BFS_time(stn1, stn2, time);
            if (valid) {
                std::vector<std::string> path = graph->AStar(stn1, stn2);
                PrintVector(path);
                std::cout << "You can reach from " << stn1 << " to " << stn2 << " within " <<  time << " hours" << std::endl;
            }
            else {
                std::cout << "You can not reach from " << stn1 << " to " << stn2 << " within " <<  time << " hours" << std::endl;
            }
            return 0;
        }

        

        //todo when subfunc is mst or trains
    }
    
    UserGuide();
    return 0;
}


void  UserGuide() {
    std::cout << "You can run following commands:" << std::endl;
    std::cout << std::endl;
    std::cout << "./amtrak [stn1] [stn2]" << std::endl;
    std::cout << "This command will print out path between given two stations" << std::endl;
    std::cout << std::endl;
    std::cout << "./amtrak [stn1] [stn2] [out.png]" << std::endl;
    std::cout << "This command will print out path between given two stations and save the output to given png file location" << std::endl;
    std::cout << std::endl;
    std::cout << "./amtrak [-n] [stn1] [stn2] [number]" << std::endl;
    std::cout << "This command will output whether it's possible to go from station 1 to station 2 within number of stops contraint" << std::endl;
    std::cout << std::endl;
    std::cout << "./amtrak [-t] [stn1] [stn2] [time]" << std::endl;
    std::cout << "This command will output whether it's possible to go from station 1 to station 2 within given time" << std::endl;
    std::cout << std::endl;
    std::cout << "./amtrak -mst [out.png]" << std::endl;
    std::cout << "This command will let you save the MST of amtrak stationsof png file" << std::endl;
    std::cout << std::endl;
    std::cout << "./amtrak -trains [stn1 src] [stn1 dest] [stn2 src] [stn2 dest] [stn3 src] [stn3 dest] ... [out.png]" << std::endl;
    std::cout << "This command will print paths between all those stations where each path would take previous trains in consideration" << std::endl;
    std::cout << std::endl;
}

void  PrintVector(std::vector<std::string> vec) {
    std::cout << vec[0];
    for (int i = 1; i < (int) vec.size(); i++) {
        std::cout << " --> " << vec[i];
    }
    std::cout << std::endl;
}


bool isNumber(const std::string& str, bool integer)
{   
    int fl = 0;
    for (char const &c : str) {
        if (std::isdigit(c) == 0) {
            if (c == '.' && fl == 0 && integer == false) {
                fl = 1;
                continue;
            }
            return false;
        }
    }
    return true;
}