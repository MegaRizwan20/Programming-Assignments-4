/*
 * FileName: MovieName.h
 *
 * Authors: Rizwan Khan, Yiming Cai
 * Date: 6/5/17
 * 
 * The header file for MovieName.cpp
 */


#ifndef MOVIENAME_H
#define MOVIENAME_H

#include <string>

using namespace std;

// The MovieName class
class MovieName
{
  // The data that can only be accessed by MovieName.cpp
  private:
  
  	int year;
  	std::string movieName;
  
  public:
  
    // The constructor
    MovieName(string p_movieName, int p_year);

    // The destructor
    ~MovieName();


    /**
     * Used to get the name of the movie. Hoping to pass the name of 
     * the movie by doing a pass by reference. Should store the name of
     * the movie within a string. 
     */
    void getName(string& g_movieName) const;
    string getName() const;

    /**
     * Used to get the year of the movie. Should do a pass by reference of
     * the year of the movie. Should store the year of the movie within
     * an integer.
     */
    void getYear(int& g_year) const;
    int getYear() const;

    /**
     * Gets the weight of the movie by doing weight = 1 + (2015 -Year). 
     * Returns the weight of the movie 
     */
    int getWeight() const;

};

#endif // MOVIENAME_H
