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

    ActorPath * path = graph.findPath( "BACON, LEVIN (I)", "HOUNSOU, DJIMON" );
    std::vector<ActorEdge *> edges = path->getEdges();
    std::cout << path->getStartNode()->getActorName() << std::endl;
    for (int i = 0; i < edges.size(); i++)
    {
        std::string movie;
        edges[i]->getMovieName()->getName(movie);
        std::cout << "--" << movie << "-->" << edges[i]->getNextNode()->getActorName() << std::endl;
    }
    delete path;
    
    return 0;

}
