/*
 * FileName: MovieGraph.h
 *
 * Authors:
 * Date:
 * CSE Login:
 * Email:
 * PID:
 */
#include "MovieGraph.h"

void MovieGraph::makeEdges() 
{
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
  // Should set the name of the movie name equal to the movieNames
  //name->movieName = movieNames;
  //name->getName(movieNames);
  // Should set the years for the movie name
  //name->year= year;
  //name->getYear(year);

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
  //return name->movieName;
  //name->getName(movieNames);
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
  //return name->year;
  //name->getYear(year);
  // Make a temporary storage 
  int tempInt;

  // Get the year
  name->getYear(tempInt);
  return tempInt;
}

// Get the MovieName instance 
// (don't get confused with getMovieName(), which returns a string)
MovieName * MovieGraph::getMoviePointer() const
{
  // This should return the MovieName instance we made called name
  return name;
}

