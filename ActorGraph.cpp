/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) 
{
    allNodes = set< ActorNode *, compareNodes >();
    prevSearch = nullptr;
}

ActorGraph::~ActorGraph() 
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
ActorPath * ActorGraph::findPath( std::string start_name, std::string end_name )
{
    ActorNode * start = new ActorNode(start_name);
    ActorNode * end = new ActorNode(end_name);
    ActorNode * v;
    std::vector< std::pair< ActorNode *, int > > neighbors;
    int weight;
    auto it_start = allNodes.find( start );
    auto it_end = allNodes.find( end );
    delete start;
    delete end;
  
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
        std::priority_queue< std::pair<int, ActorNode *>, std::vector<std::pair<int, ActorNode *>>, compareInQueue > queue;
        for (auto it = allNodes.begin(); it != allNodes.end(); it++)
        {
            v = *it;
            v->dist = INT_MAX;
            v->prev = nullptr;
            v->done = false;
        }

        start->dist = 0;
        queue.push( make_pair(start->dist, start) );

        while (!queue.empty())
        {
            std::pair<int, ActorNode *> curr = queue.top();
            queue.pop();
            int weight = curr.first;
            v = curr.second;

            if (v->done == false)
            {
                v->done = true;
                //          	cout << "Start: " << start->getActorName() << ", End: " << v->getActorName() << ", TotalWeight: " << weight << endl;

                // IMPORTANT: put "true" in this parameter to make the edges weighted
                neighbors = v->getAdjacentNodes(weighted);


                for (int i = 0; i < neighbors.size(); i++)
                {
                    int c = v->dist + neighbors[i].second;
                    if (c < neighbors[i].first->dist)
                    {
                        neighbors[i].first->prev = v;
                        neighbors[i].first->dist = c;
                        queue.push( std::make_pair( c, neighbors[i].first ) );
                        //                  	cout << "Pushing neighbour: " << neighbors[i].first->getActorName() << ", dist: " << neighbors[i].first->dist << endl;
                    }
                }
            }

            // found the path to the end. stop.
            if (v == end) break;
        }
    }
  
  	if (end->prev == nullptr)
    {
      delete ret;
      return nullptr;
    }

    // time to construct the path
    std::stack<ActorNode *> stack;
    ActorNode * curr = end;
    ActorNode * prev;
    while (curr != nullptr)
    {
        stack.push(curr);
        curr = curr->prev;
    }

    curr = stack.top();
    stack.pop();
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
