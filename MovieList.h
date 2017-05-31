/*
 * MovieList.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to store a list of MovieGraphs and
 * add ActorNode pointers to the appropriate graphs
 */

#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <iostream>
#include <string>
#include <set>
   
#include "ActorNode.h"
#include "MovieGraph.h"
#include "MovieName.h"

using namespace std;

class UnionFinder;
   
class MovieList{

    friend class UnionFinder;
   
public:
    
    // Constructor
    MovieList();    // by default disjoint is false;
   
    // Destructor: Destruct all the MovieGraphs
    ~MovieList();
   
    // Add an actorNode to one of the graphs
    void addActorNode( ActorNode * node, std::string movieName, int movieYear );
   
    // Find the moviegraph that contains this movie. Return null if does not exist   
    // We will need to create an empty MovieGraph instance, and search using set's
    // find function.
    MovieGraph * searchGraph( std::string movieName, int movieYear ) const;
   
    // Make all the MovieGraphs to start making edges 
    void makeAllEdges ();
   
    // Return a list of all the movie name pointers so we can deallocate them later
    std::vector<MovieName *> getAllMovieNames() const;
   
private:   
   
    // Pass this class into the listOfGraphs template parameters for comparison
    class compareGraphs {
    public:	
        bool operator () ( MovieGraph * const lhs, MovieGraph * const rhs ) const
   	    {
            if ( lhs->getMovieYear() != rhs->getMovieYear() )
            {
                return lhs->getMovieYear() < rhs->getMovieYear();
            }

            std::string sl = lhs->getMovieName();
            std::string sr = rhs->getMovieName();

            return (sl.compare(sr)) < 0;
        }
    };
   
    // store the list of moviegraphs
    std::set<MovieGraph *, compareGraphs> listOfGraphs;
};

   
#endif //MOVIELIST_H
