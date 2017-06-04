/*
 * FileName: MovieGraph.h
 *
 * Authors: Rizwan Khan, Yiming Cai
 * Date: 6/5/17
 *
 * This class is used to generate the graphs of all the movies
 */
#include "MovieGraph.h"

// This creates the edges between the movies
void MovieGraph::makeEdges() 
{
    // We loop through all the actors and if they are not the same
    // we make an edge
    for (int i = 0; i < listOfActors.size(); i++)
    {
        for (int j = 0; j < listOfActors.size(); j++)
        {
            if (i != j)
            {
                listOfActors[i]->addEdge(listOfActors[j], name);
            }
        }
    }
}


// The constructor
MovieGraph::MovieGraph(string movieNames, int year)
{
  // Getting the name and list of actors of the movies
  name = new MovieName(movieNames, year);
  listOfActors = vector<ActorNode *>();
}

// The destructor
MovieGraph::~MovieGraph()
{
  // Don't think we need anything in the destructor
  
}

/**
 * Used to add the actor pointers to the list(vector)
 */
void MovieGraph::addActors(ActorNode * actor)
{
  listOfActors.push_back(actor);
}

/**
 * Get the name of the movie
 */
string MovieGraph::getMovieName() const
{
  // Make a temporary string to return the data
  string tempString;

  // Get the name
  name->getName(tempString);
  return tempString;
}

/**
 * Get the year of the movie
 */
int MovieGraph::getMovieYear() const
{
  // Temporary integer to get the year of the movie
  int tempInt;

  // Get the year
  name->getYear(tempInt);
  return tempInt;
}

// Get the MovieName instance 
MovieName * MovieGraph::getMoviePointer() const
{
  // This should return the MovieName instance we made called name
  return name;
}

// Delete the MovieName Instance
void MovieGraph::deleteMovieName()
{
	delete name; 
}

