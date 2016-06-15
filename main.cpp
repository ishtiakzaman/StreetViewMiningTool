#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
#include <CImg.h>
#include <assert.h>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 0 || argc > 5)
    {
        cerr << "usage: " << argv[0] << " image_file seeds_file [optional:beta(default:25.0)]" << endl;
        return 1;
    }

    string input_filename1 = argv[1], input_filename2 = argv[2];

    // read in images and gt
    CImg<double> image("https://maps.googleapis.com/maps/api/streetview?size=400x400&location=40.720032,-73.988354&fov=90&heading=235&pitch=10&key=AIzaSyBTQmmD0KLx8bMU3PFaUosUMcLq9mZDaKo");
    image.save("sv.jpg");

    return 0;
}
