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
    disjoint = false;
}

ActorGraph::ActorGraph(bool p_disjoint)
{
    allNodes = set< ActorNode *, compareNodes >();
    prevSearch = nullptr;
    disjoint = p_disjoint;
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

    MovieList movieList(disjoint);
  
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

    if (prevSearch != start || end->prev == nullptr || prevIsBFS == true)
    {
        prevSearch = start;
        prevIsBFS = false;
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
            v->dist = weight;

            if (v->done == false)
            {
                v->done = true;

                // IMPORTANT: put "true" in this parameter to make the edges weighted
                neighbors = v->getAdjacentNodes(weighted);

                for (int i = 0; i < neighbors.size(); i++)
                {
                    // don't need to add neighbors that are already searched
                    if (neighbors[i].first->done == true) continue;

                    // find the total distance to get to the new neighbor
                    int c = v->dist + neighbors[i].second;
                    if (c < neighbors[i].first->dist)
                    {
                        neighbors[i].first->prev = v;
                        neighbors[i].first->dist = c;
                        queue.push( std::make_pair( c, neighbors[i].first ) );
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

// For this part, we might need the graph to become a minimum spanning tree first
int ActorGraph::bfsMin( std::string start_name, std::string end_name )
{
    ActorNode * start = new ActorNode(start_name);
    ActorNode * end = new ActorNode(end_name);
    ActorNode * v;
    std::vector< std::pair< ActorNode *, int > > neighbors;
    int weight;
    auto it_start = allNodes.find( start );
    auto it_end = allNodes.find( end );
    int retYear = 9999;
    delete start;
    delete end;
  
    if (it_start == allNodes.end() || it_end == allNodes.end())
    {
      	cout << "One or both of these actor names do not exist!" << endl;
        return retYear;
    }

    start = *it_start;
    end = *it_end;

    // Path is already complete if the start and end nodes are the same
    if (start == end) 
    {
      return retYear;
    }

    prevIsBFS = true;

    // perform a bfs search from the start node to the end node
    std::priority_queue< std::pair<ActorNode *, int>, 
        std::vector<std::pair<ActorNode *, int>>, compareYears> queue;
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
        v = *it;
        v->dist = 0;
        v->prev = nullptr;
        v->done = false;
    }
    
    queue.push( make_pair(start, 0) );
    ActorNode * curr = nullptr;
    while ( !queue.empty() )
    {
        // get the top element of the queue
        queue.top().first->prev = curr;
        curr = queue.top().first;
        int year = queue.top().second;
        if (curr->prev == nullptr)
        {
            curr->dist = year;
        }
        else if (year > curr->prev->dist)
        {
            curr->dist = year;
        }
        else
        {
            year = curr->prev->dist;
            curr->dist = year;
        }
 
        // if the curr node is actually the end node
        if (curr == end)
        {
            // find the path with the smallest year
            if (year < retYear)
            {
                retYear = year;
            }
            break;
        }

        queue.pop();
        if (curr->done == false)
        {
            curr->done = true;

            // get all the adjacent nodes with the year of the edge
            neighbors = curr->getNodesAndYears();

            // add the neighbors to the queue if they are not being visited yet
            for (int i = 0; i < neighbors.size(); i++)
            {
                if ( ! neighbors[i].first->done )
                {
                    queue.push( neighbors[i] );
                }
            }
        }
    }

    return retYear;
}

int ActorGraph::unionFind( std::string start_name, std::string end_name )
{
    ActorNode * start = new ActorNode(start_name);
    ActorNode * end = new ActorNode(end_name);
    ActorNode * v;
    std::vector< std::pair< ActorNode *, int > > neighbors;
    int weight;
    auto it_start = allNodes.find( start );
    auto it_end = allNodes.find( end );
    int retYear = 0;
    delete start;
    delete end;
  
    if (it_start == allNodes.end() || it_end == allNodes.end())
    {
      	cout << "One or both of these actor names do not exist!" << endl;
        return retYear;
    }

    start = *it_start;
    end = *it_end;

    // Path is already complete if the start and end nodes are the same
    if (start == end) 
    {
      return retYear;
    }

    ActorNode * start_set = start;
    ActorNode * end_set = end;
    int year;
    while (start_set->getNumEdges() != 0)
    {
        year = start_set->getFirstEdge()->getMovieName()->getYear();
        if (year > retYear)
        {
            retYear = year;
        }
        start_set = start_set->getFirstEdge()->getNextNode();
    }

    while (end_set->getNumEdges() != 0)
    {
        year = end_set->getFirstEdge()->getMovieName()->getYear();
        if (year > retYear)
        {
            retYear = year;
        }
        end_set = end_set->getFirstEdge()->getNextNode();
    }

    if (start_set == end_set) return retYear;
    else return 9999;
}
