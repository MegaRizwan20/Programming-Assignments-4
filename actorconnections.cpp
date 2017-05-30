// FILE HEADER HERE

#include <fstream>
#include <iostream>
#include <string.h>
#include <errno.h>

#include "ActorGraph.h"
#include "ActorNode.h"
#include "ActorEdge.h"
#include "ActorPath.h"
#include "MovieName.h"

#define USAGE "Usage: ./pathfinder 3_column_file.tsv 2_column_file.tsv output_file [bfs/ufind]\n" 
using namespace std;

// for temporary testing
//int main()
int main (int argc, char* argv[])
{
    // Make sure to add all the user input error parsings here
  	if (argc != 5 && argc!= 4)
    {
      std::cerr << "Incorrect number of inputs!" << std::endl;
      std::cerr << USAGE;
    }
  
    // Check input and output file validity
    errno = 0;
    ifstream inFile;
    inFile.open( argv[1] );
    if (errno != 0 || !inFile.is_open())
    {
        cerr << "Error: " << strerror(errno) << endl;
        cerr << USAGE;
        return -1;
    }
  	inFile.close();
  	
  	inFile.open(argv[2]);
    if (errno != 0 || !inFile.is_open())
    {
        cerr << "Error: " << strerror(errno) << endl;
        cerr << USAGE;
        return -1;
    }
  	inFile.close();
  
    ofstream outFile;
    outFile.open( argv[3] );
    if (errno != 0 )
    {
        cerr << "Error: " << strerror(errno) << endl;
        cerr << USAGE;
        return -1;
    }
  
  	// check weight input
    bool disjoint;
    if (argc == 5)
    {
        if ( strcmp( argv[4], "ufind") == 0 )
        {
            disjoint = true;
        }
        else if ( strcmp( argv[4], "bfs") == 0 )
        {
            disjoint = false;
        }
        else
        {
            std::cerr << "Invalid flag input!" << std::endl;
            std::cerr << USAGE;
            return -1;
        }
    }
    else
    {
        disjoint = true;
    }

    ActorGraph graph(disjoint);
  
  	// Load graph from the input file
    std::cout << "Loading from file, this might take a while..." << std::endl;
    if ( !graph.loadFromFile( argv[1], false ) )
    {
      cerr << USAGE;
      return -1;
    }
    graph.printStats(cout);
    cout << "done!" << endl;
  	
  	// initialize pair input and output files
    ifstream infile(argv[2]);
    ofstream outfile(argv[3]);

    // WHERE TWO COLUMN READING
    bool header_check = false;

    // output file header;
    outfile << "actor1\tactor2\tyear" << endl;
  
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
      int year;
      if (disjoint)
      {
        year = graph.unionFind(actor1, actor2);
      }
      else
      {
        year = graph.bfsMin( actor1, actor2 );
      }
   
      if (year == 9999)
      {
        cerr << " Path is not found for the pair (" << actor1 << ") -> (" << actor2 << ")" <<endl;
      }
      else
      {
        cout << "Found year is: " << year << endl;
      }
    // End of outer while loop 
    }

  	// if the loop is broken out before eof is reached, exit with failure
    if (!infile.eof())
    {
      cerr << "Failed to read " << argv[2] << "!\n";
      std::cerr << USAGE;
      return -1;
    }
  
  	// Ended program successfully
    infile.close();
    return 0;
}
