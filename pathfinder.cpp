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
    //std::cout << "done!" << std::endl;
    graph.printStats(cout);
    cout << "done!" << endl;
    //graph.printStats(std::cout);

    /*ActorPath * path = graph.findPath( "A4", "A1" );
	if (path == nullptr)
    {
      cout << "PATH NOT FOUND!!" << endl;
    }
  	else
    {
      path->printPath(std::cout);
      delete path;
    }
  */
    //return 0;

    //ifstream infile(fileIn);
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

      //ActorNode * tempNode = new ActorNode(actor1);
      //ActorNode * temp2 = new ActorNode(actor2);
      //auto pair = allNodes.insert(tempNode);
      //ActorPath* twoActors;
      twoActors = graph.findPath(actor1, actor2);

      /*if (!infile.eof())
      {
        cerr << "Failed to read " << argv[3] << "!\n";
        delete twoActors;
        return false;
      }
      infile.close();

      cout << " Done! " << endl;
      */
      //graph.printStats(std::cout);
      //graph.printStats(outfile);

      if (twoActors == nullptr)
      {
        cout << " PATH NOT FOUND!!! " << endl;
      }
      else
      {
        // Print out to the outfile
        //twoActors->printPath(std::cout);
        //cout << "Computing Path for " << twoActors << endl;
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
      return false;
    }
    infile.close();
    //cout << "Done! " << endl;
    
    //graph.printStats(std::cout);
    //graph.printStats(outfile);

    /*if (twoActors == nullptr)
    {
      cout << " PATH NOT FOUND!!! " << endl;
    }
    else
    {
      // Print out to the outfile
      //twoActors->printPath(std::cout);
      twoActors->printPath(outfile);
      delete twoActors;
    }*/

    return 0;


    /*if (!infile.eof())
    {
      cerr << "Failed to read " << argv[3] << "!\n";
      delete twoActors;
      return false;
    }
    infile.close();

    cout << " Done! " << endl;
    graph.printStats(std::cout);

    if (twoActors == nullptr)
    {
      cout << " PATH NOT FOUND!!! " << endl;
    }
    else
    {
      twoActors->printPath(std::cout);
      delete twoActors;
    }*/
    //return 0;
}
/*
bool load2ColumnFile(const char* fileIn, bool weighted_edges)
{
  //allNodes = set<ActorNode *, compareNodes>();
  
  ifstream infile(fileIn);

  bool header_check = false;

  //MovieList movieList;

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

    //ActorNode * tempNode = new ActorNode(actor1);
    //ActorNode * temp2 = new ActorNode(actor2);
    //auto pair = allNodes.insert(tempNode);
    ActorPath* twoActors;

  // End of outer while loop 
  }
}*/
