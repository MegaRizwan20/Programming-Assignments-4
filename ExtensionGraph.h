/*
 * ExtensionGraph.h
 * Author: Rizwan Khan, Yiming Cai
 * Date:   6/5/17
 *
 * This file is meant to exist as a container for starter code that can use 
 * to read the input file format defined in movie_casts.tsv. Feel free to 
 * modify any/all aspects as you wish.
 */

#ifndef EXTENSIONGRAPH_H
#define EXTENSIONGRAPH_H

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

// Operating overloading for comparing the nodea
class compareNodes {
public:
    bool operator() ( std::pair<ActorNode *, int> lhs, std::pair<ActorNode *, int> rhs ) const
    {
        return ((lhs.first)->getActorName()).compare((rhs.first)->getActorName()) < 0;
    }
};

// Operator overloading for comparing the paths
class comparePaths {
public:
    bool operator() ( ActorPath lhs, ActorPath rhs ) const
    {
        return lhs.getEndNode() < rhs.getEndNode();
    }
};

// Operator overloading for how things go into the queue
class compareInQueue {
public:
    bool operator() ( std::pair<int, ActorNode *> lhs, 
                      std::pair<int, ActorNode *> rhs) const
    {
        return lhs.first > rhs.first;
        // Changing queue priority to get longest path
        //return lhs.first < rhs.first;
    }
};

// Operator overloading for comparing the years
class compareYears {
public:
    bool operator() ( std::pair<ActorNode *, int> lhs, 
                      std::pair<ActorNode *, int> rhs ) const
    {
        return lhs.second > rhs.second;
    }
};

class ExtensionGraph {
protected:

    // This defines a set of pairs, each containing a node (the starting node)
    // and the set of found paths.
    // changed from just taking in an actor node to taking in pair of 
    // actornode and double
    std::set< std::pair<ActorNode *, double>, compareNodes> allNodes;

    // Stores the list of pointers of all MovieName instances constructed. 
    // This is to ensure that the MovieName instances get deleted once 
    // and once only
    std::vector< MovieName *> allMovies;

    // store previously searched paths to make the next search faster 
    // if its the same starting actor
    ActorNode * prevSearch;
    bool prevIsBFS;
   
public:
    ExtensionGraph(void);
    ~ExtensionGraph();

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights 
     * as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename);

    // Find the shortest path from the starting node and ends up at 
    // the ending node
    ActorPath * findPath( std::string start_name, std::string end_name ) ;

    // print the number of nodes, edges and movies in the graph
    void printStats( ostream& out ) const;

    double findIncome( ActorNode * bla) const;

};


#endif // ACTORGRAPH_H
