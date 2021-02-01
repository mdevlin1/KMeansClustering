#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include "Point3D.h"

namespace ImageProcessor {

    static std::vector<Point3DPtr> convertImageToPoints( cv::Mat img ) 
    {
        std::vector<Point3DPtr> imagePoints; 

        cv::MatIterator_ <cv::Vec3b> it, end;
        for (it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; ++it) {
            uchar &r = (*it)[2];
            uchar &g = (*it)[1];
            uchar &b = (*it)[0];

            Point3DPtr imgPointRGB = std::make_shared<Point3D>( (int)r, (int)g, (int)b );
            imagePoints.push_back(imgPointRGB);
        }
        return imagePoints;
   }

    static cv::Mat convertPointsToImage( std::vector<CentroidPtr> centroids, std::vector<Point3DPtr> points, cv::Mat img )
    {
        // This loops changes all of the RGB values of the points contained in each cluster to be same
        // as the cluster RGB value
        for (std::vector<CentroidPtr>::iterator cent_iter = centroids.begin(); cent_iter != centroids.end(); ++cent_iter)
        {
            std::vector<Point3DPtr> clusterPoints = (*cent_iter)->getCentroidPoints();
            for (std::vector<Point3DPtr>::iterator point_iter = clusterPoints.begin(); point_iter != clusterPoints.end(); ++point_iter)
            {
                (*point_iter)->setXPos((*cent_iter)->getXPos());
                (*point_iter)->setYPos((*cent_iter)->getYPos());
                (*point_iter)->setZPos((*cent_iter)->getZPos());
            }
        }

        cv::MatIterator_ <cv::Vec3b> it, end;
        unsigned int pointCount = 0;
        for (it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; ++it) {
            (*it)[2] = (uchar)points[pointCount]->getXPos();
            (*it)[1] = (uchar)points[pointCount]->getYPos();
            (*it)[0] = (uchar)points[pointCount]->getZPos();
            pointCount++;
        }
        
        return img;
    }
   
}