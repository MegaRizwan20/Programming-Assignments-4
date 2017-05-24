/*
 * ActorPath.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to generate a user-readable string
 * that displays the path from one node to the other node
 */

#include "ActorPath.h"

// Constructor: start with a starting node
ActorPath::ActorPath(ActorNode * p_start)
{
    start  = p_start;
}

// Destructor: deallocate nothing
ActorPath::~ActorPath()
{

}

// add an edge to the list to extend the path
void ActorPath::addEdge( ActorEdge * edge )
{
    linkedEdges.push_back(edge);
}

// print the path to the user
void ActorPath::printPath( ostream& out ) const
{
    std::vector<ActorEdge *> edges = getEdges();
    //cout << " money " << endl;
    out << "(" << getStartNode()->getActorName() << ")";
    //cout << "Computing path for (" <<getStartNode()->getActorName() << ") -> ("
    //                << edges[i]->getNextNode()->getActorName() << ")" << endl;
    for (int i = 0; i < edges.size(); i++)
    {
        std::string movie;
      	int year;
        //cout << "Computing path for (" <<getStartNode()->getActorName() << 
        //") -> ("<< edges[i]->getNextNode()->getActorName() << ")" << endl;

        edges[i]->getMovieName()->getName(movie);
        edges[i]->getMovieName()->getYear(year);
        out << "--[" << movie << "#@" << year << "]-->" << "(" << 
                               edges[i]->getNextNode()->getActorName()<< ")";
    }
  	out << std::endl;
}

// check if the path starts and ends at these input nodes
bool ActorPath::checkStartAndEnd( ActorNode * p_start, ActorNode * p_end) const
{
    if (p_start == getStartNode() && p_end == getEndNode())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// return the start node
ActorNode * ActorPath::getStartNode() const
{
    return start;
}

// return the end node
ActorNode * ActorPath::getEndNode() const
{
    return linkedEdges[ linkedEdges.size() -1 ]->getNextNode();
}

std::vector<ActorEdge *> ActorPath::getEdges() const
{
    return linkedEdges;
}

// return the total weight of the path
// By finding the sum of weight of all the edges
int ActorPath::getTotalWeight() const
{
    int sum = 0;
    for (int i = 0; i < linkedEdges.size(); i++)
    {
        sum += linkedEdges[i]->getWeight();
    }
}

// Return the total length of the path (unweighed)
// Simply by finding the length of the list
int ActorPath::getTotalLength() const
{
    return linkedEdges.size();
}


