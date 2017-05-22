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
        std::set<ActorNode *, compareNodes>::iterator it = allNodes.find( tempNode );

        // if it does not exist
        if (it == allNodes.end() )
        {
            allNodes.insert( tempNode );
        }
        // else if it exists
        else
        {
            delete tempNode;
            tempNode = *it;
        }

        movieList.addActorNode( tempNode, movie_title, movie_year );
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
ActorPath * ActorGraph::findPath( std::string start_name, std::string end_name ) const
{
    ActorNode temp_start(start_name);
    ActorNode temp_end(end_name);
    auto it_start = allNodes.find( &temp_start );
    auto it_end = allNodes.find( &temp_end );

    if (it_start == allNodes.end() || it_end == allNodes.end())
    {
        return nullptr;
    }

    ActorNode * start = *it_start;
    ActorNode * end = *it_end;
    ActorPath * ret = new ActorPath(start);

    // Path is already complete if the start and end nodes are the same
    if (start == end) return ret;

}
