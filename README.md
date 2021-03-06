# Amtrak Scheduling Helper

### Contributors:
- Sambhav Gupta (Computer Science)
- Joshua Brown (Computer Science + Advertising)
- Louis Sungwoo Cho (Civil and Environmental Engineering Major and Computer Science Minor)
- Abhi Vinnakota (Computer Science)

# Structure 

Presentation, result.MD is located in root directory, All the main .h files are in includes folder which includes all descriptions, whereas code ".cc" files are in src folder, and finaly all test files and mock datset for test is in test folder. We also have static folder which contains static images which are essential for our program, and all the output images are generated in given path. You can run following commands to compile the code in your machine in root directory and subsequently run normal commands as mentioned in rest of the README to interact with our software.

    make test
    make exec
    make

# Motivation
We designed this project as a way to find the most efficient route between two Amtrak stations in the US since there was no dedicated software or website to help you plan your Amtrak route with a visual map and additional functionality.  We also wanted to make it usable for the Amtrak company so that they can run multiple trains at the same time - so they can find the quickest way for each train.  In addition, we wanted to find whether or not two stations are reachable in a set amount of time and our project is able to determine this. 

# Functionalities & Usage
Our program can take in many arguments from the user and will output the data asked for as well as a visual representation of the map as a whole
The valid inputs the user can provide when calling the function are as follows and their uses are listed after each one:


    ./amtrak [stn1] [stn2]

This command will print out path between stations [stn1] and [stn2]
    
    ./amtrak [stn1] [stn2] [out.png]

This command will print out path between the stations [stn1] and [stn2] and save the output to given png file location

    ./amtrak [-n] [stn1] [stn2] [number]

This command will output whether it's possible to go from station [stn1] to station [stn2] within [number] of stops
    
    ./amtrak [-t] [stn1] [stn2] [time]

This command will output whether it's possible to go from station [stn1] to station [stn2] within given time [time] in hours

    ./amtrak -mst [out.png]

This command will let you save the MST of all of the amtrak stations at the given png file location

    ./amtrak -trains [stn1 src] [stn1 dest] [stn2 src] [stn2 dest] [stn3 src] [stn3 dest] ... [out.png]

This command will print paths between all those stations where each path would take previous trains in consideration

# About the Code (time complexity)
For the following commands run, the time complexity will be listed.  As a reference, the number of stations will hereby be referred to as V and the number of connections between stations (edges) will be referred to as E.

    ./amtrak [stn1] [stn2]

This command is running the A* algorithm which has a worst case time complexity of O(V+E).  Or, A* can be O(1.2^(length of the distance between the two stations nodes in the graph)).  This is based on the branching factor of our graph which in our calculation turned out to be approximately 1.2
    
    
    ./amtrak [stn1] [stn2] [out.png]

This command is running the A* algorithm which has a worst case time complexity of O(V+E).  Or, A* can be O(1.2^(length of the distance between the two stations nodes in the graph)).  This is based on the branching factor of our graph which in our calculation turned out to be approximately 1.2.  It also has additional time used to save the PNG to the computer.


    ./amtrak [-n] [stn1] [stn2] [number]

This command is running a BFS using the BFS algorithm which has a time complexity of O(branching factor^(number)).  In our case we found the branching factor be approximately 1.2 so the time complexity is O(1.2^number)
    
    
    ./amtrak [-t] [stn1] [stn2] [time]

This command is running a BFS using the BFS algorithm which has a time complexity of O(branching factor^(number)).  In our case we found the branching factor be approximately 1.2 so the time complexity is O(1.2^number)


    ./amtrak -mst [out.png]

This command is running Kruskal's algorithm which has a time complexity of O(E+V).  To do this, we start by sorting all of the edges using radix sort which has O(E) time complexity.  After that, we created a DSet which took time complexity of O(V).  Then, there was a constant time (technically log*(V)) for finding the cycles.  But, for our code it is constant so the total time complexity of Kruskal's algorithm in our implementation was O(E+V).


    ./amtrak -trains [stn1 src] [stn1 dest] [stn2 src] [stn2 dest] [stn3 src] [stn3 dest] ... [out.png]

This command runs the A* algorithm repeatedly for the number of stations entered.  There is a constant time overhead for updating the weight, but otherwise it has the same complexity of the A* algorithm O(V+E) Or, A* can be O(1.2^(length of the distance between the two stations nodes in the graph)).  This is based on the branching factor of our graph which in our calculation turned out to be approximately 1.2.  This is just run multiple times.


