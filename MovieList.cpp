/*
 * MovieList.cpp
 * Author: Rizwan Khan, Yiming Cai
 * Date:   6/5/17
 *
 * This class is meant to be used to store a list of MovieGraphs and
 * add ActorNode pointers to the appropriate graphs
 */

#include "MovieList.h"
   
// Constructor
MovieList::MovieList()
{
  // Setting the list of graphs we will use
  listOfGraphs = set<MovieGraph* , compareGraphs>();
}

// Destructor: Destruct all the MovieGraphs
MovieList::~MovieList()
{
  // Destruct all the Movie Graphs
  std::set<MovieGraph*, compareGraphs>::iterator it3;

  // Delete all the iterators that we set
  for (it3 = listOfGraphs.begin(); it3 != listOfGraphs.end(); ++it3)
  {
    delete *it3;
  }
}

// Add an actorNode to one of the graphs
void MovieList::addActorNode( ActorNode * node, std::string movieName, int movieYear )
{
  // Initialize a temporary graph
  MovieGraph * tempGraph = new MovieGraph(movieName, movieYear);
  // Initialize a pair to put data in
  auto pair = listOfGraphs.insert( tempGraph );
  
  // delete if not inserted
  if (!pair.second)
  {
    tempGraph->deleteMovieName();
    delete tempGraph;
  }
  
  // Otherwise we add the actors in
  (*(pair.first))->addActors(node);
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
  temp.deleteMovieName();

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
  // We are making all the edges
  cout << "Making the edges!" << endl;
  MovieGraph* edgeMake;
  // Iterator for going through the set
  std::set<MovieGraph*, compareGraphs>::iterator it3;

  // Create all the edges between the graphs that we have
  for (it3 = listOfGraphs.begin(); it3 != listOfGraphs.end(); ++it3)
  {
    edgeMake = *it3;
    edgeMake->makeEdges();
  }
}

// Return a list of all the movie name pointers so we can deallocate them later
std::vector<MovieName *> MovieList::getAllMovieNames() const
{
  // The vector to store the names in
  std::vector<MovieName *> tempVec;
  // MovieGraph instance
  MovieGraph* nameList;
  // An iterator for going through the movie Graphs
  std::set<MovieGraph*, compareGraphs>::iterator it4;

  // Go through the movie graphs and push them into the vector
  for (it4 = listOfGraphs.begin(); it4 != listOfGraphs.end(); ++it4)
  {
    nameList = *it4;
    tempVec.push_back(nameList->getMoviePointer());
  }
  // Return the vector
  return tempVec;
  
}


