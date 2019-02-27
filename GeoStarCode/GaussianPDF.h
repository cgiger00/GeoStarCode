//
//  GaussianPDF.h
//  GeoStarCode
//
//  Created by Carmen Giger on 2/26/19.
//  Copyright © 2019 Carmen Giger. All rights reserved.
//

#include "Raster.h"
#include "Slice.h"
#include <cmath>
#include <tgmath.h>

#define PI           3.14159265358979323846  /* pi */

#ifndef Gaussian_h
#define Gaussian_h

class Gaussian {
private:
    double mean;
    double stdev;
public:
    Gaussian(): mean(0), stdev(0) {}
    Gaussian(double mean, double stdev) : mean(mean), stdev(stdev) {}
    double getMean() {return mean;}
    double getStdev() {return stdev;}
};


#endif /* Gaussian_h */

double getGaussianPDF(double x, Gaussian &gaussian) {
    double mean = gaussian.getMean();
    double stdev = gaussian.getStdev();
    return (1 / (sqrt(2 * PI * pow(stdev, 2.0)))) *
                (exp( -pow(x - mean, 2.0) / ( 2 * pow(stdev, 2.0))));
}
//a raster is a geostar object, geostar is not on my mac :(
void classifyRaster(std::vector<Raster *> input, std::vector<Gaussian> guassians, Raster *output) {
    //assuming this will be a loop later
    long int nx = input[0]->get_nx();
    long int ny = input[0]->get_ny();
    
    Slice slice(0,0,nx,1)
    
    std::vector<uint8_t> data(nx); //this type was in the example
    
    for(int line = 0; line < ny; ++line) {
        slice.setY0(line);
        input[0]->read(slice, data);
        for(int pixel = 0; pixel < nx; ++pixel) {
            double gaussianPDF_max = -1; //should not ever be this
            for (int i = 0; i < static_cast<int>(gaussians.size()); ++i) { //tedious..
                if (getGaussianPDF(data[pixel], gaussians[i]) > gaussianPDF_max) {
                    gaussianPDF_max = getGaussianPDF(data[pixel], gaussians[i]);
                }
            }
            if (gaussianPDF_max == -1) {std::cout << "max Gaussian PDF error " << std::endl;}
            data[pixel] = gaussianPDF_max;
        }
        output->write(slice, data);
    }
}




























