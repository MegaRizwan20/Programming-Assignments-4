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
  
  /* --------------- This is slow -----------------------------
    ActorEdge temp( node, nullptr );
    ActorEdge * temp2;

    // Search to see if the edge already exist between the nodes
    std::set<ActorEdge *, compareEdges>::iterator it = edges.find( &temp );

    // If the edge does not exist
    if (it == edges.end())
    {
        ActorEdge * temp2 = new ActorEdge(node, name);
        edges.insert( temp2 );
    }
    else
    {
        temp2 = *it;
      	// Add the moviename to the edge
    	temp2->addMovie( name );
    }
    / ----------------------------------------------------------- */
  
  	ActorEdge * temp = new ActorEdge(node, name);
  
  /* ------------ old slow shits -----------------
    auto pair = edges.insert(temp);
  	
  	// If not inserted succesfully
  	if (! pair.second )
    {
      delete temp;
      (*(pair.first))->addMovie( name );
    }
    ---------------------------------------------- */
  
  	edges.push_back( temp );
}

// Find an edge that connects to a neighbour with this name. If no neighbour with this name exist, return nullptr.
/* ---------------------------------------------------------
ActorEdge * ActorNode::findEdge( std::string name ) const
{
    ActorNode node(name);
    ActorEdge temp(&node, nullptr);
    std::set<ActorEdge *, compareEdges>::iterator it = edges.find( &temp );

    // If the edge does not exist
    if (it == edges.end())
    {
        return nullptr;
    }

    // Else if the edge does exist
    else
    {
        return *it;
    }
}
----------------------------------------------------------- */

ActorEdge * ActorNode::findEdge( const ActorNode * node ) const
{
    //return findEdge( node->getActorName() );
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

