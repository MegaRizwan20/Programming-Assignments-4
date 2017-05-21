/*
 * ActorEdge.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to generate an edge instance in the graph. 
 * Contains some useful methods and variables for graph traversal.
 */

#include "ActorEdge.h"

// Constructor: make an edge that points to the input node
ActorEdge::ActorEdge(ActorNode * node)
{

}

// Destructor: do not deallocate anything here
ActorEdge::~ActorEdge()
{

}

// get the actor name of the next node
std::string ActorEdge::getNextActorName() const
{

}

// check if the next node is the same as the node passed in
bool ActorEdge::isSameNode( ActorNode * node ) const
{

}

// get the actor node of the next node
ActorNode * ActorEdge::getNextNode() const
{

}

// Add a MovieName to the vector, and if the MovieName is not null,
// compare the MovieName instances and keep only the one with smaller 
// weight (essentially the one with more recent year)
bool ActorEdge::addMovie( MovieName * movie )
{

}

// get the weight of the edge
int ActorEdge::getWeight() const
{

}

