 /*
 * ActorNode.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to generate a node instance in the graph. 
 * Contains some useful methods and variables for graph traversal.
 */ 

#include "ActorNode.h"

// Constructor, initialize Actor's name and other variables
ActorNode::ActorNode( std::string actorName )
{

}

// Destructor, probably need to deallocate edges if its allocated on the heap
ActorNode::~ActorNode()
{

}

// Add an edge to the node. Make the edge in this function
void ActorNode::addEdge( ActorNode * node, MovieName * name )
{

}

// Find an edge that connects to a neighbour with this name. If no neighbour with this name exist, return nullptr.
ActorEdge * ActorNode::findEdge( std::string name ) const
{

}

// Check if this actor has the same name as the input
bool ActorNode::isSameActor( std::string name ) const
{

}

// Return the actor name
std::string ActorNode::getActorName( ) const
{

}

// Return the actor edges by value (not reference, so no change can be done)
std::vector< ActorEdge * > ActorNode::getEdges() const
{

}

// Return the list of neighbour nodes
std::vector< ActorNode * > ActorNode::getAdjacentNodes() const
{

}

