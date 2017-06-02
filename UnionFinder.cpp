#include "UnionFinder.h"

// Constructor.
UnionFinder::UnionFinder(void)
{
  
}

// Destructor. deallocate all the nodes and moviename instances
// All other instances are allocated on stack so they don't need
// to be manually deleted
// All the edges are deleted along with their nodes so we don't
// have to worry about them here
UnionFinder::~UnionFinder()
{
    for (int i = 0; i < allMovies.size(); i++)
    {
        delete allMovies[i];
    }

    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
        delete *it;
    }
}

// Maybe add some more methods here

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool UnionFinder::loadFromFile(const char* in_filename)
{
   // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false; 

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // we have an actor/movie relationship, now see if actor already exists
        ActorNode * tempNode = new ActorNode(actor_name);
        auto pair = allNodes.insert( tempNode );

        // if it does not exist
        if (!pair.second)
        {
            delete tempNode;
        }

        movieList.addActorNode( *(pair.first), movie_title, movie_year );
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    // get a list of pointers to all the MovieName instances for memory
    // management later on
    allMovies = movieList.getAllMovieNames();

    return true; 
}

// print the number of nodes and movies in the graph
void UnionFinder::printStats( ostream& out ) const
{
    out << "#nodes: " << allNodes.size() << std::endl;
    out << "#movies: " << allMovies.size() << std::endl;
  
    // calculate the number of edges in the case that a graph is constructed
    // since each movieGraph creates a complete graph, which has a total number of edges
    // of n*(n-1), we just need to find the number of edges generated in each movieGraph
    // and sum them all up
    int sum = 0;
    for (auto it = movieList.listOfGraphs.begin(); it != movieList.listOfGraphs.end(); it++)
    {
        sum += (*it)->listOfActors.size() * ( (*it)->listOfActors.size() - 1) ;
    }
    out << "#edges: " << sum << std::endl;
  
  /* ---------------------------------------------------------------
  * This is just used to generate a random test pairs file
  * Need to include fstream, time.h, and stdlib.h for this to work
  * ----------------------------------------------------------------
  ofstream file;
  file.open( "many_pairs.tsv" );
  file << "actor1\tactor2\n";
  srand (time(NULL));
  for (int i = 0; i < 1000; i++)
  {
    int random = rand() % allNodes.size();
    auto it = allNodes.begin();
    std::advance(it, random);
   	string actor1 = (*it)->getActorName();
    
    random = rand() % allNodes.size();
    it = allNodes.begin();
    std::advance(it, random);
   	string actor2 = (*it)->getActorName();
    file << actor1 << "\t" << actor2 << "\n" ;
  }
  *---------------------------------------------------------------- */
}

// print all the actor names and the earliest year in which they are connected to the output stream
void UnionFinder::printAllYears( std::vector< std::pair< std::string, std::string> > pairs, ostream& out )
{
    // initialize a vector of found years
    std::vector<int> allFoundYears( pairs.size(), 0 );
    std::vector< std::pair< ActorNode *, ActorNode *> > pointerPairs;
    for (int i = 0; i < pairs.size(); i++)
    {
      	// construct temporary nodes to search its location in the set
        ActorNode * start = new ActorNode( pairs[i].first );
        ActorNode * end = new ActorNode( pairs[i].second );
        auto it_start = allNodes.find( start );
        auto it_end = allNodes.find( end );
      
        // delete them after getting the iterators
        delete start;
        delete end;

      	// if either name is not in the list, make it 9999 
        if (it_start == allNodes.end() || it_end == allNodes.end())
        {
            allFoundYears[i] = 9999;
            pointerPairs.push_back( make_pair(nullptr, nullptr) );
        }
      
      	// otherwise push the pair of nodes onto the new vector
        // so that we don't need to perform the find operation 
        // repeatedly
        else
        {
            start = *it_start;
            end = *it_end;
            pointerPairs.push_back( make_pair(start, end) );
        }
    }


    // Preprocess all the years
    std::set<int> allYears;
    for (int i = 0; i < allMovies.size(); i++)
    {
      	// a set ensures that no duplicate year is inserted
        allYears.insert(allMovies[i]->getYear());
    }

  	// use iterators to keep track of which year and set of nodes
    // should be included in the union operation.
    auto it_year = allYears.begin();
    auto it_graph = movieList.listOfGraphs.begin();
    MovieGraph * curr;

    // initialize all prev fields to be nullptr
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
      	// note that prev is used to represent the parent pointer
        (*it)->prev = nullptr;
      
      	// note that the edges field is used to represent the 
        // edges to the children only (referring to incoming edges
        // in the uptree structure)
      	(*it)->clearEdges();
    }

    while (it_year != allYears.end() )
    {
        // create the disjoint sets of all the movies before the current year
        while (it_graph != movieList.listOfGraphs.end() && (*it_graph)->getMovieYear() == *it_year )
        {
            curr = *it_graph;

            // find a sentinel node (not in any set already), if there is 1
            int sentinel = -1;
            ActorNode * node;
            for (int i = 0; i < curr->listOfActors.size(); i++)
            {
                if (curr->listOfActors[i]->prev == nullptr && curr->listOfActors[i]->getFirstEdge() == nullptr)
                {
                    sentinel = i;
                    break;
                }
            }

            // have all the lone actor nodes point to the sentinel node
            if (sentinel != -1)
            {
                for (int i = 0; i < curr->listOfActors.size(); i++)
                {
                  	// check if both the parent pointer and child pointers are null
                    if ( curr->listOfActors[i]->prev == nullptr && curr->listOfActors[i]->getFirstEdge() == nullptr)
                    {
                        if ( curr->listOfActors[i] != curr->listOfActors[sentinel] )
                        {
                            curr->listOfActors[i]->prev = curr->listOfActors[sentinel];
                            curr->listOfActors[sentinel]->addEdge(curr->listOfActors[i], curr->getMoviePointer());
                        }
                    }
                    
                    // union with nodes that already belong to another set
                    else
                    {
                        if (i != sentinel)
                        {
                            curr->listOfActors[sentinel]->unionWith(curr->listOfActors[i], curr->getMoviePointer());
                        }
                    }
                }
            }

            // have all the sets union with each other if possible
            else
            {
                for (int i = 0; i < curr->listOfActors.size(); i++)
                {
                    for (int j = i+1; j < curr->listOfActors.size(); j++)
                    {
                        curr->listOfActors[i]->unionWith(curr->listOfActors[j], curr->getMoviePointer());
                    }
                }
            }

            it_graph++;
        }
        
        // used to check if every single pairs are found already. If yes, break out of main loop
        bool allFound = true;
      
        // for each pair, check if they are already in the same set
        for (int i = 0; i < pairs.size(); i++)
        {
          	// check only the pairs whose years are still unset (0 by default)
            if (allFoundYears[i] == 0)
            {
                if (pointerPairs[i].first->unionFind(pointerPairs[i].second))
                {
                    allFoundYears[i] = *it_year;
                }
                else
                {
                    allFound = false;
                }
            }
        }
        if (allFound) break;

        it_year++;
    }

  	// print the actor names and found years to the output stream that is given as a parameter
    for (int i = 0; i < allFoundYears.size(); i++)
    {
        // no path is found if the found year for the pair is still 0 at this point
        if (allFoundYears[i] == 0) allFoundYears[i] = 9999;
        out << pairs[i].first << "\t" << pairs[i].second << "\t" << allFoundYears[i] << "\n";
    }
}

// print all the actor names and the earliest year in which they are connected to the output stream
// This function uses the 'existPath' function, which is basically using bfs to check if there exists
// a path between a pair of nodes
void UnionFinder::bfsAllPairs( std::vector< std::pair< std::string, std::string> > pairs, ostream& out )
{
      // initialize a vector of found years
    std::vector<int> allFoundYears( pairs.size(), 0 );
    std::vector< std::pair< ActorNode *, ActorNode *> > pointerPairs;
    for (int i = 0; i < pairs.size(); i++)
    {
      	// construct temporary nodes to search its location in the set
        ActorNode * start = new ActorNode( pairs[i].first );
        ActorNode * end = new ActorNode( pairs[i].second );
        auto it_start = allNodes.find( start );
        auto it_end = allNodes.find( end );
      
        // delete them after getting the iterators
        delete start;
        delete end;

      	// if either name is not in the list, make it 9999 
        if (it_start == allNodes.end() || it_end == allNodes.end())
        {
            allFoundYears[i] = 9999;
            pointerPairs.push_back( make_pair(nullptr, nullptr) );
        }
      
      	// otherwise push the pair of nodes onto the new vector
        // so that we don't need to perform the find operation 
        // repeatedly
        else
        {
            start = *it_start;
            end = *it_end;
            pointerPairs.push_back( make_pair(start, end) );
        }
    }


    // Preprocess all the years
    std::set<int> allYears;
    for (int i = 0; i < allMovies.size(); i++)
    {
      	// a set ensures that no duplicate year is inserted
        allYears.insert(allMovies[i]->getYear());
    }

  	// use iterators to keep track of which year and set of nodes
    // should be included in the union operation.
    auto it_year = allYears.begin();
    auto it_graph = movieList.listOfGraphs.begin();
    MovieGraph * curr;

    // initialize all prev fields to be nullptr
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    { 
      	// note that the edges field is used to represent the 
        // edges to the children only (referring to incoming edges
        // in the uptree structure)
      	(*it)->clearEdges();
    }

    while (it_year != allYears.end() )
    {
        // create the disjoint sets of all the movies before the current year
        while (it_graph != movieList.listOfGraphs.end() && (*it_graph)->getMovieYear() == *it_year )
        {
            curr = *it_graph;

            curr->makeEdges();

            it_graph++;
        }
        
        // used to check if every single pairs are found already. If yes, break out of main loop
        bool allFound = true;
      
        // for each pair, check if they are already in the same set
        for (int i = 0; i < pairs.size(); i++)
        {
          	// check only the pairs whose years are still unset (0 by default)
            if (allFoundYears[i] == 0)
            {
                if (existPath( pointerPairs[i].first, pointerPairs[i].second ) )
                {
                    allFoundYears[i] = *it_year;
                }
                else
                {
                    allFound = false;
                }
            }
        }
        if (allFound) break;

        it_year++;
        cout << "going to the next year: " << *it_year << endl;
    }

  	// print the actor names and found years to the output stream that is given as a parameter
    for (int i = 0; i < allFoundYears.size(); i++)
    {
        // no path is found if the found year for the pair is still 0 at this point
        if (allFoundYears[i] == 0) allFoundYears[i] = 9999;
        out << pairs[i].first << "\t" << pairs[i].second << "\t" << allFoundYears[i] << "\n";
    }
}

bool UnionFinder::existPath( ActorNode * actor1, ActorNode * actor2)
{
      // initialize all prev fields to be nullptr
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    { 
      	// note that the edges field is used to represent the 
        // edges to the children only (referring to incoming edges
        // in the uptree structure)
      	(*it)->done = false;
    }
  
    ActorNode * end = actor2;
  	ActorNode * curr = actor1;
    
    std::queue<ActorNode *> queue;
    queue.push(curr);
    while (!queue.empty())
    {
      curr = queue.front();
      queue.pop();
      curr->done = true;
      if (curr == end) break;
      cout << "stuck here? " << endl;
      
      // push a bunch of neighbor nodes onto the queue if they are not on the 
      // queue before already
      std::vector< ActorNode * > neighbors = curr->getNeighbors();
      for (int i = 0; i < neighbors.size(); i++)
      {
       	if (!neighbors[i]->done)
        {
          queue.push(curr);
        }
      }
      
    }
  
    return end->done;
}