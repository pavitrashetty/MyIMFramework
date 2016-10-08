#include "utils.hpp"

Position::Position ():x(0),y(0) {
  strcpy (xy_position,"0,0");
}

Position::Position(int x, int y):x(x),y(y) {
  sprintf (xy_position, "\"%d,%d\"", x,y);
  //cout<<"Position is "<<xy_position;
}

Position::Position(char *xy_position) {
  strcpy(this->xy_position, xy_position);
  // also initialize x and y
}

int Position::get_x() {
  return x;
}

int Position::get_y() {
  return y;
}

Geometry * Position::get_postion() {
  Geometry *pos = new Geometry(0,0,x,y);
  return pos;
}

void Position::set_position(int x, int y) {
  this->x=x;
  this->y=y;
}



Resolution::Resolution() {
  w=0;
  h=0;
  strcpy(dimensions, "0x0");
}

Resolution::Resolution(int w, int h):w(w),h(h) {
  sprintf (dimensions, "\"%d,%d\"", w,h);
  //cout<<"Resolution is "<<dimensions;
}

Resolution::Resolution(char *dimen) {
  strcpy(this->dimensions, dimen);
  // also initialize w and h
}

int Resolution::get_w() {
  return w;
}

int Resolution::get_h() {
  return h;
}

Geometry *Resolution::get_resolution() {
  Geometry *res = new Geometry(w,h,0,0);
  return res;
}