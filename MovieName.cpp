/*
 * FileName: MovieName.cpp
 *
 * Authors: Rizwan Khan, Yiming Cai
 * Date: 6/5/17
 * 
 * This is used to get all the important information regarding the movies
 */

#include "MovieName.h"
#include <string>

using namespace std;

// The Movie name constructor to create instances of movie names
MovieName::MovieName(string p_movieName, int p_year)
{ 
  // Initializing the movie name and the year
  movieName = p_movieName;
  year = p_year;
}

// Getting the name of the movie
string MovieName::getName() const
{
  return movieName;
}

// Getting the year of the movie
int MovieName::getYear() const
{
  return year;
}

// Another method to get the name of the movie
void MovieName::getName(string& g_movieName) const
{
  g_movieName = movieName;
}

// Another method for getting the year of the movie
void MovieName::getYear(int& g_year) const
{
  g_year = year;
}

// Used to calculate the weight of the movie
int MovieName::getWeight() const
{
  int theWeight = 0;
  theWeight = 1 + (2015 - year);
  return theWeight;
}

// The destructor to get rid of the movie name instances
MovieName::~MovieName()
{
}
