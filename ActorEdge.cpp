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
    movie = nullptr;
    nextNode = node;
}

// Destructor: do not deallocate anything here
ActorEdge::~ActorEdge()
{

}

// check if the next node is the same as the node passed in
bool ActorEdge::isSameNode( ActorNode * node ) const
{
    return nextNode == node;
}

// get the actor node of the next node
ActorNode * ActorEdge::getNextNode() const
{
    return nextNode;
}

MovieName * ActorEdge::getMovieName() const 
{
    return movie;
}

// Add a MovieName to the vector, and if the MovieName is not null,
// compare the MovieName instances and keep only the one with smaller 
// weight (essentially the one with more recent year)
// Return true if it is replaced by the new_movie
bool ActorEdge::addMovie( MovieName * new_movie )
{
    if (movie == nullptr)
    {
        movie = new_movie;
        return true;
    }

    if (movie->getWeight() > new_movie->getWeight())
    {

        movie = new_movie;
        return true;
    }

    else 
    {
        return false;
    }
}

// get the weight of the edge
int ActorEdge::getWeight() const
{
    return movie->getWeight();
}

