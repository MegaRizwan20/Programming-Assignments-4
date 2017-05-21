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
ActorPath::ActorPath(ActorNode * start)
{

}

// Destructor: deallocate nothing
ActorPath::~ActorPath()
{

}

// add an edge to the list to extend the path
void ActorPath::addEdge( ActorEdge * edge )
{

}

// print the path to the user
void ActorPath::printPath( ostream& out ) const
{

}

// check if the path starts and ends at these input nodes
bool ActorPath::checkStartAndEnd( ActorNode * start, ActorNode * end) const
{

}

// return the start node
ActorNode * ActorPath::getStartNode() const
{

}

// return the end node
ActorNode * ActorPath::getEndNode() const
{

}

// return the total weight of the path
// By finding the sum of weight of all the edges
int ActorPath::getTotalWeight() const
{

}

// Return the total length of the path (unweighed)
// Simply by finding the length of the list
int ActorPath::getTotalLength() const
{

}


