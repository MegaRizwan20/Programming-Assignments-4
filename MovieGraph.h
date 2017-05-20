/*
 * FileName: MovieGraph.h
 *
 * Authors:
 * Date:
 * CSE Login:
 * Email:
 * PID:
 */

#ifndef MOVIEGRAPH_H
#define MOVIEGRAPH_H

#include <string>
#include "MovieName.h"
#include "ActorGraph.h"
#include "ActorNode.h"

using namespace std;

class MovieGraph
{
  private:
    
    // The name of the movie. All edges generated by this class will store
    // a pointer that points to MovieName instance
    MovieName names;
    // The list of ActorNode pointers
    vector<ActorNode*> listOfActors;

  public:

   // The constructor
   MovieGraph(string movieNames, int year);
   // The destructor
   ~MovieName();


   /**
    * Used to add the actor pointers to the list(vector)
    */
   void addActors(ActorNode& actor);

   /**
    * Used to create a list of edges among the actor nodes. Should
    * only be called one time and be able to modify the ActorNode class.
    * Should be able to modify the ActorNode class member variable, or use
    * a function to add edges/nodes to the list of edges/nodes in ActorNode
    * class
    */
   void makeEdges();

   /**
    * Get the name of the movie
    */
   string getMovieName() const;

   /**
    * Get the year of the movie
    */
   int getMovieYear() const;
};

#endif // MOVIEGRAPH_H
