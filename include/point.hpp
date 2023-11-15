#pragma once

#include <cmath>

/*
 * @author Ethan Rosati
 *
 * Stores 2D point data
 */
struct Point {
    int x {};
    int y {};

    Point() {}
    
    Point(int xInit, int yInit)
    : x(xInit), y(yInit) {}

    // Math operators
    Point operator+(const Point& p) {
        return {x + p.x, y + p.y};
    }

    Point operator+ (const int add) {
        return {x + add, y + add};
    }

    Point operator-(const Point& p) {
        return {x - p.x, y - p.y};
    }

    Point operator-(const int subtract) {
        return {x - subtract, y - subtract};
    }

    Point operator*(const Point& p) {
        return {x * p.x, y * p.y};
    }

    Point operator*(const int mult) {
        return {x * mult, y * mult};
    }

    Point operator/(const Point& p) {
        return {x / p.x, y / p.y};
    }

    Point operator/(const int div) {
        return {x / div, y / div};
    }

    // Mathematical quantity operators
    float size() {
        return sqrt((x * x) + (y * y));
    }

    Point absVal() {
        return {abs(x), abs(y)};
    }

    void transpose() {
        int tmp = x;
        y = x;
        x = tmp;
    }


    // Comparison operators
    bool operator<(const Point& p) {
        return x < p.x && y < p.y ? true : false;
    }

    bool operator<(const int comp) {
        return x < comp && y < comp ? true : false;
    }

    bool operator>(const Point& p) {
        return x > p.x && y > p.y ? true : false;
    }

    bool operator>(const int comp) {
        return x > comp && y > comp ? true : false;
    }

    bool operator==(const int comp) {
        return x == comp && y == comp ? true : false;
    }

    bool operator==(const Point& p) {
        return x == p.x && y == p.y ? true : false;
    }
};