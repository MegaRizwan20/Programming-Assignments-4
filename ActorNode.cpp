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
    name = actorName;
    edges = std::vector<ActorEdge *>();
}

// Destructor, probably need to deallocate edges if its allocated on the heap
ActorNode::~ActorNode()
{
    for (auto it = edges.begin();
        it != edges.end(); ++it)
    {
        delete *it;
    }
}

int ActorNode::getNumEdges() const
{
	return edges.size();
}

// Add an edge to the node. Make the edge in this function
// If the edge already exist, just add the moviename to it
void ActorNode::addEdge( ActorNode * node, MovieName * name )
{
  	edges.push_back( new ActorEdge(node, name) );
}

// This is a sequential search. Since its a pointer comparison,
// this shouldn't take too long.
ActorEdge * ActorNode::findEdge( const ActorNode * node ) const
{
  	for (int i = 0; i < edges.size(); i++)
    {
      if (edges[i]->getNextNode() == node)
        return edges[i];
    }
  
  	return nullptr;
}

// Check if this actor has the same name as the input
bool ActorNode::isSameActor( std::string p_name ) const
{
    return (p_name.compare(name)) == 0;
}

// Return the actor name
std::string ActorNode::getActorName( ) const
{
    return name;
}

// Return the list of neighbour nodes and the weights of these edges
std::vector< std::pair<ActorNode *, int> > ActorNode::getAdjacentNodes(bool weighted /*= false*/) const
{
   
    std::vector< std::pair<ActorNode *, int> > list;
    
    // If we are dealing with weighted edges
    if (weighted)
    {
        for (auto it = edges.begin();
                it != edges.end(); ++it)
        {
            ActorNode * tempNode = (*it)->getNextNode();
            int weight = (*it)->getWeight();
            list.push_back( std::make_pair(tempNode, weight) );
        }
    }
    else
    {
        for (auto it = edges.begin();
                it != edges.end(); ++it)
        {
            ActorNode * tempNode = (*it)->getNextNode();
            list.push_back( std::make_pair(tempNode, 1) );
        }

    }

    return list;
}

