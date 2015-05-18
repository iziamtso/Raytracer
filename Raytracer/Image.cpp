#include "image.h"

using namespace std;

Image::Image() {}

Image::Image(int width, int height) {
	m_x = width;
	m_y = height;

	//Allocate memory for raster
	raster = new Rgb*[m_x];

	for(int i = 0; i < m_x; ++i) {
		raster[i] = new Rgb[m_y];
	}
}

Image::Image(int width, int height, Rgb background) {
	m_x = width;
	m_y = height;

	//Allocate memory for raster
	raster = new Rgb*[m_x];
	for(int i = 0; i < m_x; ++i) {
		raster[i] = new Rgb[m_y];
		for(int j = 0; j < m_y; ++j) {
			raster[i][j] = background;
		}
	}
}

//This function set the color of the cell
bool Image::set(int x, int y, const Rgb& color) {

	if(0 > x || x > m_x) { return false; }
	if(0 > y || y > m_y) { return false; }

	raster[x][y] = color;
	return true;
}

//Mutliply All Rgb values on gamma to correct the color
void Image::GammaCorrect(float gamma) {
	Rgb temp;
	float power = 1.0 / gamma;

	for(int i = 0; i < m_x; ++i ) {
		for(int j = 0; j < m_y; ++j) {
			temp = raster[i][j];
			raster[i][j] = Rgb(pow(temp.r(), power) , pow(temp.g(), power), pow(temp.b(), power));
		}
	}
}

void Image::writePPM6(std::ostream& out) {
	unsigned int int_red, int_green, int_blue;
	unsigned char red, green, blue;

	//Output header
	out << "P6\n";
	out << m_x << ' ' << m_y << '\n';
	out << "255 ";

	//Output clamped to [0, 255] values

	for(int i = m_y - 1; i >= 0 ; --i ) {//I think this makes the image be loaded from top to bottom
		for(int j = 0; j < m_x ; ++j) {
			int_red = (unsigned int) (256 * raster[j][i].r());
			int_green = (unsigned int) (256 * raster[j][i].g());
			int_blue = (unsigned int) (256 * raster[j][i].b());


			if(int_red > 255) { int_red = 255; }
			if(int_green > 255) { int_green = 255; }
			if(int_blue > 255) { int_blue = 255; }

			//convert to char
			red = (unsigned char) (int_red);
			green = (unsigned char) (int_green);
			blue = (unsigned char) (int_blue);


			out.put(red);
			out.put(green);
			out.put(blue);
		}
	}
}

void Image::writePPM3(std::ostream& out) {
	unsigned int int_red, int_green, int_blue;
	

	//Output header
	out << "P3\n";
	out << m_x << ' ' << m_y << '\n';
	out << "255\n";


	//Output clamped to [0, 255] values

	for(int i = m_y - 1; i >= 0 ; --i ) {//I think this makes the image be loaded from top to bottom
		for(int j = 0; j < m_x ; ++j) {
			int_red = (unsigned int) (256 * raster[j][i].r());
			int_green = (unsigned int) (256 * raster[j][i].g());
			int_blue = (unsigned int) (256 * raster[j][i].b());


			if(int_red > 255) { int_red = 255; }
			if(int_green > 255) { int_green = 255; }
			if(int_blue > 255) { int_blue = 255; }

			//cin.put(ch) writes a single character to the stream.

			out<<int_red<<" ";
			out<<int_green<<" ";
			out<<int_blue<<endl;

		}
	}
}
void Image::readPPM(string file_name) {
	//Open stream file
	ifstream in;
	in.open(file_name.c_str());

	if(!in.is_open()) {
		cerr<< " ERROR  -- Could not open file \'" << file_name << "\'.\n";
		exit(-1);
	}

	char ch, type;
	char red, green, blue;
	int cols, rows;
	int num;

	//read in header info
	//NOTE

	//cin.get(name, 30) means it will read 30 characters or until it hits the NEWLINE character
	//so if I call another cin.get(name, 30) it will not record anything because NEWLINE character still
	//there. Use cin.get() to get over the NEWLINE.
	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	m_x = cols;
	m_y = rows;

	//Allocate raster
	raster = new Rgb*[m_x];
	for(int i = 0 ; i < m_x ; ++i ) {
		raster[i] = new Rgb[m_y];
	}

	//clean up newline
	in.get(ch);

	//Store PPM pixel values in raster
	for(int i = m_y - 1; i >= 0; i--) {
		for(int j = 0; j < m_x; ++j) {

			//Note 
			//Below is the method the read the Ascii content
			/*int val;

			in >> val;
			red = static_cast<unsigned char>(val);
			in >> val;
			green = static_cast<unsigned char>(val);
			in >> val;
			blue = static_cast<unsigned char>(val);
			*/
			//END



			//NOTE
			//This method is to read binary data
			in.get(red);
			in.get(green);
			in.get(blue);

			raster[j][i] = Rgb((float) ((unsigned char) red) / 255.0, 
							   (float) ((unsigned char) green) / 255.0, 
							   (float) ((unsigned char) blue) / 255.0);
		}
	}
}

Rgb& Image::get(int i, int j) {
	return raster[i][j];
}


