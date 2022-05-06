#include "../includes/graph.h"

// // empty constructor
// Graph::Graph() {

// }
//Use all stations data and connections data to populate the graph
Graph::Graph(std::string file1, std::string file2) {
    data_ = new Data(file1, file2);
    std::vector<std::string> stations = data_->getCodes();
    for (int i = 0; i < (int) stations.size(); i++) {
        std::string stn_code = stations[i];
        Station stn_node = Station(stn_code, data_->getLat(stn_code), data_->getLong(stn_code));
        std::map<std::string, double> connection_map;
        std::vector<std::string> connections = data_->getConnections(stn_code);
        for (int j = 0; j < (int) connections.size(); j++) {
            std::string connection = connections[j];
            if (stn_code < connection) {
                std::vector<std::string> edge;
                edge.push_back(stn_code);
                edge.push_back(connection);
                edges_.push_back(edge);
            }
            double dist = GetDistance(stn_code, connection) / TRAIN_SPEED;   
            connection_map.insert(std::pair<std::string, double>(connection, dist));
        } 
        stations_.insert(std::pair<std::string, std::map<std::string, double>>(stn_code, connection_map));
        nodes_.insert(std::pair<std::string, Station>(stn_code, stn_node));
    }
}
// //prints the possible errors in our data and returns whether there is some possible errors
// bool Graph::Validity() {

// }
//returns all the stations in the graph
std::vector<std::string> Graph::GetStations() {
    return data_->getCodes();
}
// //distance between 2 stations
double Graph::GetDistance(std::string stn1, std::string stn2) {
    double lat1 = data_->getLat(stn1);
    double long1 = data_->getLong(stn1);
    double lat2 = data_->getLat(stn2);
    double long2 = data_->getLong(stn2);
    double earth_radius = 3959.87;
    lat1 = (lat1*3.14159265358979) / ((double)180);
    long1 = (long1*3.14159265358979) / ((double)180);
    lat2 = (lat2*3.14159265358979) / ((double)180);
    long2 = (long2*3.14159265358979) / ((double)180);
    double q = acos(1.0*sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(long1-long2));
    double distance_btwn = earth_radius*q;
    return distance_btwn;
}
//returns vecotr of codes of all stations connected to given stn
std::vector<std::string> Graph::GetConnections(std::string stn) {
    return data_->getConnections(stn);
}

// //returns true if connected
// bool Graph::IsConnected(std::string stn1, std::string stn2) {

// }
// //get Station (Node) object
Station& Graph::GetStation(std::string stn) {
    return nodes_[stn];
}

//get's weight between two nodes
double Graph::GetWeight(std::string stn1, std::string stn2) {
    double wt = stations_[stn1][stn2];
    int num_train = get_num_train(stn1)->second;
    if (wt < 1) {
        return wt + wt * (1-wt) * (1-wt) * (num_train - 1)* (num_train - 1);
    } 
    return wt + ((num_train - 1)* (num_train - 1)/(wt*wt))/(10 - wt);
}

//finds the shortest path between two stations
std::vector<std::string> Graph::AStar(std::string src, std::string dest) {
    std::priority_queue <std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>> > priority;
    priority.push(std::pair<double, std::string>(0, src));

    std::map<std::string, std::string>  prev;
    std::map<std::string, double>  dist;

    prev[src] = src;
    dist[src] = 0;

    while (!priority.empty()) {
        std::string curr = priority.top().second;
        priority.pop();

        if (curr == dest) {
            break;
        }

        for (std::string adj: GetConnections(curr)) {
            double dist_new = dist[curr] + GetWeight(curr, adj);
            if (dist.find(adj) == dist.end() || dist_new < dist[adj]) {
                dist[adj] = dist_new;
                double weight = dist_new + (GetDistance(adj, dest)/TRAIN_SPEED);
                priority.push(std::pair<double, std::string>(weight, adj));
                prev[adj] = curr;
            }
        }

        
    }

    std::vector<std::string> path;
    std::string curr = dest;

    while (1) {
        if (curr == src) {
            path.push_back(curr);
            break;
        }
        path.push_back(curr);
        curr = prev[curr];
    }

    std::reverse(path.begin(), path.end());

    return path;
}   
//finds the path spanning all stations, Kruskal's
std::vector<std::vector<std::string>> Graph::SpanAllStation() {
    SortedEdges();
    Dset disjoint_set((int) nodes_.size());

    double total_distance = 0;

    std::vector<std::vector<std::string>> mst;

    for (int i = 0; i < (int) edges_.size(); i++) {
        std::string stn1 = edges_[i][0];
        std::string stn2 = edges_[i][1];
        double dist = GetDistance(stn1, stn2);
        int stn1_idx = data_->getIdx(stn1);
        int stn2_idx = data_->getIdx(stn2);
        if (disjoint_set.find(stn1_idx) != disjoint_set.find(stn2_idx)) {
            disjoint_set.set_union(stn1_idx, stn2_idx);
            total_distance += dist;
            std::vector<std::string> temp;
            temp.push_back(stn1);
            temp.push_back(stn2);
            mst.push_back(temp);
        }
    }
    span_weight_ = total_distance;
    return mst;
}

std::vector<std::vector<std::string>> Graph::SortedEdges() {
    std::vector<std::vector<int>> das;
    for (int i = 0; i < 400; i++) {
        std::vector<int> temp;
        das.push_back(temp);
    }
    for (int i = 0; i < (int) edges_.size(); i++) {
        std::vector<std::string> edge = edges_[i];
        int idx = GetDistance(edge[0], edge[1]);
        das[idx].push_back(i);
    }
    std::vector<std::vector<std::string>> sorted;
    for (int i = 0; i < (int) das.size(); i++) {
        std::vector<int> temp = das[i];
        if (temp.empty()) {
            continue;
        }
        for (int j = 0; j < (int) temp.size(); j++) {
            int idx = temp[j];
            sorted.push_back(edges_[idx]);
        }
    }
    edges_ = sorted;

    return sorted;
}


bool Graph::BFS_stations(std::string src, std::string dest, int num_stations) {
    std::map<std::string, bool>  visited;
    std::map<std::string, int>  dist;

    std::queue<std::string>  bfs;
    
    //marking source visited and adding in queue
    visited[src] = true;
    dist[src] = 0;
    bfs.push(src);

    while (!bfs.empty()) {
        std::string curr = bfs.front();
        bfs.pop();
        std::vector<std::string> adjs = GetConnections(curr);
        for (int i = 0; i < (int) adjs.size(); i++) {
            std::string adj = adjs[i];
            std::map<std::string, bool>::iterator it = visited.find(adj);
            if (it == visited.end()) {
                visited[adj] = true;
                dist[adj] = dist[curr] + 1;
                if (dist[adj] < num_stations) {
                    bfs.push(adj);
                }
            }
            if (adj == dest) {
                return true;
            }
        }
    }
    return false;

}
bool Graph::BFS_time(std::string src, std::string dest, double total_time) {
    std::map<std::string, bool>  visited;
    std::map<std::string, double>  time;

    std::queue<std::string>  bfs;
    
    //marking source visited and adding in queue
    visited[src] = true;
    time[src] = 0;
    bfs.push(src);

    while (!bfs.empty()) {
        std::string curr = bfs.front();
        bfs.pop();
        std::vector<std::string> adjs = GetConnections(curr);
        for (int i = 0; i < (int) adjs.size(); i++) {
            std::string adj = adjs[i];
            std::map<std::string, bool>::iterator it = visited.find(adj);
            if (it == visited.end()) {
                visited[adj] = true;
                time[adj] = time[curr] + GetWeight(adj, curr);
                if (time[adj] < total_time) {
                    bfs.push(adj);
                }
            }
            if (adj == dest) {
                return true;
            }
        }
    }
    return false;
}


//returns Miles reduced in MST weight after adding an edge;
int Graph::PotentialEdge(std::string stn1, std::string stn2) {
    SpanAllStation();
    double span_weight_original = span_weight_;

    stations_[stn1][stn2] = GetWeight(stn1, stn2);
    stations_[stn2][stn1] = GetWeight(stn1, stn2);

    std::vector<std::string> temp;
    temp.push_back(stn1);
    temp.push_back(stn2);

    edges_.push_back(temp);

    SpanAllStation();
    double span_weight_new= span_weight_;

    return (span_weight_new - span_weight_original) * TRAIN_SPEED;
}   


bool Graph::isValidStation(std::string stn) {
    std::map<std::string, Station>::iterator it = nodes_.find(stn);
    return it != nodes_.end();
}