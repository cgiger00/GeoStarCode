//#include "Raster.hpp"
#include "RasterClassifier.h"
#include "Slice.hpp"
#include "RasterFunction.hpp"
#include <cmath>
#include <tgmath.h>
#include <vector>
#include <iostream>
#include "Raster_classifier.hpp"
#define PI           3.14159265358979323846  /* pi */


namespace GeoStar {
    
    /** get gaussianPDF.
     The gaussianPDF is calculated with the formula
     \f$\ f(x) = \dfrac{1}{\sqrt{2 \pi \sigma}} e^{- \dfrac{(x - \my)^2}{2 \sigma ^2}} \f$
     @param x - pixel
     @return gaussianPDF
     */
    double getGaussianPDFHelper(double x, std::pair<Gaussian, int> guassianPair) {
        Gaussian gaussian = guassianPair.first;
        double mean = gaussian.getMean();
        double stdev = gaussian.getStdev();
        return (1 / (sqrt(2 * PI * pow(stdev, 2.0)))) *
        (exp( -pow(x - mean, 2.0) / ( 2 * pow(stdev, 2.0))));
    }
    
    std::pair<double, int> getGaussianPDF(double x, std::pair<Gaussian, int> gaussianPair) {
        std::pair<double, int> gaussianPDFPair {getGaussianPDFHelper(x, gaussianPair),
                                                                        gaussianPair.second };
        return gaussianPDFPair;
    }
    
    
    /** classifes rasters based off of highest gaussianPDFs
     */
    void classifyRaster(std::vector<Raster *> input, std::vector<int> /*place holder data type*/ guassianVal, std::vector<Gaussian> gaussians, Raster *output) {
        
        std::map<Gaussian, int> gaussiansMap;
        createMap(gaussians, gaussianVal, gaussiansMap);
        //assuming this will be a loop later
        long int nx = input[0]->get_nx();
        long int ny = input[0]->get_ny();
        
        Slice slice(0,0,nx,1);
        
        std::vector<uint8_t> data(nx); //this type was in the example
        
        for(int line = 0; line < ny; ++line) {
            slice.setY0(line);
            input[0]->read(slice, data);
            
            for(int pixel = 0; pixel < nx; ++pixel) {
                std::pair<double, int> gaussianPDF_max = {-1.0,-1}; //should not ever be this
                
                for (int i = 0; i < static_cast<int>(gaussiansMap.size()); ++i) { //tedious..
                    if (getGaussianPDF(data[pixel], gaussiansMap[i]).first > gaussianPDF_max.first) {
                        gaussianPDF_max = getGaussianPDF(data[pixel], gaussiansMap[i]);
                    }
                }
                if (gaussianPDF_max.first == -1.0) {std::cout << "max Gaussian PDF error " << std::endl;}
                data[pixel] = gaussianPDF_max.second;
            }
            output->write(slice, data);
        }
    }
}//end namespace geostar














