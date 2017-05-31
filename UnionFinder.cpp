#include "UnionFinder.h"

UnionFinder::UnionFinder(void)
{
    allNodes = set<ActorNode *, compareNodes>();
}

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

    // Initialize all edges, and other member variables of the graph
    allMovies = movieList.getAllMovieNames();

    return true; 
}

// print the number of nodes and movies in the graph
void UnionFinder::printStats( ostream& out ) const
{
    out << "#nodes: " << allNodes.size() << std::endl;
    out << "#movies: " << allMovies.size() << std::endl;
}

// print all the actor names and the earliest year in which they are connected to the output stream
void UnionFinder::printAllYears( std::vector< std::pair< std::string, std::string> > pairs, ostream& out )
{
    // initialize a vector of found years
    std::vector<int> allFoundYears( pairs.size(), 0 );
    std::vector< std::pair< ActorNode *, ActorNode *> > pointerPairs;
    for (int i = 0; i < pairs.size(); i++)
    {
        ActorNode * start = new ActorNode( pairs[i].first );
        ActorNode * end = new ActorNode( pairs[i].second );
        auto it_start = allNodes.find( start );
        auto it_end = allNodes.find( end );
        delete start;
        delete end;

        if (it_start == allNodes.end() || it_end == allNodes.end())
        {
            allFoundYears[i] = 9999;
            pointerPairs.push_back( make_pair(nullptr, nullptr) );
        }
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
        allYears.insert(allMovies[i]->getYear());
    }

    auto it_year = allYears.begin();
    auto it_graph = movieList.listOfGraphs.begin();
    MovieGraph * curr;

    // initialize all prev fields to be nullptr
    for (auto it = allNodes.begin(); it != allNodes.end(); it++)
    {
        (*it)->prev = nullptr;
    }

    while (it_year != allYears.end() )
    {
        // create the disjoint sets of all the movies before the current year
        //cout << "Looping in year: " << *it_year << endl;
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
                //cout << "stuck here" << endl;
                for (int i = 0; i < curr->listOfActors.size(); i++)
                {
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
                //cout << "stuck here 2" << endl;
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
        
        //cout << "done with previous year!" << endl;

        for (int i = 0; i < pairs.size(); i++)
        {
            if (allFoundYears[i] == 0)
            {
                if (pointerPairs[i].first->unionFind(pointerPairs[i].second))
                {
                    allFoundYears[i] = *it_year;
                }
            }
        }

        it_year++;
    }

    for (int i = 0; i < allFoundYears[i]; i++)
    {
        // none is found if it is still 0 by now
        if (allFoundYears[i] == 0) allFoundYears[i] = 9999;
        out << pairs[i].first << "\t" << pairs[i].second << "\t" << allFoundYears[i] << "\n";
    }
}

