  For our project, we decided to use the open flights database to create a directed graph,run a DFS Traversal, and run dijkstra's and the landmark path algorithm.
  
  For DFS traversal, I created a constructor and use the graph as argument in traversal. Also create a vector of bool to track which vertex in the graph is already visited. I labelled all vertex in the graph as non-visited, and then call traversal helper function for all vertex in the graph, not only for vertex are connected. In the DFS_helper function, I labelled the current vertex v as visited, and print the current visited vertex in the terminal. Then I get all adjacent vertices to current vertex v and traverse these vertex recurseively. 
  
  For Dijkstra's algorithm, the first thing I did was lay out the .h and .cpp file for the ShortestPath class. Then I used my knowledge fo the algorithm to take a graph from the graph class and two vertices in order to preform Dijkstra's algorithm. One discovery I made while coding the algorithm was that I needed helper method to find the index of a specific Vertex in the set I made at the beginning, so I coded it and used it. Anouther discovery made was that the algorithm starts with the distance of every vertex being labeled as infinity. I didn't really know how to code this so I set the starting distances to 1000000 instead. The attempted results of my code is that it prints out the starting vertex and then each vertex it visits until it hits the target end vertex. The results can be seen by running the finalproj executable and looking where it is labeled. I also wrote a few test cases to help me ensure my development of Dijkstra's algorithm was working as intended.

  For landmark algorithm, I decided to combine two Dijkstra algorithm, the first start from start point to landmark checkpoint, the second goes from landmark checkpoint to end point. I used the same SSSP function, but I changed the return type to vector of Vertex and combine the two vectors and write the result to text file by creating a new iostream and iterate through the result vector, and after the program is done, a message will display on where the result has been save on disk. The main bug I faced was that vector gave a segfault and I then resize the vector before use it. 
  
 For loading data set, I reviewed the graph.cpp/ .h and the edge.h file in previous lab to help me construct the graph structure in this project. Then I build the constructor to load the data from data set. First, I use getline() method to get each line in the data set and set it as a istringstream. Then use getline() method again with the line separate by "," not " ". After loading the data, I was tried to save all the information in to the graph but I didn't figure out how to use the unordered_map<Vertex, unordered_map<Vertex, Edge>> to save more data. Therefore, I just use the Airport ID as the Vertex to save the graph without any addition data. This is all the problem I meet in my coding. 