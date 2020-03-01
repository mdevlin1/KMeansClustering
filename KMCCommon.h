#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Point.h"

typedef std::shared_ptr<Centroid> CentroidPtr;

static std::vector<Point> parseFile(std::string filename)
{
    std::ifstream csvFile(filename);
    std::string delimiter = ",";
    std::vector<Point> points;
    for (std::string line; getline(csvFile, line);)
    {
        std::istringstream iss(line);
        std::vector<std::string> coords((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());
        Point p(std::stoi(coords[0]), std::stoi(coords[1]));
        points.push_back(p);
    }
    return points;
}