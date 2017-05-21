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
   
class MovieList{
   
public:
    
    // Constructor
    MovieList();
   
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
        bool operator () ( const MovieGraph *& lhs, const MovieGraph *& rhs ) const
   	{
	    std::string sl = lhs->getMovieName();
   	    sl += std::to_string(lhs->getMovieYear());
   
	    std::string sr = rhs->getMovieName();
   	    sr += std::to_string(rhs->getMovieYear());
   
   	    return (sl.compare(sr)) < 0;
        }
    };
   
    // store the list of moviegraphs
    std::set<MovieGraph *, compareGraphs> listOfGraphs;
   
};

   
#endif //MOVIELIST_H
