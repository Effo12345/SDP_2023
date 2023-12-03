#pragma once

#include <cmath>
#include <iostream>

/**
 * @author Ethan Rosati
 *
 * Stores 2D Cartesian point data. Overloads a number of operators to allow for
 * vector arithmetic of point objects.
 **/
struct Point {
    // Set to 0 by default
    float x {};
    float y {};

    Point() {}
    
    /**
     * @author Ethan Rosati
     * 
     * Construct a new Point object
     * 
     * @param xInit x-coordinate
     * @param yInit y-coordinate
     **/
    Point(int xInit, float yInit)
    : x(xInit), y(yInit) {}

    //
    // Math operators
    // @author Ethan Rosati
    // 

    // point1 + point2 = (point1.x + point2.x, point1.y + poin2.y)
    Point operator+(const Point& p) {
        return {x + p.x, y + p.y};
    }

    // point + float = (point.x + float, point.y + float)
    Point operator+ (const float add) {
        return {x + add, y + add};
    }

    // point1 - point2 = (point1.y - point2.x, point1.y - poin2.y)
    Point operator-(const Point& p) {
        return {x - p.x, y - p.y};
    }

    // point - float = (point.x - float, point.y - float)
    Point operator-(const float subtract) {
        return {x - subtract, y - subtract};
    }

    // point1 * point2 = (point1.x * point2.x, point1.y * poin2.y)
    Point operator*(const Point& p) {
        return {x * p.x, y * p.y};
    }

    // point * float = (point.x * float, point.y * float)
    Point operator*(const float mult) {
        return {x * mult, y * mult};
    }

    // point1 / point2 = (point1.x / point2.x, point1.y / poin2.y)
    Point operator/(const Point& p) {
        return {x / p.x, y / p.y};
    }

    // point / float = (point.x / float, point.y / float)
    Point operator/(const float div) {
        return {x / div, y / div};
    }

    // point1 + point2 = (point1.x + point2.x, point1.y + poin2.y)
    // Saves to this instance of Point class
    Point operator+=(const Point& p) {
        x += p.x;
        y += p.y;
    }

    // point1 - point2 = (point1.y - point2.x, point1.y - poin2.y)
    // Saves to this instance of Point class
    Point operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
    }

    //
    // Mathematical quantity functions
    // @author Ethan Rosati
    //

    // Returns size of vector using pythagorean theorem
    float size() {
        return sqrt((x * x) + (y * y));
    }

    // Returns absolute value of x- and y-coordinates
    Point abs() {
        return {fabs(x), fabs(y)};
    }

    // Swaps x- and y-values
    void transpose() {
        float tmp = y;
        y = x;
        x = tmp;
    }

    // Proportionally clamp x- and y-components to be on [0, 1]
    // Operates on this instance of Point class
    void normalize() {
        float len = size();

        x /= len;
        y /= len;
    }

    //
    // Comparison operators
    // @author Ethan Rosati
    //

    // Are both the x- and y-values of this instance less than that of the 
    // parameter? Returns bool yes/no
    bool operator<(const Point& p) {
        return x < p.x && y < p.y ? true : false;
    }

    // Are both the x- and y-values of this instance less than the scalar 
    // parameter? Returns bool yes/no
    bool operator<(const float comp) {
        return x < comp && y < comp ? true : false;
    }

    // Are both the x- and y-values of this instance greater than that of the 
    // parameter? Returns bool yes/no
    bool operator>(const Point& p) {
        return x > p.x && y > p.y ? true : false;
    }

    // Are both the x- and y-values of this instance greater than the scalar 
    // parameter? Returns bool yes/no
    bool operator>(const float comp) {
        return x > comp && y > comp ? true : false;
    }

    // Are both the x- and y-values of this instance equal to that of the 
    // parameter? Returns bool yes/no
    bool operator==(const Point& p) {
        return x == p.x && y == p.y ? true : false;
    }

    // Are both the x- and y-values of this instance equal to the scalar 
    // parameter? Returns bool yes/no
    bool operator==(const float comp) {
        return x == comp && y == comp ? true : false;
    }
};