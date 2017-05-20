/*
 * ActorNode.h
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
#include <priority_queue>
   
#include "ActorNode.h"
#include "MovieName.h"
   
   
class MovieNameComparator{

public:
   
	bool greaterMovieWeight( const MovieName * movie1, const MovieName * movie2 ) const;   
   
};   
   
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
   
    // add a MovieName to the queue
    bool addMovie( MovieName * movie );
   
    // get the weight of the edge
    int getWeight() const;
   
private:   
    
    // Store a list of movie names
	std::priority_queue< MovieName * > movieList;
   
    // Store the node that this edge is pointing to
    ActorNode * nextNode;
   
};

   
#endif //ACTOREDGE_H