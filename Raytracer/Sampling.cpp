//#include "stdafx.h"
#include "Sampling.h"
#include "vector3.h"
#include <cstdlib>
#include <cmath>

using namespace std;

void random(Vector3* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		//double-precision, floating-point values, 
		//uniformly distributed over the interval [0.0 , 1.0].
		samples[i].SetX((double)rand()/RAND_MAX); //drand48() used to be here
		samples[i].SetY( (double)rand()/RAND_MAX); // drand48() used to be here
	}
}

//Assume num_samples is a perfect square
void jitter(Vector3* samples, int num_samples) {
	int sqrt_samples = (int)(sqrt(num_samples));

	for(int i = 0; i < sqrt_samples; i++) {
		for(int j = 0; j < sqrt_samples; j++){
			float x = ((double)i + (double)rand()/RAND_MAX) / (double)sqrt_samples;
			float y = ((double)j + (double)rand()/RAND_MAX) / (double)sqrt_samples;
			(samples[i * sqrt_samples + j]).SetX(x);
			(samples[i * sqrt_samples + j]).SetY(y);
		}
	}
}

void nrooks(Vector3* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		samples[i].SetX( ((double)i + (double)rand()/RAND_MAX) / (double)num_samples);
		samples[i].SetY( ((double)i + (double)rand()/RAND_MAX) / (double)num_samples);
	}

	//shuffle x coordinates
	for(int i = num_samples - 2; i >= 0; i--) {
		int target = int((double)rand()/RAND_MAX * (double)i);
		float tempXstg = samples[i+1].x();
		samples[i+1].SetX(samples[target].x());
		samples[i].SetX(tempXstg);
	}

}

//assume num_samples is a perfect square
void multiJitter(Vector3* samples, int num_samples) {
	int sqrt_samples = (int)sqrt(num_samples);
	float subcell_width = 1.0f /(float(num_samples));

	//This for loop create chess board with rooks standing on a diagonal
	//initialize points to the "canonical" multi-jittered pattern
	for(int i = 0; i < sqrt_samples; i++) {
		for(int j = 0; j < sqrt_samples; j++) {
			//x value
			samples[i * sqrt_samples + j].e[0] =
				i*sqrt_samples*subcell_width + j*subcell_width +
				((double)rand()/RAND_MAX) * subcell_width;
			//y value
			samples[i * sqrt_samples + j].e[1] =
				i*sqrt_samples*subcell_width + j*subcell_width +
				((double)rand()/RAND_MAX) * subcell_width;
		}
	}

	//shuffle x coordinates and y coordinates
	for(int i = 0; i< sqrt_samples; i++) {
		for(int j = 0; j < sqrt_samples; j++) {
			int k = j + int(((double)rand()/RAND_MAX) * (sqrt_samples - j - 1));
			float t = samples[i*sqrt_samples + j].e[0];
			samples[i*sqrt_samples + j].e[0] = samples[i * sqrt_samples + k].e[0];
			samples[i*sqrt_samples + k].e[0] = t; 


			k = j + int(((double)rand()/RAND_MAX) * (sqrt_samples - j - 1));
			t = samples[j*sqrt_samples + i].e[1];
			samples[j*sqrt_samples + i].e[1] = samples[k * sqrt_samples + i].e[1];
			samples[k*sqrt_samples + i].e[1] = t; 
		}
	}
}

void shuffle(Vector3* samples, int num_samples) {
	for(int i = num_samples - 2; i >= 0; i--) {
		int target = int((double)rand()/RAND_MAX * (double)i);
		Vector3 temp = samples[i+1];
		samples[i+1] = samples[target];
		samples[target] = temp;
	}

}

//-------------------------------------------------------------------------------------
//Filters
//-------------------------------------------------------------------------------------
void boxFilter(Vector3* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		samples[i].SetX(samples[i].x() - 0.5f);
		samples[i].SetY(samples[i].y() - 0.5f);
	}
}

void tentFilter(Vector3* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		float x = samples[i].x();
		float y = samples[i].y();

		//X
		if(x < 0.5f) {
			samples[i].SetX((float) sqrt(2.0f * (double)x) - 1.0f);
		}
		else {
			samples[i].SetX(1.0f - (float)sqrt(2.0 - 2.0 * (double)x));
		}


		//Y
		if(y < 0.5f) {
			samples[i].SetY((float) sqrt(2.0f * (double)y) - 1.0f);
		}
		else {
			samples[i].SetY(1.0f - (float)sqrt(2.0 - 2.0 * (double)y));
		}

	}
}

void cubicSplineFilter(Vector3* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		float x = samples[i].x();
		float y = samples[i].y();

		samples[i].e[0] = cubicFilter(x);
		samples[i].e[1] = cubicFilter(y);
	}
}


///1D
void random(float* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		samples[i] = float((double)rand()/RAND_MAX);
	}
}

void jitter(float* samples, int num_samples) {
	for(int i = 0; i < num_samples; i++) {
		samples[i] = float(((double)i + (double)rand()/RAND_MAX) / (double)num_samples);
	}
}

void shuffle(float* samples, int num_samples) {
	for(int i = num_samples -2; i >= 0; i--) {
		int target = int((double)rand()/RAND_MAX * (double)i);
		float temp = samples[i+1];
		samples[i+1] = samples[target];
		samples[target] = temp;
	}
}



Rgb averageColor(Rgb* array, int num_samples) {
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;

	for(int i = 0; i < num_samples; i++) {
		red += array[i].r();
		green += array[i].g();
		blue += array[i].b();
	}
	return Rgb(red/num_samples, green/num_samples, blue/num_samples);
}

