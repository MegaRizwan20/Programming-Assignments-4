/*
 * ActorGraph.cpp
 * Author: Rizwan Khan, Yiming Cai
 * Date:   6/5/17
 *
 * This file is meant to exist as a container for starter code that you can use 
 * to read the input file format defined in movie_casts.tsv. Feel free to 
 * modify any/all aspects as you wish.
 */

#include "ActorGraph.h"

using namespace std;

// We call the constructor
ActorGraph::ActorGraph(void) 
{
    // Set what we searched for before as nullptr
    prevSearch = nullptr;
}

// The destructor the deallocate all the data we allocated on the heap
ActorGraph::~ActorGraph() 
{
    // Delete all the movies in the vector
    for (int i = 0; i < allMovies.size(); i++)
    {
        delete allMovies[i];
    }

    // Delete all the iterators
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
        delete *it;
    }
}

/* Print out all the statistics of running the program such as how many nodes
 * were made, number of movies in the graph and how many edges connecct the
 * movies
 */
void ActorGraph::printStats( ostream& out ) const
{
    out << "#nodes: " << allNodes.size() << std::endl;
    out << "#movies: " << allMovies.size() << std::endl;
    int sum = 0;
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
      sum += (*it)->getNumEdges();
    }
  	
  	// uncomment if you want to get the number of undirected edges
  	//sum /= 2;
  
  	out << "#edges: " << sum << std::endl;
}

// This function will initialize the graph, along with all the nodes, edges and movienames
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) 
{
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    MovieList movieList;
  
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

    // Initialize all edges, and other member variables of the graph
    movieList.makeAllEdges();
    allMovies = movieList.getAllMovieNames();
    weighted = use_weighted_edges;

    return true;
}

// This function returns a pointer to a heap-allocated ActorPath instance
// Depending on the implementation of this class, the caller might have
// to manually deallocate the returned pointer to prevent leaks.
// Return null if the start_name or end_name is not in the graph
ActorPath * ActorGraph::findPath(std::string start_name, std::string end_name)
{
    // Initialize a new actor Node for the start
    ActorNode * start = new ActorNode(start_name);
    // Initialize a new actor node for the end
    ActorNode * end = new ActorNode(end_name);
    // Actor node used to call the necessary functions
    ActorNode * v;
    // Initializze a vector to store the necessary data
    std::vector< std::pair< ActorNode *, int > > neighbors;
    // Used to get the weight of the actors
    int weight;
    // Where we start iterating through the graph
    auto it_start = allNodes.find( start );
    // Iterator used to find the end of the graph
    auto it_end = allNodes.find( end );
    // Delete the memory allocated so no memory leaks, but we still use the
    // nodes themselves
    delete start;
    delete end;
  
    // If we are at the end or they do not exist
    if (it_start == allNodes.end() || it_end == allNodes.end())
    {
      	cout << "One or both of these actor names do not exist!" << endl;
        return nullptr;
    }

    start = *it_start;
    end = *it_end;
    ActorPath * ret = new ActorPath(start);

    // Path is already complete if the start and end nodes are the same
    if (start == end) 
    {
      return ret;
    }

    if (prevSearch != start || end->prev == nullptr)
    {
        prevSearch = start;
        // Use the Dijkstra algorithm to find the path
        // Initialize a priority queue to use and store the data
        std::priority_queue< std::pair<int, ActorNode *>, 
        std::vector<std::pair<int, ActorNode *>>, compareInQueue > queue;
        // Initialize all the data in the nodes so we set everything to
        // infinity, nullptr and false before doing the main part of
        // djikstra's algorithm.
        for (auto it = allNodes.begin(); it != allNodes.end(); it++)
        {
            v = *it;
            v->dist = INT_MAX;
            v->prev = nullptr;
            v->done = false;
        }

        // Set the distance to 0
        start->dist = 0;
        // Push onto the queue and make a pair
        queue.push( make_pair(start->dist, start) );

        // While the queue is not empty
        while (!queue.empty())
        {
            // To keep track of current node
            std::pair<int, ActorNode *> curr = queue.top();
            // Pop because we don't need it anymore
            queue.pop();
            // Get the weight
            int weight = curr.first;
            v = curr.second;

            // While actor node is false
            if (v->done == false)
            {
                v->done = true;
                
                // IMPORTANT: put "true" in this parameter to make the edges weighted
                neighbors = v->getAdjacentNodes(weighted);

                // This is to add all the neighboring nodes that will be needed 
                for (int i = 0; i < neighbors.size(); i++)
                {
                    // don't need to add neighbors that are already searched
                    // if (neighbors[i].first->done == true) continue;

                    // find the total distance to get to the new neighbor
                    int c = neighbors[i].second + v->dist;
    
                    // Check if our number is less than the distance so we can
                    // set all the necessary data
                    if (c < neighbors[i].first->dist)
                    {
                        neighbors[i].first->prev = v;
                        neighbors[i].first->dist = c;
                        queue.push( make_pair( c, neighbors[i].first) );
                    }
                }
            }

        }
    }

    // If we reach the end, we delete the ret and return nullptr
    if (end->prev == nullptr)
    {
      delete ret;
      return nullptr;
    }

    // time to construct the path
    std::stack<ActorNode *> stack;
    ActorNode * curr = end;
    ActorNode * prev;
    // While it is not a nullptr we push it onto the stack
    while (curr != nullptr)
    {
        stack.push(curr);
        curr = curr->prev;
    }

    // We want to get the data in the stack
    curr = stack.top();
    stack.pop();
    // While it is not empty we want to create the edges needed and return it
    while (!stack.empty()) 
    {
        prev = curr;
        curr = stack.top();
        stack.pop();

        ret->addEdge( prev->findEdge(curr) );
    }

    // for the compiler, for now
    return ret;
}


