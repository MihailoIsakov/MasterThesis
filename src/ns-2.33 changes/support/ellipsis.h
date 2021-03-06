#ifndef ns_ellipsis_h
#define ns_ellipsis_h

#include <math.h>
#include <stdio.h>

#include "point.h"

// Ellipsis class 
class Ellipsis {
private:
  Point p1, p2;
  double major, minor;
  int hit_edge_counter;
 
  void find_minor();

public:
// Constructer
  Ellipsis(Point point1, Point point2);
 
  void change_major(double new_major);
  bool hit_edge();
  
  double get_major();
  Point get_p1();
  Point get_p2();

  bool point_in_ellipsis(double x, double y);
  
  inline Ellipsis* copy() const;
};

inline Ellipsis* Ellipsis::copy() const {
  Ellipsis *e = new Ellipsis(p1, p2);
    e->change_major(major);
    return e;
  };

#endif
