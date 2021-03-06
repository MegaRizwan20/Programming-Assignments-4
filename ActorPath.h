/*
 * ActorPath.h
 * Author: Rizwan Khan, Yiming Cai
 * Date:   6/5/17
 *
 * This class is meant to be used to generate a user-readable string
 * that displays the path from one node to the other node
 */

#ifndef ACTORPATH_H
#define ACTORPATH_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
   
#include "ActorNode.h"
#include "ActorEdge.h"
#include "MovieName.h"
   
   
class ActorPath{
   
public:
    
    // Constructor: start with a starting node
    ActorPath(ActorNode * start);
   
    // Destructor: deallocate nothing
    ~ActorPath();
   
    // add an edge to the list to extend the path
    void addEdge( ActorEdge * edge );
   
    // print the path to the user
   	void printPath( ostream& out ) const;
   
    // check if the path starts and ends at these input nodes
    bool checkStartAndEnd( ActorNode * start, ActorNode * end) const;
   
    // return the start node
    ActorNode * getStartNode() const;

    // return the edges
    std::vector<ActorEdge *> getEdges() const;
   
    // return the end node
    ActorNode * getEndNode() const;
   
    // return the total weight of the path
    // By finding the sum of weight of all the edges
    int getTotalWeight() const;
   
    // Return the total length of the path (unweighed)
    // Simply by finding the length of the list
    int getTotalLength() const;

private:   
    
    // the starting node
	ActorNode * start;
   
    // the list of edges that will eventually bring us to the end node
    std::vector<ActorEdge *> linkedEdges;
   
};

   
#endif //ACTORPATH_H
