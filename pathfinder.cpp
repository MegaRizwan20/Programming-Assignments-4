// FILE HEADER HERE

#include <fstream>
#include <iostream>

#include "ActorGraph.h"
#include "ActorNode.h"
#include "ActorEdge.h"
#include "ActorPath.h"
#include "MovieName.h"

// for temporary testing
int main()
{
    // Make sure to add all the user input error parsings here

    // initiate graph
    ActorGraph graph;
    const static bool weight = false;
    std::cout << "Loading from file, this might take a while..." << flush;
    graph.loadFromFile( "movie_casts.tsv", weight );
    std::cout << "done!" << std::endl;
    graph.printStats(std::cout);

    ActorPath * path = graph.findPath( "BACON, KEVIN (I)", "GIAMATTI, PAUL" );
	if (path == nullptr)
    {
      cout << "PATH NOT FOUND!!" << endl;
    }
  	else
    {
      path->printPath(std::cout);
    }
  
    delete path;
    
    return 0;

}
