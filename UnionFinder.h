/*
 * UnionFinder.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef UNIONFINDER_H
#define UNIONFINDER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <set>

#include "ActorNode.h"
#include "ActorEdge.h"
#include "MovieList.h"
#include "MovieName.h"
#include "MovieGraph.h"

class compareNodes {
public:
    bool operator() ( ActorNode * lhs, ActorNode * rhs ) const
    {
        return (lhs->getActorName()).compare(rhs->getActorName()) < 0;
    }
};

class UnionFinder {
protected:
  

    // This defines a set of pairs, each containing a node (the starting node) and the set of
    // found paths.
    std::set< ActorNode *, compareNodes> allNodes;

    // Stores the list of pointers of all MovieName instances constructed. This is to ensure that
    // the MovieName instances get deleted once and once only
    std::vector< MovieName *> allMovies;

    // stores the set of moviegraphs that each act as a disjoint set before they are connected
    MovieList movieList;
   
public:
    UnionFinder(void);
    ~UnionFinder();

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename);

    // print the number of nodes, edges and movies in the graph
    void printStats( ostream& out ) const;

    // print all the actor names and the earliest year in which they are connected to the output stream
    void printAllYears( std::vector< std::pair< std::string, std::string> >, ostream& out );
};


#endif // UNIONFINDER_H
