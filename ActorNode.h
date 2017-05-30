/*
 * ActorNode.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to generate a node instance in the graph. 
 * Contains some useful methods and variables for graph traversal.
 */

#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <limits.h>
   
#include "ActorEdge.h"
#include "MovieName.h"
   

class ActorNode{
   
public:
   
   	// Constructor, initialize Actor's name and other variables
    ActorNode( std::string actorName );
   
    // Destructor, probably need to deallocate edges if its allocated on the heap
    ~ActorNode();
   
    // Add an edge to the node. Make the edge in this function
	void addEdge( ActorNode * node, MovieName * name );

   	// Find an edge that connects to a neighbour with this name. If no neighbour with this name exist, return nullptr.
    ActorEdge * findEdge( std::string name ) const;

    ActorEdge * findEdge( const ActorNode * node ) const;
   
    // Check if this actor has the same name as the input
    bool isSameActor( std::string name ) const;
   
    // Return the actor name
   	std::string getActorName( ) const;
    
    // Return the list of neighbour nodes and the weights
    std::vector< std::pair<ActorNode *, int> > getAdjacentNodes(bool weighted = false) const;
  
    // Return the list of neighbor nodes and the years
    std::vector< std::pair<ActorNode *, int> > getNodesAndYears() const;

   	// Return the number of edges this node is connected to
   	int getNumEdges() const;
   
    // Some member variables that can be used in a Dijkstra's algorithm
    int dist;
    ActorNode * prev;
    bool done;
   
private:   
    class compareEdges {
        public:
            bool operator() ( ActorEdge * edge1, ActorEdge * edge2 ) const
            {
                return (edge1->getNextNode()->getActorName())
                    .compare(edge2->getNextNode()->getActorName()) < 0;
            } 
    };

   	// Member variables. Define the name of this actor and which adjacent actors this actor is connected to.
    std::string name;
                                                                       
                                                                       
    //std::set< ActorEdge *, compareEdges > edges;
   	std::vector< ActorEdge * > edges;
    
};
   

#endif //ACTORNODE_H
