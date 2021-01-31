#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Point3D.h"
#include "Centroid.h"

static std::vector<Point3DPtr> parseFile(std::string filename)
{
    std::ifstream csvFile(filename);
    std::string delimiter = ",";
    std::vector<Point3DPtr> points;
    for (std::string line; getline(csvFile, line);)
    {
        std::istringstream iss(line);
        std::vector<std::string> coords((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());
        Point3DPtr p = std::make_shared<Point3D>( std::stoi(coords[0]), std::stoi(coords[1]), std::stoi(coords[2]) );
        points.push_back(p);
    }
    return points;
}