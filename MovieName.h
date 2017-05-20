/*
 * FileName: MovieName.h
 *
 * Authors:
 * Date:
 * CSE Login:
 * Email:
 * PID:
 */


#ifndef MOVIENAME_H
#define MOVIENAME_H

#include <string>

using namespace std;

class MovieName
{
  private:
  
  	int year;
  	std::string movieName;
  
  public:
  
    // The constructor
    MovieName(string movieName, int year);

    // The destructor
    ~MovieName();


    /**
     * Used to get the name of the movie. Hoping to pass the name of 
     * the movie by doing a pass by reference. Should store the name of
     * the movie within a string. 
     */
    void getName(string& movieName) const;

    /**
     * Used to get the year of the movie. Should do a pass by reference of
     * the year of the movie. Should store the year of the movie within
     * an integer.
     */
    void getYear(int& year) const;

    /**
     * Gets the weight of the movie by doing weight = 1 + (2015 -Y). Returns
     * the weight of the movie 
     */
    int getWeight() const;

    /**
     * Comparing the movie name that we get to another movie name and seeing
     * which one is greater.
     */
    bool operator> (const MovieName& movie) const;


    // ALL OTHER NECESSARY HELPER FUNCTIONS BELOW HERE
};

#endif // MOVIENAME_H
