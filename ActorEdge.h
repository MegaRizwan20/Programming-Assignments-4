/*
 * ActorEdge.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to generate an edge instance in the graph. 
 * Contains some useful methods and variables for graph traversal.
 */

#ifndef ACTOREDGE_H
#define ACTOREDGE_H

#include <iostream>
#include <string>
#include <vector>
   
#include "ActorNode.h"
#include "MovieName.h"
   
class ActorNode;
   
class ActorEdge{
   
public:
   
    // Constructor: make an edge that points to the input node
    ActorEdge(ActorNode * node);
   
   	// Destructor: do not deallocate anything here
    ~ActorEdge();
   
    // get the actor name of the next node
    std::string getNextActorName() const;
    
    // check if the next node is the same as the node passed in
	bool isSameNode( ActorNode * node ) const;
   
    // get the actor node of the next node
    ActorNode * getNextNode() const;
   
    // Add a MovieName to the vector, and if the MovieName is not null,
   	// compare the MovieName instances and keep only the one with smaller 
    // weight (essentially the one with more recent year)
    bool addMovie( MovieName * movie );
   
    // get the weight of the edge
    int getWeight() const;
   
private:   
    
    // Store the movie with the least weight
	MovieName *  movie;
   
    // Store the node that this edge is pointing to
    ActorNode * nextNode;
   
};

   
#endif //ACTOREDGE_H