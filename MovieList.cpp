/*
 * MovieList.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This class is meant to be used to store a list of MovieGraphs and
 * add ActorNode pointers to the appropriate graphs
 */

#include "MovieList.h"
   
// Constructor
MovieList::MovieList()
{

}

// Destructor: Destruct all the MovieGraphs
MovieList::~MovieList()
{

}

// Add an actorNode to one of the graphs
void MovieList::addActorNode( ActorNode * node, std::string movieName, int movieYear )
{

}

// Find the moviegraph that contains this movie. Return null if does not exist   
// We will need to create an empty MovieGraph instance, and search using set's
// find function.
MovieGraph * MovieList::searchGraph( std::string movieName, int movieYear ) const
{

}

// Make all the MovieGraphs to start making edges
void MovieList::makeAllEdges ()
{

}

// Return a list of all the movie name pointers so we can deallocate them later
std::vector<MovieName *> MovieList::getAllMovieNames() const
{

}


