// Raytracer.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include <cstdio>
#include <Windows.h>

#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Sampling.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	HitRecord record;
	bool is_a_hit;
	float tmax;
	Vector3 d(0, 0, -1);

	int width = 500;
	int height = 500;

	ofstream myfile;
	myfile.open ("image.ppm");
	
	//Point for my triangles
	Vector3 p0(300, 600, -800);
	Vector3 p1(0, 100, -1000);
	Vector3 p2(450, 20, -1000);

	Rgb blue(0.2f, 0.2f, 0.8f);
	Rgb green(0.8f, 0.2f, 0.2f);


	//Geometry
	Sphere *sphere = new Sphere(Vector3(250.0f, 250.0f, -1000.0f), 150, blue);
	Triangle *tri = new Triangle(p0, p1, p2, green);

	vector<Shape*> shapes;
	shapes.push_back(sphere);
	shapes.push_back(tri);

	//Create image
	Image image(width, height);
	int sampleSize = 9;
	Vector3 v[9];
	Rgb c[9];
	//random(v, sampleSize);
	//jitter(v, sampleSize);
	//nrooks(v, sampleSize);
	multiJitter(v, sampleSize);
	tentFilter(v, sampleSize);

	//Create Filtering test pattern
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++){
			for(int k = 0; k < sampleSize; k++) {
				double sx = i + v[k].x();
				double sy = j + v[k].y();
				c[k] = Rgb(0.5 * (1.088 + sin((sx*sx + sy*sy) * 0.01)));
			}
			image.set(i, j, averageColor(c, sampleSize));
		}
	}

	////Loop the pixels
	//for(int i = 0; i < width; i++) {
	//	for(int j = 0; j < height; j++) {
	//		tmax = 1000000.0f;
	//		is_a_hit = false;
	//		//Ray(origin, direction)
	//		Ray r(Vector3(i, j, 0), d);

	//		//Loop the shapes
	//		for(int k = 0; k < shapes.size(); k++) {
	//			if(shapes[k]->hit(r, 0.00001f, tmax, 1.0, record)) {
	//				tmax = record.t;
	//				is_a_hit = true;
	//			}
	//		}
	//		if(is_a_hit) {
	//			image.set(i, j, record.color);
	//			

	//			
	//		}
	//		else{
	//			image.set(i, j, Rgb(0.2f, 0.2f, 0.2f));
	//		}
	//	}
	//}
	
	image.writePPM6(myfile);
	myfile.close();
	return 0;
}



