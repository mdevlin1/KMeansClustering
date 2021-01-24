#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Point3D.h"

typedef std::shared_ptr<Centroid> CentroidPtr;

static std::vector<Point3D> parseFile(std::string filename)
{
    std::ifstream csvFile(filename);
    std::string delimiter = ",";
    std::vector<Point3D> points;
    for (std::string line; getline(csvFile, line);)
    {
        std::istringstream iss(line);
        std::vector<std::string> coords((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());
        Point3D p( std::stoi(coords[0]), std::stoi(coords[1]), std::stoi(coords[2]) );
        points.push_back(p);
    }
    return points;
}