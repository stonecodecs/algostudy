#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include "point.h"

std::vector<Point> sortPoints(std::vector<Point> set, bool byX=true);
int d2(Point x, Point y); // distance squared
// std::tuple<Point, Point> closestPair(std::vector<Point> set);
// std::tuple<Point, Point> closestPair(std::vector<Point> s1, std::vector<Point> s2);
// std::tuple<Point, Point> closestPairSplit(std::vector<Point> a, std::vector<Point> b, float distance);