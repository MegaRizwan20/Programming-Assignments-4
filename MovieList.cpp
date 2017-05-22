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
  // Unsure if we need to do anything in the constructor
  listOfGraphs = set<MovieGraph* , compareGraphs>();

}

// Destructor: Destruct all the MovieGraphs
MovieList::~MovieList()
{
  // Unsure if we need to do anything in the destructor
  // We actually need to remove all the movie graphs here
  std::set<MovieGraph*, compareGraphs>::iterator it3;

  for (it3 = listOfGraphs.begin(); it3 != listOfGraphs.end(); ++it3)
  {
    delete *it3;
  }

}

// Add an actorNode to one of the graphs
void MovieList::addActorNode( ActorNode * node, std::string movieName, int movieYear )
{
  // Make a new Movie Graph instance to do comparisons
  MovieGraph temp(movieName, movieYear);
  MovieGraph * tempGraph = &temp;
  
  // Make an iterator
  std::set<MovieGraph*, compareGraphs>::iterator it;
  // Return an iterator if we found the graph
  it = listOfGraphs.find(tempGraph);
  // If it didn't we make a new instance of the movie Graph
  if (it == listOfGraphs.end())
  {
    cout << "Made a new MovieGraph (and Name) !!" << endl;
    tempGraph = new MovieGraph(movieName, movieYear);
    listOfGraphs.insert( tempGraph );
  }
  // Else we dereference it and store it into your temp graph
  else
  {
    tempGraph = *it;
  }
  // Add the actor to the temp graph
  tempGraph->addActors(node);
}

// Find the moviegraph that contains this movie. Return null if does not exist   
// We will need to create an empty MovieGraph instance, and search using set's
// find function.
MovieGraph * MovieList::searchGraph( std::string movieName, int movieYear ) const
{
  // Make an empty MovieGraph Instance
  MovieGraph temp(movieName, movieYear);
  MovieGraph * tempSearch = &temp;
  
  // Make an iterator to look for graph
  std::set<MovieGraph*, compareGraphs>::iterator it2;

  // Look for the graph
  it2 = listOfGraphs.find(tempSearch);

  // If we couldn't find it, then return NULL
  if (it2 == listOfGraphs.end())
  {
    return NULL;
  }
  // Else we return the movieGraph that contains the movie
  else
  {
    return *it2;
  }
  //return tempSearch;
}

// Make all the MovieGraphs to start making edges
// Delegate to makeEdges() function in MovieGraph
// Do this for each element in the set
void MovieList::makeAllEdges ()
{
  MovieGraph* edgeMake;
  // Iterator for going through the set
  std::set<MovieGraph*, compareGraphs>::iterator it3;

  for (it3 = listOfGraphs.begin(); it3 != listOfGraphs.end(); ++it3)
  {
    edgeMake = *it3;
    edgeMake->makeEdges();
  }
  /*it3 = listOfGraphs.find(edgeMake);

  if (it3 != listOfGraphs.end())
  {
    edgeMake->makeEdges();
  }*/
}

// Return a list of all the movie name pointers so we can deallocate them later
std::vector<MovieName *> MovieList::getAllMovieNames() const
{
  std::vector<MovieName *> tempVec;
  MovieGraph* nameList;
  std::set<MovieGraph*, compareGraphs>::iterator it4;

  for (it4 = listOfGraphs.begin(); it4 != listOfGraphs.end(); ++it4)
  {
    nameList = *it4;
    tempVec.push_back(nameList->getMoviePointer());
  }
  return tempVec;
  
}


