# CS 225 Final Project: Optimal Route for Automated Trains in Intelligent Transportation Systems (ITS)

## Contributors
- Joshua Brown (CS + Advertising)
- Sam Gupta (CS)
- Louis Sungwoo Cho (CEE Major / CS Minor)
- Abhi Vinnakota (CS)

## Leading Question
In a world where Artificial Intelligence (AI), 5G LTE and Internet of Things (IoT) are changing our transportation systems, Intelligent Transportation Systems (ITS) in both Civil and Environmental Engineering and Computer Science are becoming a main topic when discussing futuristic urban mobility for Smart Cities ranging from self-driving cars, automated public transportation systems, monorails, light rails and many more. There are many different types of mobility passengers use to travel from one point to another. In this project, our team will analyze a dataset of Amtrak data of all train stations to determine the optimal path for a self-driving train. We will animate the movement of the train on the path to visualize the path that the train will take as determined by the algorithm.  We plan on using A star’s algorithm to find the shortest path (time wise) between any two Amtrak stations.  In addition to this, we want to build a path wherein a cross-country train could visit all of the Amtrak stations in the most time-efficient way possible.  To do this, we will use Prim’s or Kruskal’s algorithm.  This will return a way for such a train to travel and visit all of the stations in the most efficient way possible.

## Data Acquisition and Processing

### Data Format
For our project, we plan to use a dataset with all of the Amtrak stations in the US and their locations (via addresses, station names/codes, etc.).  Likewise, we will expand this dataset with latitude and longitude coordinates.  Finally, our dataset will include all of the connections between each Amtrak station.  The base dataset is available at: https://hifld-geoplatform.opendata.arcgis.com/datasets/amtrak-stations/explore?location=39.528931%2C-90.323756%2C5.00.  We are only using the train stations (not all of the bus stations).  This dataset (the  stations that we are using - not bus) have roughly 500 data points.  We are manually entering all of the data connections (each station’s connected stations).  Similarly, we are using math based on the latitude and longitude coordinates of each station to calculate the distance between two consecutive stations. We have divided the stations between us, and so far we have already got 30% of the stations done. So, we are confident it will be done soon. Overall, it's been added manually by all of us.

### Data Correction
We are checking that all of the stations are not isolated (this means that the graph is connected - there should only be one connected component will all nodes).  Also, the distance between two consecutive stations should not be more than the farthest actual distance between two Amtrak stations (we will check but it is roughly 300 miles).  Finally, we will make sure that the number of connections is no more than the actual number of connections for each Amtrak station (roughly 6). After we process this data, we will convert the distance in time so that we can use that as our weights in the graph for all of our graph algorithms.  We are using time instead of distance so that we can get better output and also for the possibility of multiple trains with potentially overlapping routes.  

### Data Storage
We are going to use a connected weighted graph to store our data.  To physically do this in C++ we are going to use an unordered map with station code as the key and another unordered_map as the value.  Inside this value’s unordered_map, we are going to have each of the connected stations as keys and the time between the origin station and this connected station as the value. To calculate the time, we will divide the distance between the stations by average train speed initially (weight = Distance / Avg speed of train), and we are using time instead of distance as we can update the weights to replicate time delay in case of multiple trains dynamically (new_weight = weight + constant * num_trains). Consequenlty it would be same as just using distance at start but in case of multiple trains it would be able to represent congestion which is easier to update if we are using time as our weights. So if the station is Nodes (N) of our graph and connections are edges (E). The space complexity is O(|N| + |E|) for our graph. Along with this we will have multiple smaller data structures like Arrays of O(|N|) to store all the information about nodes such as Latitudes and Longitudes. Each station node would include these values within a struct.

## Graph Algorithms
Dynamic Programming will be very crucial in our project because we will be using DP algorithms to find the most optimal path in the Amtrak network. We will be mainly using A star’s Shortest Path Algorithm for our project, along with Prim’s or Kruskal’s algorithm to find the ideal path covering all amtrak stations. We could also use DFS to animate the trains over the path to form a gif. Our input would be the graph data structure as described above. Briefly for A* star we have time as weight for each edge (connecting two stations).
The main output of A* star will be a route of nodes that has the most optimal sum of weights in our graph network and Prim’s algorithm would output the shortest path covering all Amtrak stations. Our ideal goal is O(|E| + |N|) complexity for A star algorithm in our case. (It's B^d where d represents path distance and B is average number of connections, however since we have not that many different nodes, O(|E| + |N|) is better representative of runtime complexity since most nodes would be marked visited.)

## Timeline
The first task is acquiring the Amtrak data and performing any necessary data cleaning in order to get the dataset ready for our project. We will then be focusing on turning the dataset into a Struct and getting our data structures ready for use in our graph algorithms. The first algorithm we will tackle is A star’s Shortest Path algorithm to find the optimal path for the train. Once we implement this algorithm, we will then focus on using Prim’s or Kruskal’s algorithm to find the optimal path which covers all of the Amtrak stations. If we have time remaining, we will use DFS to animate the path of the trains in a GIF. Here is the timeline for the project:

### Proposed Timeline
By April 1: Prepare Amtrak data in a CSV file with relevant features, clean the data and prepare it for use

By April 8: Write all the functions signatures and descriptions to create the general outline of all the project, this would make collaboration easier and would give a sense of direction for the project.

By April 15: Then we will locate all the amtrak stations on the US map and display that, this would also help to see the common bugs in our code and be able to give us pixel offset from coordinates of the station. We should also be able to create the paths between two stations.

By April 22: Then we will finally implement A star’s algorithm to output the path which would be the vector of nodes.

By April 29: User iterator and DFS or some other algorithm depending on the situation we would create the animation of a single train over the path.

By May 6: Since time is our weight, in case we have time remaining we could add multiple trains, and change the weights dynamically based on that so that multiple trains can flow at the same time.  Finally, the project should be polished and working at this time.
