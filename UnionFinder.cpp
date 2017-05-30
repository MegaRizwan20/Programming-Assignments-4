#include "UnionFinder.h"

UnionFinder::UnionFinder(void)
{
    allNodes = set<ActorNode *, compareNodes>();
}

UnionFinder::~UnionFinder()
{

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

    // Initialize all edges, and other member variables of the graph
    allMovies = movieList.getAllMovieNames();

    return true; 
}

// print the number of nodes, edges and movies in the graph
void UnionFinder::printStats( ostream& out ) const
{
    out << "#nodes: " << allNodes.size() << std::endl;
    out << "#movies: " << allMovies.size() << std::endl;
  	int sum = 0;
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
      sum += (*it)->getNumEdges();
    }	
  
  	out << "#edges: " << sum << std::endl;
}

// print all the actor names and the earliest year in which they are connected to the output stream
void UnionFinder::printAllYears( std::vector< std::pair< std::string, std::string> >, ostream& out )
{

}

