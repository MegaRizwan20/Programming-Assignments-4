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

}

// The destructor
MovieGraph::~MovieGraph()
{

}

/**
 * Used to add the actor pointers to the list(vector)
 */
void MovieGraph::addActors(ActorNode * actor)
{

}

/**
 * Get the name of the movie
 */
string MovieGraph::getMovieName() const
{

}

/**
 * Get the year of the movie
 */
int MovieGraph::getMovieYear() const
{

}

// Get the MovieName instance 
// (don't get confused with getMovieName(), which returns a string)
MovieName * MovieGraph::getMoviePointer() const
{

}

