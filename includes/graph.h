#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include "math.h"
#include <algorithm>
#include "station.h"
#include "data.h"


const double TRAIN_SPEED = 60;
class Graph
{
    public:
        //empty constructor
        Graph();
        ~Graph() {
            if (data_ != nullptr) {
                delete data_;
                data_ = nullptr;
            }
        }
        //Use all stations data and connections data to populate the graph
        Graph(std::string file1, std::string file2);
        //returns all the stations in the graph
        std::vector<std::string> GetStations();
        //distance between 2 stations
        double GetDistance(std::string stn1, std::string stn2);
        //returns vecotr of codes of all stations connected to given stn
        std::vector<std::string> GetConnections(std::string stn);
        //returns true if connected
        bool IsConnected(std::string stn1, std::string stn2);
        //get Station (Node) object
        Station& GetStation(std::string stn);
        //gives weight between 2 stations
        double GetWeight(std::string stn1, std::string stn2);
        //finds the shortest path between two stations
        std::vector<std::string> AStar(std::string src, std::string dest);
        
        //returns whether a path exist between 2 given stations within given num stations or Time
        // BFS_stations doesnt include src station. so path of 6 stations would give true if num_stations >= 5
        bool BFS_stations(std::string src, std::string dest, int num_stations);
        bool BFS_time(std::string src, std::string dest, double time);


        //finds the edges spanning all stations, Prim's or Kruskal's
        std::vector<std::vector<std::string>> SpanAllStation();
        int  TotalSpanWeight() {return span_weight_;}

        //get all edges
        std::vector<std::vector<std::string>> GetEdges() {
            return edges_;
        }
        //sort all edges using direct access memory sort
        std::vector<std::vector<std::string>> SortedEdges();

        Data* get_data() {return data_;}

        //adjency
        std::vector<std::string> operator[](std::string stn) {
            return data_->getConnections(stn);
        }
        //returns iterator of get_num_train
        std::map<std::string, int>::iterator get_num_train(std::string stn) {
            return data_->get_num_train(stn);
        } 

        //returns Miles reduced in MST weight after adding an edge;
        int PotentialEdge(std::string stn1, std::string stn2);

        //returns bool whether station exists
        bool isValidStation(std::string stn);

    private:
        //stations_ = {'code': {'code': distance}}
        std::map<std::string, std::map<std::string, double>> stations_;
        //nodes_ = {'code': Station object}
        std::map<std::string, Station> nodes_;
        //given data object
        Data* data_;
        std::vector<std::vector<std::string>> edges_;

        double span_weight_;
};



//helper dset class for running minimum spanning tree

// our implementation of Disjoint set class
class Dset
{
    public:
        Dset(int n){
            parents = std::vector<int>(n, -1);
            size = std::vector<int>(n, 1);
        }
        int find(int n){
            if(parents.at(n) == -1){
                return n;
            }
            else{
                int parent_idx = find(parents.at(n));
                return parent_idx;
            }
        }
        void set_union(int first, int second){
            int top_idx_1 = find(first);
            int top_idx_2 = find(second);
            if(top_idx_1 == top_idx_2){
                //already connected
                return;
            }
            if(size.at(top_idx_2) < size.at(top_idx_1)){
                parents.at(top_idx_2) = top_idx_1;
                size.at(top_idx_1) += size.at(top_idx_2);
            }
            else{
                parents.at(top_idx_1) = top_idx_2;
                size.at(top_idx_2) += size.at(top_idx_1);
            }

        }
    private:
        std::vector<int> parents;
        std::vector<int> size;
};


 