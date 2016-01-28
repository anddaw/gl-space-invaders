#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle {

  //współrzędne lewego dolnego rogu
  double startX;
  double startY;

  //wysokość
  double width;
  //długość
  double height;

public:
  Rectangle(double x, double y, double w, double h) : startX(x), startY(y), width(w), height(h) {}

  /*Czy punkt znajduje się w środku*/
  bool isInside(double pointX, double pointY);

  /*Czy dwa prostokąty nakładają się na siebie*/
  bool overlaps(Rectangle);

  void shift(double x, double y) {
    startX += x;
    startY += y;
  }
    
};

#endif
