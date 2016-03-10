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

	grad1f operator()(gvec1f n) const;
};

struct noise2hdl
{
	noise2hdl();
	noise2hdl(int s);
	~noise2hdl();

	int seed;
	float data[noise_size*3]; // permutations and gradients

	void initialize(int s);

	grad2f operator()(gvec2f n) const;
};

struct noise3hdl
{
	noise3hdl();
	noise3hdl(int s);
	~noise3hdl();

	int seed;
	float data[noise_size*4]; // permutations and gradients

	void initialize(int s);

	grad3f operator()(gvec3f n) const;
};

/*
 * Procedural fBm evaluated at "point"; returns value stored in "value".
 *
 * Copyright 1994 F. Kenton Musgrave
 *
 * Parameters:
 *    ``H''  is the fractal increment parameter
 *    ``lacunarity''  is the gap between successive frequencies
 *    ``octaves''  is the number of frequencies in the fBm
 */
grad3f fBm(gvec3f point, float H, float lacunarity, float octaves, const noise3hdl &noise = noise3hdl(0));

/*
 * Procedural multifractal evaluated at "point";
 * returns value stored in "value".
 *
 * Copyright 1994 F. Kenton Musgrave
 *
 * Parameters:
 *    ``H''  determines the highest fractal dimension
 *    ``lacunarity''  is gap between successive frequencies
 *    ``octaves''  is the number of frequencies in the fBm
 *    ``offset''  is the zero offset, which determines multifractality
 */
grad3f multifractal(gvec3f point, float H, float lacunarity, float octaves, float offset, const noise3hdl &noise = noise3hdl(0));

/* Ridged multifractal terrain model.
 *
 * Copyright 1994 F. Kenton Musgrave
 *
 * Some good parameter values to start with:
 *
 *      H:           1.0
 *      offset:      1.0
 *      gain:        2.0
 */
grad3f ridge_noise(gvec3f point, float H, float lacunarity, float octaves, float offset, float gain, const noise3hdl &noise = noise3hdl(0));

}

#endif
