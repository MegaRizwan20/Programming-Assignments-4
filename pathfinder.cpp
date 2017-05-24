// FILE HEADER HERE

#include <fstream>
#include <iostream>

#include "ActorGraph.h"
#include "ActorNode.h"
#include "ActorEdge.h"
#include "ActorPath.h"
#include "MovieName.h"

using namespace std;

// for temporary testing
//int main()
int main (int argc, char* argv[])
{
    // Make sure to add all the user input error parsings here

    // initiate graph
    ActorGraph graph;
    ActorPath* twoActors;
    static bool weight = true;
    if (argv[2] == "u")
    {
      weight = false;
    }
    std::cout << "Loading from file, this might take a while..." << flush;
    cout << endl;
    graph.loadFromFile( argv[1], false );
    graph.printStats(cout);
    cout << "done!" << endl;

    ifstream infile(argv[3]);
    ofstream outfile(argv[4]);

    // WHERE TWO COLUMN READING
    bool header_check = false;

    //MovieList movieList;
    outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;
    // Read lines until we reach the end of the file
    while (infile)
    {
      string s;
      // Get the next lines in a file
      if (!getline(infile, s))
      {
        break;
      }
      // Skip header part
      if (!header_check)
      {
        header_check = true;
        continue;
      }

      istringstream ss(s);
      vector<string> record;
   
      while(ss)
      {
        string next;
        // Get next string before hitting tab character and put it in next
        if (!getline(ss, next, '\t'))
        {
          break;
        }

        record.push_back(next);
     
      }
      // Should have exactly 2 columns
      if (record.size() != 2)
      {
        continue;
      }

      // The names of the 2 actors
      string actor1(record[0]);
      string actor2(record[1]);

      twoActors = graph.findPath(actor1, actor2);

      if (twoActors == nullptr)
      {
        cout << " PATH NOT FOUND!!! " << endl;
      }
      else
      {
        cout << "Computing path for (" << actor1 << ") -> (" << actor2 << ")" <<endl;
        twoActors->printPath(outfile);
        delete twoActors;
      }
    // End of outer while loop 
    }

    if (!infile.eof())
    {
      cerr << "Failed to read " << argv[3] << "!\n";
      delete twoActors;
      return -1;
    }
    infile.close();
    return 0;
}