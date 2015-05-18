#ifndef _IMAGE
#define _IMAGE

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"

class Image {
public:
	Image();

	//Initializes raster to defaul Rgb color
	Image(int width, int height);
	//Initializes raster to the Rgb background
	Image(int width, int height, Rgb background);

	//Return false if x or y are out of bounds, else true
	bool set(int x, int y, const Rgb& color);
	void GammaCorrect(float gamma);

	//Outputs PPM image to 'out'
	void writePPM6(std::ostream& out);
	void writePPM3(std::ostream& out);

	void readPPM(std::string file_name);

	Rgb& get(int i, int j);

private:
	int m_x;
	int m_y;

	//Two Dimensional Array to store all image pixels
	Rgb** raster; 
};

#endif
