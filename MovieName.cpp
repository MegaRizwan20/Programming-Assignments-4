/*
 * FileName: MovieName.cpp
 *
 * Authors:
 * Date:
 * CSE Login:
 * Email:
 * PID:
 */

#include "MovieName.h"
#include <string>

using namespace std;

MovieName::MovieName(string p_movieName, int p_year)
{
  //p_movieName = movieName;
  //p_year = year;

  movieName = p_movieName;
  year = p_year;
}

void MovieName::getName(string& g_movieName) const
{
  g_movieName = movieName;
}

void MovieName::getYear(int& g_year) const
{
  g_year = year;
}

int MovieName::getWeight() const
{
  int theWeight = 0;
  theWeight = 1 + (2015 - year);
  return theWeight;
}

MovieName::~MovieName()
{
}
