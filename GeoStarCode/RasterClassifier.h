//
//  GaussianPDF.h
//  GeoStarCode
//
//  Created by Carmen Giger on 2/26/19.
//
//#include "Raster.hpp"
#include "Raster.h"
#include "Slice.hpp"
#include "RasterFunction.hpp"
#include <cmath>
#include <tgmath.h>
#include <vector>
#include <iostream>

#ifndef Gaussian_h
#define Gaussian_h

namespace GeoStar {
    
    class Gaussian {
    private:
        double mean; /** <mean  */
        double stdev; /** <stdev */
    public:
        /** Default constructor sets mean and stdev to 0
         */
        Gaussian(): mean(0), stdev(0) {}
        /** Custom constructor, initalizes mean and stdev
         */
        Gaussian(double mean, double stdev) : mean(mean), stdev(stdev) {}
        /** returns mean
         */
        double getMean() {return mean;}
        /** returns stdev
         */
        double getStdev() {return stdev;}
    };
    
    
#endif /* Gaussian_h */
    
    std::pair<double, int> getGaussianPDF(double x, std::pair<Gaussian, int> guassianPair);
    
    void classifyRaster(std::vector<Raster *> input,
                        std::vector<int> /*place holder data type*/ guassianVal
                        std::vector<Gaussian> gaussians, Raster *output);
    
    
    void createMap(vector<Gaussian> guassians, vector<int /**/> values, map<Gaussian, int> &newMap) {
        std::transform(gaussians.begin(), gaussians.end(), values.begin(),
                    std::inserter(newMap, newMap.end()), std::make_pair<Gaussian, int>);
    
        double getGaussianPDFHelper(double x, std::pair<Gaussian, int> guassianPair);

    } //helper function 





















