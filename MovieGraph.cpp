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
    if (!disjoint)
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
    else
    {
        // find a node to be the sentinel node
        int sentinel = -1;
        for (int i = 0; i < listOfActors.size(); i++)
        {
            if (listOfActors[i]->getNumEdges() == 0)
            {
                sentinel = i;
                break;
            }
        }

        // if there is at  least 1 node with no edges yet
        if (sentinel != -1)
        {
            for (int i = 0; i < listOfActors.size(); i++)
            {
                if (listOfActors[i]->getNumEdges() == 0)
                {
                    listOfActors[i]->addEdge(listOfActors[sentinel], name);
                }
                else
                {
                    if (listOfActors[sentinel]->getNumEdges() == 0)
                    {
                        listOfActors[sentinel]->unionWith(listOfActors[i], name);
                    }
                }
            }
        }
    }
}


// The constructor
MovieGraph::MovieGraph(string movieNames, int year, bool p_disjoint)
{
  // Should set the name of the movie name equal to the movieNames
  //name->movieName = movieNames;
  //name->getName(movieNames);
  // Should set the years for the movie name
  //name->year= year;
  //name->getYear(year);

  name = new MovieName(movieNames, year);
  listOfActors = vector<ActorNode *>();
  disjoint = p_disjoint;
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

void MovieGraph::deleteMovieName()
{
	delete name; 
}

