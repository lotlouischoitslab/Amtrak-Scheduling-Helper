#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include "math.h"

#include "station.h"
#include "graph.h"



//represents train, which takes source and destination, it updates each stations and tell them that one station is on them atm.
class Train {
    public:
        Train() {};
        Train(std::string src, std::string dest, Graph* graph);
        ~Train() = default;

        std::vector<std::string> getPaths() const {return path_;}
        std::vector<std::vector<std::string>> getEdges() {return edges_;}

    private:
        std::string origin_;
        std::string dest_;
        std::vector<std::string> path_;
        std::vector<std::vector<std::string>> edges_;
        Graph* graph_;
        friend ostream& operator<<(ostream& os, const Train& dt) {
            std::vector<std::string> path = dt.getPaths();
            os << path[0];
            for (int i = 1; i < (int) path.size(); i++) {
                os << " --> " << path[i];
            }
            os << std::endl;
            return os;
        }
};
