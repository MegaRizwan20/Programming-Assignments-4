 /*
 * ActorNode.cpp
 * Author: Rizwan Khan, Yiming Cai
 * Date:   6/5/17
 *
 * This class is meant to be used to generate a node instance in the graph. 
 * Contains some useful methods and variables for graph traversal.
 */ 

#include "ActorNode.h"

// Constructor, initialize Actor's name and other variables
ActorNode::ActorNode( std::string actorName )
{
    name = actorName;
    edges = std::vector<ActorEdge *>();
}

// Destructor, probably need to deallocate edges if its allocated on the heap
ActorNode::~ActorNode()
{
    // Used to deallocate the edges
    for (auto it = edges.begin();
        it != edges.end(); ++it)
    {
        delete *it;
    }
}

// Getter for getting how many edges we made
int ActorNode::getNumEdges() const
{
	return edges.size();
}

// Add an edge to the node. Make the edge in this function
// If the edge already exist, just add the moviename to it
void ActorNode::addEdge( ActorNode * node, MovieName * name )
{
  	edges.push_back( new ActorEdge(node, name) );
}

// This is a sequential search. Since its a pointer comparison,
// this shouldn't take too long. This finds the edges that are needed
// to be found to properly do searches.
ActorEdge * ActorNode::findEdge( const ActorNode * node ) const
{
    // The weight of the movies
    int weight = 0;
    // The index to get to the movies
    int index = -1;
    // To loop through all the edges that exist
    for (int i = 0; i < edges.size(); i++)
    {
      // Check the existence of the edge
      if (edges[i]->getNextNode() == node)
      {
        // Check conditions to set the indexx
        if (weight == 0 || edges[i]->getWeight() < weight)
        {
          index = i;
        }
      }
    }
  
    // If the index stayed -1, we return nullptr
    if (index == -1)
    {
        return nullptr;
    }
    // Else we return the edges  itself at that index
    else
    {
        return edges[index];
    }
}

// Check if this actor has the same name as the input
bool ActorNode::isSameActor( std::string p_name ) const
{
    return (p_name.compare(name)) == 0;
}

// Return the actor name
std::string ActorNode::getActorName( ) const
{
    return name;
}

// Return the list of neighbour nodes and the weights of these edges
std::vector< std::pair<ActorNode *, int> > 
                    ActorNode::getAdjacentNodes(bool weighted) const
{
   // The vector we will return
    std::vector< std::pair<ActorNode *, int> > list;
    
    // If we are dealing with weighted edges
    if (weighted)
    {
        for (auto it = edges.begin();
                it != edges.end(); ++it)
        {
            ActorNode * tempNode = (*it)->getNextNode();
            int weight = (*it)->getWeight();
            list.push_back( std::make_pair(tempNode, weight) );
        }
    }
    // Else it is unweighted
    else
    {
        for (auto it = edges.begin();
                it != edges.end(); ++it)
        {
            ActorNode * tempNode = (*it)->getNextNode();
            list.push_back( std::make_pair(tempNode, 1) );
        }

    }

    // Return the list
    return list;
}

// Used to get the neighbors of the nodes, so we return a list of them
std::vector<ActorNode * > ActorNode::getNeighbors() const
{
    // The list we will return
    std::vector< ActorNode * > list;
    
    // If we are dealing with weighted edges
    for (auto it = edges.begin();
            it != edges.end(); ++it)
    {
        list.push_back( (*it)->getNextNode() );
    }

    return list;
}

// Wanting to get the very first edge
ActorEdge * ActorNode::getFirstEdge() const 
{
    // If there are no edges, return nullptr, else
    // return what is in the first index
    if (edges.size() == 0) return nullptr;
    return edges[0];
}


// Calling the union function to find the sets that
// exist
bool ActorNode::unionFind( ActorNode * ufind )
{
    // Initialize the actor nodes needed to do union finding
    ActorNode * this_set = this;
    ActorNode * u_set = ufind;
  
    // stacks for implementing path compression
    std::stack<ActorNode *> st;
     
    // find the sentinel node of this_set
    while (this_set->prev != nullptr)
    {
      	st.push(this_set);
        this_set = this_set->prev;
    }
  
  	// perform path compression for this_set
  	while (!st.empty())
    {
        (st.top())->prev = this_set;
        st.pop();
    }
    
  	// find the sentinel node of u_set
    while (u_set->prev != nullptr)
    {
        st.push(u_set);
        u_set = u_set->prev;
    }
  
  	// perform path compression for u_set
    while (!st.empty())
    {
        (st.top())->prev = u_set;
        st.pop();
    }
    
    // already in the same set, so quit
    return this_set == u_set;
}

// This method actually joins the union sets together
void ActorNode::unionWith( ActorNode * ufind, MovieName * p_name) 
{
    // Initialize the actor nodes
    ActorNode * this_set = this;
    ActorNode * u_set = ufind;
     
    // find the sentinel node of each set
    while (this_set->prev != nullptr)
    {
        this_set = this_set->prev;
    }
    
    while (u_set->prev != nullptr)
    {
        u_set = u_set->prev;
    }
    
    // already in the same set, so quit
    if (this_set == u_set )
    {
        return;    
    }

    // Find the height of each set
    int this_height = 0;
    int u_height = 0;
    ActorNode * curr = this_set;

    // traverse down the this_set to find its height
    while (curr->getFirstEdge() != nullptr)
    {
        curr = curr->getFirstEdge()->getNextNode();
        this_height++;
    }

    // traverse down the u_set to find its height
    curr = u_set;
    while (curr->getFirstEdge() != nullptr)
    {
        curr = curr->getFirstEdge()->getNextNode();
        u_height++;
    }

    // union the sets by having the sentinel node of the
    // smaller height point to the other sentinel node
    if (this_height < u_height)
    {
        this_set->prev = u_set;
        u_set->addEdge(this_set, p_name);
    }
    else
    {
        u_set->prev = this_set;
        this_set->addEdge(u_set, p_name);
    }
}

// This is used to get rid of all the edges that exist so we do not have
// memory leaks after running the code
void ActorNode::clearEdges()
{
    for (auto it = edges.begin();
        it != edges.end(); ++it)
    {
        delete *it;
    }
    edges.clear();
}
