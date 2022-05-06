# Description
This file will detail the output of each of the functions that can be run as well as describe the tests created to ensure that each of these functions is working correctly.  Finally, this file will talk about our leading question and how we answered it.

# Each function the User can Run


    ./amtrak [stn1] [stn2]

This command will use the A* algorithm to find the optimized path between [stn1] and [stn2] so that the user can know which way the train will go.  As an example of this function working, when you run the command with the stations Champaign (CHM) to Chicago (CHI), the output is as follows:
    <img width="906" alt="Screen Shot 2022-05-02 at 8 44 46 PM" src="https://media.github-dev.cs.illinois.edu/user/14304/files/ca79b95f-28f6-4fcb-adff-7ec9f6781399">

    ./amtrak [stn1] [stn2] [out.png]

This command will also use the A* algorithm to find the optimized path between [stn1] and [stn2] so that the user can know which way the train will go.  Additionally, this function saves the path to the output file [out.png].  If you run this command with the stations Chicago (CHI) to Miami (MIA), the image out.png is as follows:
<img width="1639" alt="Screen Shot 2022-05-02 at 8 49 45 PM" src="https://media.github-dev.cs.illinois.edu/user/14304/files/059fe5fe-a0fa-4f2d-9afe-5b31fff0ae5f">


    ./amtrak [-n] [stn1] [stn2] [number]

This command will tell the user whether it is possible to go from station [stn1] to [stn2] within [number] of stops using the BFS algorithm.  As an example of this function being run, when you run the command with Champaign (CHM), Chicago (CHI), and 5, the output is the first part of the photo (possible) but if you run it with Champaign (CHM), Chicago (CHI), and 4, the output is the second part of the photo (not possible)
    <img width="986" alt="Screen Shot 2022-05-02 at 8 52 31 PM" src="https://media.github-dev.cs.illinois.edu/user/14304/files/896fd045-d7c2-4922-af95-da99f1ca62b8">

    ./amtrak [-t] [stn1] [stn2] [time]

This command will output whether it's possible to go from station [stn1] to  [stn2] within a given [time] in hours using the BFS algorithm and conversion from the time given.  As an example of this function being run, when you run the command with Champaign (CHM), Chicago (CHI), and 3 hours, the output is the first part of the photo (possible), but if you run it with Champaign (CHM), Chicago (CHI), and 1 hour, the output is the second part of the photo (not possible)
<img width="986" alt="Screen Shot 2022-05-02 at 8 55 27 PM" src="https://media.github-dev.cs.illinois.edu/user/14304/files/4492bc63-4008-439a-bf42-f63fa13c67f3">


    ./amtrak -mst [out.png]

This command uses Kruskal's algorithm to allow the user to save the MST of all of the amtrak stations at [out.png].  To demonstrate this function working, when it is run, the following is the output file:
<img width="1468" alt="Screen Shot 2022-05-02 at 9 01 16 PM" src="https://media.github-dev.cs.illinois.edu/user/14304/files/a357e033-efcb-40d0-bc81-83ac3e0301b9">


    ./amtrak -trains [stn1 src] [stn1 dest] [stn2 src] [stn2 dest] [stn3 src] [stn3 dest] ... [out.png]

This command will print all of the paths between all of the stations where each train would take taking previous trains in consideration (demonstrating crowding of tracks).  To show this working, when the command is run (with a lot of trains going between the stations DRT and SMC - exact number shown in terminal), the output is as follows.  The top part is a very zoomed in version of the image with the trains going on different paths and the bottom part is the output of the terminal describing which path which trains are going on.
<img width="1529" alt="Screen Shot 2022-05-02 at 9 26 42 PM" src="https://media.github-dev.cs.illinois.edu/user/14304/files/898e43d0-978e-4454-9716-d0ef5e3a4c5f">



# Test Cases
We have three main algorithms that we focused on in the test cases since those were the three most complex parts (and the majority of the project other than user interface stuff), so for each of them we created test cases to make sure they were working as expected.  The algorithms are MST (Kruskal's algorithm), BFS, and A* algorithm.

For MST we created a mock data set (much smaller) and ran our MST algorithm (Kruskal's algoritm) and then checked that the MST was completely correct, even including checking the order in which the edges were added to the MST to make sure that Kruskal's algorithm was running appropraitely.

For BFS we checked whether the function we implemented (reachability between two stations) returned true or false for various cases.  We manually addded these cases to make sure that the function should either result in true or false and then had the test cases double check that they were all working to make sure that our BFS algorithm was working appropriately.

For A* we ran our algorithm on various different destinations across the Amtak map and manually made sure that the outputted result was the most efficient route.  This worked for all of the cases we could think about providing and therefore it waas able to make sure it was working apporopriately. 


# Leading Question

Our leading question in the proposal talked about how we wanted find the optimal path forr a self driving train using A* algorithm for time wise and number of stops wise.  Also, we wanted to create a minimum spanning tree of all of the Amtrak stations in the US.  We answered this goal set by implementing all of the features that we set out to do and also allowing the user to interact with the software in a useful way.  So, we did accomplish our goals about meeting the criteria we set out in the leading question section and it was a successful project overall.
