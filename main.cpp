#include <iostream>
#include "Point.h"
#include "Centroid.h"
#include "ClusterCoordinator.h"
#include <memory>
#include <vector>
#include <Poco/Util/XMLConfiguration.h>

using Poco::AutoPtr;
using Poco::Util::XMLConfiguration;

// TODO: Use this implemenation of K means clustering to write an image
// compression program (will need to add a 3rd dimension for RGB values)

int main()
{
    AutoPtr<XMLConfiguration> config(new XMLConfiguration("kmeanscluster.xml"));

    ClusterCoordinator clusterCoord(config);
    clusterCoord.initialize();
    clusterCoord.run();
    clusterCoord.printClusterInformation();
    
    return 0;
}