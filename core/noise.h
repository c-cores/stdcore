#include "vector.h"
#include "geometry.h"
#include "gradient.h"

#ifndef noise_h
#define noise_h

namespace core
{

#define noise_size 64
#define noise_mask 63

struct noise1hdl
{
	noise1hdl();
	noise1hdl(int s);
	~noise1hdl();

	int seed;
	float data[noise_size*2]; // permutations and gradients

	void initialize(int s);

	grad1f operator()(vec1f n, float r, float m);
};

struct noise2hdl
{
	noise2hdl();
	noise2hdl(int s);
	~noise2hdl();

	int seed;
	float data[noise_size*3]; // permutations and gradients

	void initialize(int s);

	grad2f operator()(vec2f n, float r, float m);
};

struct noise3hdl
{
	noise3hdl();
	noise3hdl(int s);
	~noise3hdl();

	int seed;
	float data[noise_size*4]; // permutations and gradients

	void initialize(int s);

	grad3f operator()(vec3f n, float r, float m);
};

}

#endif
