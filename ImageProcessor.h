#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include "Point3D.h"

namespace ImageProcessor {

    static std::vector<Point3D> convertImageToPoints( cv::Mat img ) 
    {
        std::vector<Point3D> imagePoints; 

        cv::MatIterator_ <cv::Vec3b> it, end;
        for (it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; ++it) {
            uchar &r = (*it)[2];
            uchar &g = (*it)[1];
            uchar &b = (*it)[0];

            Point3D imgPointRGB( (int)r, (int)g, (int)b );
            imagePoints.push_back(imgPointRGB);
        }
        return imagePoints;
   }

    static cv::Mat convertPointsToImage( std::vector<CentroidPtr> points, cv::Mat img )
    {
        return img;
    }
   
}