/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <stack>

#include "ActorNode.h"
#include "ActorEdge.h"
#include "ActorPath.h"
#include "MovieList.h"
#include "MovieName.h"
#include "MovieGraph.h"

// Maybe include some data structures here

using namespace std;

class compareNodes {
public:
    bool operator() ( ActorNode * lhs, ActorNode * rhs ) const
    {
        return (lhs->getActorName()).compare(rhs->getActorName()) < 0;
    }
};

class comparePaths {
public:
    bool operator() ( ActorPath lhs, ActorPath rhs ) const
    {
        return lhs.getEndNode() < rhs.getEndNode();
    }
};

class compareInQueue {
public:
    bool operator() ( std::pair<int, ActorNode *> lhs, std::pair<int, ActorNode *> rhs) const
    {
        return lhs.first > rhs.first;
    }
};

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
    bool weighted;

    // This defines a set of pairs, each containing a node (the starting node) and the set of
    // found paths.
    std::set< ActorNode *, compareNodes> allNodes;

    // Stores the list of pointers of all MovieName instances constructed. This is to ensure that
    // the MovieName instances get deleted once and once only
    std::vector< MovieName *> allMovies;

    ActorNode * prevSearch;
   
public:
    ActorGraph(void);
    ~ActorGraph();

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    // Find the shortest path from the starting node and ends up at the ending node
    ActorPath * findPath( std::string start_name, std::string end_name ) ;
  
    void printStats( ostream& out ) const;
};


#endif // ACTORGRAPH_H
