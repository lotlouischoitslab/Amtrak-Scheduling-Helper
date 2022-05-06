#include "../includes/train.h"

Train::Train(std::string src, std::string dest, Graph* graph) {
    graph_ = graph;
    origin_ = src;
    dest_ = dest;
    path_ = graph->AStar(src, dest);
    for (int i = 0; i < (int) path_.size() - 1; i++) {
        std::vector<std::string> temp;
        temp.push_back(path_[i]);
        temp.push_back(path_[i+1]);
        edges_.push_back(temp);
    }
    for (int i = 0; i < (int) path_.size(); i++) {
        std::string stn = path_[i];
        graph->get_num_train(stn)->second += 1;
    }
}   