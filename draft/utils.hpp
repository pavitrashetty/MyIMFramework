#ifndef __UTILS__
#define __UTILS__

#include "base.hpp"

/* UTIL CLASS:
    Implements classes for
    1. Defining geometry - give cordinates in string, get back cordinates as Geometry object
    2. Defining rate and duration of video playback
    3. Defining geometry - give size in string, get back size as Geometry object
*/


// VVIMP TODO: all int to size_t
    
class Position {
  int x;
  int y;
  char xy_position[10];

  public:

    Position ();
    Position(int x, int y);
    Position(char *xy_position);
    int get_x();
    int get_y();
    Geometry *get_postion();
    void set_position(int x, int y);
};


class Resolution {
  int w;
  int h;
  char dimensions[10];

  public:
    Resolution();
    Resolution(int w, int h);
    Resolution(char *dimen);
    int get_w();
    int get_h();
    Geometry *get_resolution();
};


#endif