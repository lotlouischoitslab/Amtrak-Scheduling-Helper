#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "../cs225/catch/catch.hpp"


#include "../includes/data.h"
#include "../includes/graph.h"
#include "../includes/image.h"
#include "../includes/station.h"
#include "../includes/train.h"
#include <iostream>


TEST_CASE("Check Graph structure on all data"){ 
    Graph graph = Graph("data/train_connections.csv", "data/train_data.csv");

    //SMC,AUS,SAS,HOS
    std::vector<std::string> SMC = graph.GetConnections("SMC");

    REQUIRE(SMC.size() == 3);
    REQUIRE((SMC[0] == "AUS" || SMC[0] == "SAS" || SMC[0] == "HOS"));
    REQUIRE((SMC[1] == "AUS" || SMC[1] == "SAS" || SMC[1] == "HOS"));
    REQUIRE((SMC[2] == "AUS" || SMC[2] == "SAS" || SMC[2] == "HOS"));
    REQUIRE((SMC[0] != SMC[1] && SMC[1] != SMC[2] && SMC[0] != SMC[2]));
}

TEST_CASE("Try MST on small graph") {
    Graph graph = Graph("tests/mst_connections.csv", "tests/mst_data.csv");
   
    //          42              77
    // KEE  ---------- MDT-------------- GLN
    // |          _____/                 /  
    // |72      230   _________235______/
    // |   _____/    /  
    // |  /        /   
    // BNL --31--PON --18--- DWT
    
    std::vector<std::vector<std::string>> mst = graph.SpanAllStation();

    REQUIRE(mst.size() == 5);
    //minimum edge is PON DWT, should be first edge visited in mst
    REQUIRE((mst[0][0] == "PON" || mst[0][0] == "DWT"));
    REQUIRE((mst[0][1] == "PON" || mst[0][1] == "DWT"));
    REQUIRE((mst[0][1] != mst[0][0]));

    //maximum edge is MDT GLN should be last edge visited in mst
    REQUIRE((mst[4][0] == "MDT" || mst[4][0] == "GLN"));
    REQUIRE((mst[4][1] == "MDT" || mst[4][1] == "GLN"));
    REQUIRE((mst[0][1] != mst[0][0]));

    //range because weights above are approximations, actual weight should be around 245miles.
    REQUIRE((graph.TotalSpanWeight() > 244 && graph.TotalSpanWeight() < 246));
}

/////////////////////////////////////////////////TESTING A* ALGORITHM FOR THE WHOLE GRAPH//////////////////////////////
TEST_CASE("Try AStar on whole graph") {
    Graph graph = Graph("data/train_connections.csv", "data/train_data.csv");

    std::vector<std::string> route = graph.AStar("CHM", "CHI");

    REQUIRE(route.size() == 6);
    REQUIRE(route[0] == "CHM");
    REQUIRE(route[1] == "RTL");
    REQUIRE(route[2] == "GLM");
    REQUIRE(route[3] == "KKI");
    REQUIRE(route[4] == "HMW");
    REQUIRE(route[5] == "CHI");

    std::vector<std::string> route_rev = graph.AStar("CHI", "CHM");
    REQUIRE(route[0] == route_rev[5]);
    REQUIRE(route[1] == route_rev[4]);
    REQUIRE(route[2] == route_rev[3]);
    REQUIRE(route[3] == route_rev[2]);
    REQUIRE(route[4] == route_rev[1]);
    REQUIRE(route[5] == route_rev[0]);

    //random path length, where multiple route is possible
    route = graph.AStar("SND", "AUS");
    REQUIRE(route.size() == 5);
    route = graph.AStar("WIH", "LIB");
    REQUIRE(route.size() == 5);
    route = graph.AStar("RDW", "HAV");
    REQUIRE(route.size() == 16);
}

/////////////////////////////////TESTING THE A* ALGORITHM FOR SUB GRAPHS ////////////////////////////////////////////////////
TEST_CASE("Try AStar on a sub graph part 1") {
    Graph graph = Graph("data/train_connections.csv", "data/train_data.csv");

    std::vector<std::string> route = graph.AStar("FAR", "EVR");
    
    REQUIRE(route.size() > 10); ////////THIS GRAPH IS A PRETTY LONG ONE


    /////////////////////////////PRINT OUT EACH TRAIN STATION RIGHT NOW/////////////////////////////////////////////////////
    size_t idx = 0;
    while(idx < route.size()) {
        cout << idx << ": " << route[idx] << " ";
        idx++;
    }
    cout << endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    REQUIRE(route[0] == "FAR");
    REQUIRE(route[1] == "GFK");
    REQUIRE(route[2] == "DVL");
    REQUIRE(route[3] == "RUG");
    REQUIRE(route[4] == "MOT");
    REQUIRE(route[5] == "STN");

    REQUIRE(route[6] == "WTN");
    REQUIRE(route[7] == "WPT");
    REQUIRE(route[8] == "GGW");
    REQUIRE(route[9] == "MAL");
    REQUIRE(route[10] == "HAV");
    REQUIRE(route[11] == "SBY");

    REQUIRE(route[12] == "CUT");
    REQUIRE(route[13] == "BRO");
    REQUIRE(route[14] == "GPK");
    REQUIRE(route[15] == "ESM");
    REQUIRE(route[16] == "WGL");
    REQUIRE(route[17] == "WFH");

    REQUIRE(route[18] == "LIB");
    REQUIRE(route[19] == "SPT");
    REQUIRE(route[20] == "SPK");
    REQUIRE(route[21] == "EPH");
    REQUIRE(route[22] == "WEN");
    REQUIRE(route[23] == "LWA");
    REQUIRE(route[24] == "EVR");

}

TEST_CASE("Try AStar on a sub graph part 2") {
    Graph graph = Graph("data/train_connections.csv", "data/train_data.csv");

    std::vector<std::string> route = graph.AStar("FLO", "EKH");
    
    cout << route.size() << endl;
    REQUIRE(route.size() == 28);

    /////////////////////////////PRINT OUT EACH TRAIN STATION RIGHT NOW/////////////////////////////////////////////////////
    size_t idx = 0;
    while(idx < route.size()) {
        cout << idx << ": " << route[idx] << " ";
        idx++;
    }
    cout << endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    REQUIRE(route[0] == "FLO");
    REQUIRE(route[1] == "DIL");
    REQUIRE(route[2] == "FAY");
    REQUIRE(route[3] == "SSM");
    REQUIRE(route[4] == "WLN");
    REQUIRE(route[5] == "RMT");
    REQUIRE(route[6] == "PTB");

    REQUIRE(route[7] == "RVR");
    REQUIRE(route[8] == "ASD");
    REQUIRE(route[9] == "FBG");
    REQUIRE(route[10] == "QAN");
    REQUIRE(route[11] == "WDB");
    REQUIRE(route[12] == "LOR");
    REQUIRE(route[13] == "ALX");

    REQUIRE(route[14] == "WAS");
    REQUIRE(route[15] == "RKV");
    REQUIRE(route[16] == "HFY");
    REQUIRE(route[17] == "MRB");
    REQUIRE(route[18] == "CUM");
    REQUIRE(route[19] == "COV");
    REQUIRE(route[20] == "PGH");

    REQUIRE(route[21] == "CLE");
    REQUIRE(route[22] == "ELY");
    REQUIRE(route[23] == "SKY");
    REQUIRE(route[24] == "TOL");
    REQUIRE(route[25] == "BYN");
    REQUIRE(route[26] == "WTI");
    REQUIRE(route[27] == "EKH");

    
}




//////////////////////////////////////////////////////////BFS ALGORITHM TESTING//////////////////////////////////

TEST_CASE("Try BFS_time and BFS_station on whole data") {
    Graph graph = Graph("data/train_connections.csv", "data/train_data.csv");

    bool result;

    result = graph.BFS_stations("CHM", "CHI", 5);
    REQUIRE(result == true);
    result = graph.BFS_stations("CHM", "CHI", 6);
    REQUIRE(result == true);
    result = graph.BFS_stations("CHM", "CHI", 4);
    REQUIRE(result == false);

    result = graph.BFS_stations("RDW", "HAV", 15);
    REQUIRE(result == true);
    result = graph.BFS_stations("RDW", "HAV", 40);
    REQUIRE(result == true);
    result = graph.BFS_stations("RDW", "HAV", 14);
    REQUIRE(result == false);

    //it takes roughly 1.5 to 2 hours to go to chm to chi
    result = graph.BFS_time("CHM", "CHI", 2);
    REQUIRE(result == true);
    result = graph.BFS_time("CHM", "CHI", 10);
    REQUIRE(result == true);
    result = graph.BFS_time("CHM", "CHI", 1);
    REQUIRE(result == false);
}




///////////////////////////////////////////TESTING FOR TRAVERSAL OF MULTIPLE TRAINS ON ONE LINE//////////////////////

TEST_CASE("Checking traversal of multiple trains part 1"){
    Graph* graph = new Graph("data/train_connections.csv", "data/train_data.csv");

    std::string stn1 = "DRT";
    std::string stn2 = "SMC";

    std::vector<std::string> train0_path =  graph->AStar(stn1, stn2);
    REQUIRE(train0_path.size() == 3);

    double weight_train0 = graph->GetWeight(stn1, "SAS");

    Train train1 = Train(stn1, stn2, graph);
    std::vector<std::string> train1_path =  train1.getPaths();
    REQUIRE(train1_path.size() == 3);

    double weight_train1 = graph->GetWeight(stn1, "SAS");

    int same = 1;
    for (int i = 0; i < (int) train0_path.size(); i++) {
        if (train0_path[i] != train1_path[i]) {
            same = 0;
        }
    }

    REQUIRE(same);


    //crowded by train, it's gonna take detour
    Train train10;
    for (int i = 0; i < 30; i++) {
        train10 = Train(stn1, stn2, graph);
    }

    double weight_train10 = graph->GetWeight(stn1, "SAS");

    std::vector<std::string> train10_path =  train10.getPaths();
    REQUIRE(train10_path.size() > 3);
    
    //weights of edges increased as more trains are on it.
    REQUIRE(weight_train10 > weight_train1);
    REQUIRE(weight_train10 > weight_train0);
    REQUIRE(weight_train1 > weight_train0);
} 


TEST_CASE("Checking traversal of multiple trains part 2"){
    Graph* graph = new Graph("data/train_connections.csv", "data/train_data.csv");

    std::string stn1 = "ATL";
    std::string stn2 = "GNS";

    std::vector<std::string> train0_path =  graph->AStar(stn1, stn2);
    //cout << train0_path.size() << endl;

    REQUIRE(train0_path.size() == 2);
    double weight_train0 = graph->GetWeight(stn1, "GNS");
    //cout << weight_train0 << endl;

    Train train1 = Train(stn1, stn2, graph);
    std::vector<std::string> train1_path =  train1.getPaths();
    double weight_train1 = graph->GetWeight(stn1, "GNS");
    REQUIRE(train1_path.size() == 2);

    Train train2 = Train(stn1, stn2, graph);
    std::vector<std::string> train2_path =  train2.getPaths();
    double weight_train2 = graph->GetWeight(stn1, "GNS");
    REQUIRE(train2_path.size() == 2);


    Train train3 = Train(stn1, stn2, graph);
    std::vector<std::string> train3_path =  train3.getPaths();
    double weight_train3 = graph->GetWeight(stn1, "GNS");
    REQUIRE(train3_path.size() == 2);


    Train train4 = Train(stn1, stn2, graph);
    std::vector<std::string> train4_path =  train4.getPaths();
    double weight_train4 = graph->GetWeight(stn1, "GNS");
    REQUIRE(train4_path.size() == 2);


    // due to overcrowding the train needs to detour
    Train train_det = Train(stn1, stn2, graph);
    std::vector<std::string> train_detpath =  train_det.getPaths();
    // cout << train_detpath.size() << endl;
    double weight_traindet = graph->GetWeight(stn1, "GNS");
    REQUIRE(train_detpath.size() < 4);
    
    // //We need to make sure the weight of the trains are increasing by order//////////////////////
    REQUIRE(weight_train1 > weight_train0); //Weight of the first train should be greater 
    REQUIRE(weight_train2 > weight_train1); 
    REQUIRE(weight_train3 > weight_train2);
    REQUIRE(weight_traindet > weight_train4);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
