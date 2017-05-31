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

std::vector< std::pair<ActorNode *, int> > ActorNode::getNodesAndYears() const
{
   
    std::vector< std::pair<ActorNode *, int> > list;
    
    // If we are dealing with weighted edges
    for (auto it = edges.begin();
            it != edges.end(); ++it)
    {
        ActorNode * tempNode = (*it)->getNextNode();
        int year = (*it)->getMovieName()->getYear();
        list.push_back( std::make_pair(tempNode, year) );
    }

    return list;
}

ActorEdge * ActorNode::getFirstEdge() const 
{
    if (edges.size() == 0) return nullptr;
    return edges[0];
}

bool ActorNode::unionFind( ActorNode * ufind ) const
{
    const ActorNode * this_set = this;
    const ActorNode * u_set = ufind;
     
    // find the sentinel node of each set
    while (this_set->prev != nullptr)
    {
        this_set = this_set->prev;
    }
    
    while (u_set->prev != nullptr)
    {
        u_set = u_set->prev;
    }
    
    // already in the same set, so quit
    return this_set == u_set;
}

void ActorNode::unionWith( ActorNode * ufind, MovieName * p_name) 
{
    ActorNode * this_set = this;
    ActorNode * u_set = ufind;
     
    // find the sentinel node of each set
    while (this_set->prev != nullptr)
    {
        this_set = this_set->prev;
    }
    
    while (u_set->prev != nullptr)
    {
        u_set = u_set->prev;
    }
    
    // already in the same set, so quit
    if (this_set == u_set )
    {
        return;    
    }

    // Find the height of each set
    int this_height = 0;
    int u_height = 0;
    ActorNode * curr = this_set;

    // traverse down the this_set to find its height
    while (curr->getFirstEdge() != nullptr)
    {
        curr = curr->getFirstEdge()->getNextNode();
        this_height++;
    }

    // traverse down the u_set to find its height
    curr = u_set;
    while (curr->getFirstEdge() != nullptr)
    {
        curr = curr->getFirstEdge()->getNextNode();
        u_height++;
    }

    // union the sets by having the sentinel node of the
    // smaller height point to the other sentinel node
    if (this_height < u_height)
    {
        this_set->prev = u_set;
        u_set->addEdge(this_set, p_name);
    }
    else
    {
        u_set->prev = this_set;
        this_set->addEdge(u_set, p_name);
    }
}
