#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include "point.h"

std::vector<Point> sortPoints(std::vector<Point> set, bool byX=true);
int d2(Point const &x, Point const &y); // distance squared
std::tuple<std::vector<Point>,std::vector<Point>,std::vector<Point>,std::vector<Point>> splitInputPointVectors(std::vector<Point> &a, std::vector<Point> &b);
std::vector<Point> getPointsNearby(std::vector<Point> &set, int refPointIndex, int dist);
std::tuple<Point, Point> closestPair(std::vector<Point> &set);
std::tuple<Point, Point> closestPair(std::vector<Point> &a, std::vector<Point> &b);
std::tuple<Point, Point> closestPairSplit(std::vector<Point> &a, std::vector<Point> &b, float dist);