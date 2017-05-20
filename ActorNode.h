/*
 * ActorNode.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <string>
#include <vector>
   
class ActorNode{
   
public:
   
   	// Constructor, initialize Actor's name and other variables
    ActorNode( std::string actorName );
   
    // Destructor, probably need to deallocate edges if its allocated on the heap
    ~ActorNode();
   
    // Add an edge to the node
	void addEdge( ActorEdge * edge );

   	// Find an edge that connects to a neighbour with this name. If no neighbour with this name exist, return nullptr.
    ActorEdge * findEdge( std::string name ) const;
   
    // Check if this actor has the same name as the input
    bool isSameActor( std::string name ) const;
   
    // Return the actor name
   	std::string getActorName( ) const;
   
    // Return the actor edges by value (not reference, so no change can be done)
    std::vector< ActorEdge * > getEdges() const;
   
    // Some member variables that can be used in a Dijkstra's algorithm
    int dist;
    ActorNode * prev;
    bool done;
   
private:   
   
   	// Member variables. Define the name of this actor and which adjacent actors this actor is connected to.
    std::string name;
    std::vector< ActorEdge * > edges;
    
};
   
#endif //ACTORNODE_H