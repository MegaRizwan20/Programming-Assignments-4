// header here   

#include "MovieGraph.h"

void MovieGraph::makeEdges() {
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