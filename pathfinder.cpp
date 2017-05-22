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

    ActorPath * path = graph.findPath( "BACON, KEVIN (I)", "ALBAN, CARLO" );
    std::vector<ActorEdge *> edges = path->getEdges();
    std::cout << path->getStartNode()->getActorName();
    for (int i = 0; i < edges.size(); i++)
    {
        std::string movie;
      	int year;
      	if (edges[i]->getMovieName() != nullptr)
        {
        	edges[i]->getMovieName()->getName(movie);
          	edges[i]->getMovieName()->getYear(year);
        }
        std::cout << "--[" << movie << "#@" << year << "]-->" << edges[i]->getNextNode()->getActorName();
    }
  	std::cout << std::endl;
    delete path;
    
    return 0;

}
