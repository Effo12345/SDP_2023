#pragma once

#include <cmath>

/*
 * @author Ethan Rosati
 *
 * Stores 2D point data
 */
struct Point {
    float x {};
    float y {};

    Point() {}
    
    Point(int xInit, float yInit)
    : x(xInit), y(yInit) {}

    // Math operators
    Point operator+(const Point& p) {
        return {x + p.x, y + p.y};
    }

    Point operator+ (const float add) {
        return {x + add, y + add};
    }

    Point operator-(const Point& p) {
        return {x - p.x, y - p.y};
    }

    Point operator-(const float subtract) {
        return {x - subtract, y - subtract};
    }

    Point operator*(const Point& p) {
        return {x * p.x, y * p.y};
    }

    Point operator*(const float mult) {
        return {x * mult, y * mult};
    }

    Point operator/(const Point& p) {
        return {x / p.x, y / p.y};
    }

    Point operator/(const float div) {
        return {x / div, y / div};
    }

    // Mathematical quantity operators
    float size() {
        return sqrt((x * x) + (y * y));
    }

    Point absVal() {
        return {std::abs(x), std::abs(y)};
    }

    void transpose() {
        float tmp = x;
        y = x;
        x = tmp;
    }

    void normalize() {
        float len = getLength();

        x /= len;
        y /= len;
    }

    float getLength() {
        return sqrt((x * x) + (y * y));
    }


    // Comparison operators
    bool operator<(const Point& p) {
        return x < p.x && y < p.y ? true : false;
    }

    bool operator<(const float comp) {
        return x < comp && y < comp ? true : false;
    }

    bool operator>(const Point& p) {
        return x > p.x && y > p.y ? true : false;
    }

    bool operator>(const float comp) {
        return x > comp && y > comp ? true : false;
    }

    bool operator==(const float comp) {
        return x == comp && y == comp ? true : false;
    }

    bool operator==(const Point& p) {
        return x == p.x && y == p.y ? true : false;
    }
};