#include "noise.h"

namespace core
{

#define noise_curve(t, t2) (t2*t*(t*(t*6.0f-15.0f)+10.0f))
#define noise_curve1(t, t2) (30.0f*t2*(t * (t - 2.0f) + 1.0f))

noise1hdl::noise1hdl()
{
	seed = 0;
}

noise1hdl::noise1hdl(int s)
{
	initialize(s);
}

noise1hdl::~noise1hdl()
{
}

void noise1hdl::initialize(int s)
{
	seed = s;
	srand(seed);
	int i, j;
	float k;

	for (i = 0; i < noise_size; i++)
	{
		data[i*2 + 0] = i;

		data[i*2 + 1] = (float)((rand() % (noise_size*2)) - noise_size) / noise_size;
	}

	while (--i)
	{
		j = rand() & noise_mask;

		k = data[i*2 + 0];
		data[i*2 + 0] = data[j*2 + 0];
		data[j*2 + 0] = k;
	}
}

grad1f noise1hdl::operator()(gvec1f n) const
{
	int bx0, bx1, b0, b1;
	grad1f rx0, rx02, rx1, t;
	grad1f k0, k1;
	grad1f a, b;
	grad1f u;

	t = n[0];
    bx0 = int(t.elems[1]) & noise_mask;
    bx1 = (bx0+1) & noise_mask;
    rx0 = t - floor(t);
    rx1 = rx0 - 1.0f;
    rx02 = rx0*rx0;

	u = noise_curve(rx0, rx02);

	b0 = int(data[bx0*2 + 0]);
	b1 = int(data[bx1*2 + 0]);

	a = rx0 * data[b0*2 + 1];
	b = rx1 * data[b1*2 + 1];

	k0 = a;
	k1 = b - a;

	return k0 + k1*u;
}

noise2hdl::noise2hdl()
{
	seed = 0;
}

noise2hdl::noise2hdl(int s)
{
	initialize(s);
}

noise2hdl::~noise2hdl()
{
}

void noise2hdl::initialize(int s)
{
	seed = s;
	srand(seed);
	int i, j;
	float k;
	float length;

	for (i = 0; i < noise_size; i++)
	{
		data[i*3 + 0] = float(i);

		length = 0;
		for (j = 1; j < 3; j++)
		{
			data[i*3 + j] = (float)((rand() % (noise_size*2)) - noise_size) / noise_size;
			length += data[i*3 + j]*data[i*3 + j];
		}

		length = ::sqrt(length);

		data[i*3 + 1] /= length;
		data[i*3 + 2] /= length;
	}

	while (--i)
	{
		j = rand() & noise_mask;

		k = data[i*3 + 0];
		data[i*3 + 0] = data[j*3 + 0];
		data[j*3 + 0] = k;
	}
}

grad2f noise2hdl::operator()(gvec2f n) const
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11, i, j;
	const float *q;
	grad2f rx0, rx02, rx1, ry0, ry02, ry1, t;
	grad2f k0, k1, k2, k3;
	grad2f a, b, c, d;
	grad2f u, v;

	t = n[0];
    bx0 = int(t.elems[2]) & noise_mask;
    bx1 = (bx0+1) & noise_mask;
    rx0 = t - floor(t);
    rx1 = rx0 - 1.0f;
    rx02 = rx0*rx0;

    t = n[1];
    by0 = int(t.elems[2]) & noise_mask;
    by1 = (by0+1) & noise_mask;
    ry0 = t - floor(t);
    ry1 = ry0 - 1.0f;
    ry02 = ry0*ry0;

	u = noise_curve(rx0, rx02);
	v = noise_curve(ry0, ry02);

	i = int(data[bx0*3 + 0]);
	j = int(data[bx1*3 + 0]);

	b00 = int(data[(i + by0)*3 + 0]);
	b10 = int(data[(j + by0)*3 + 0]);
	b01 = int(data[(i + by1)*3 + 0]);
	b11 = int(data[(j + by1)*3 + 0]);

	q = &data[b00*3 + 1];
	a = rx0 * q[0] + ry0 * q[1];
	q = &data[b10*3 + 1];
	b = rx1 * q[0] + ry0 * q[1];

	q = &data[b01*3 + 1];
	c = rx0 * q[0] + ry1 * q[1];
	q = &data[b11*3 + 1];
	d = rx1 * q[0] + ry1 * q[1];

	k0 = a;
	k1 = b - a;
	k2 = c - a;
	k3 = - k1 - c + d;

	return k0 + k1*u + k2*v + k3*u*v;
}

noise3hdl::noise3hdl()
{
	seed = 0;
}

noise3hdl::noise3hdl(int s)
{
	initialize(s);
}

noise3hdl::~noise3hdl()
{
}

void noise3hdl::initialize(int s)
{
	seed = s;
	srand(seed);
	int i, j;
	float k;
	float length;

	for (i = 0; i < noise_size; i++)
	{
		data[i*4 + 0] = float(i);

		length = 0;
		for (j = 1; j < 4; j++)
		{
			data[i*4 + j] = (float)((rand() % (noise_size*2)) - noise_size) / noise_size;
			length += data[i*4 + j]*data[i*4 + j];
		}

		length = ::sqrt(length);

		data[i*4 + 1] /= length;
		data[i*4 + 2] /= length;
		data[i*4 + 3] /= length;
	}

	while (--i)
	{
		j = rand() & noise_mask;

		k = data[i*4 + 0];
		data[i*4 + 0] = data[j*4 + 0];
		data[j*4 + 0] = k;
	}
}

grad3f noise3hdl::operator()(gvec3f n) const
{
	grad3f ret;
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11, i, j;
	grad3f rx0, rx02, rx1, ry0, ry02, ry1, rz0, rz02, rz1, t;
	grad3f k0, k1, k2, k3, k4, k5, k6, k7;
	grad3f a, b, c, d, e, f, g, h;
	const float *q;
	grad3f u, v, w;

	t = n[0];
    bx0 = int(t.elems[3]) & noise_mask;
    bx1 = (bx0+1) & noise_mask;
    rx0 = t - floor(t);
    rx1 = rx0 - 1.0f;
    rx02 = rx0*rx0;

    t = n[1];
    by0 = int(t.elems[3]) & noise_mask;
    by1 = (by0+1) & noise_mask;
    ry0 = t - floor(t);
    ry1 = ry0 - 1.0f;
    ry02 = ry0*ry0;

    t = n[2];
    bz0 = int(t.elems[3]) & noise_mask;
    bz1 = (bz0+1) & noise_mask;
    rz0 = t - floor(t);
    rz1 = rz0 - 1.0f;
    rz02 = rz0*rz0;

	u = noise_curve(rx0, rx02);
	v = noise_curve(ry0, ry02);
	w = noise_curve(rz0, rz02);

	i = int(data[bx0*4 + 0]);
	j = int(data[bx1*4 + 0]);

	b00 = int(data[((i + by0)&noise_mask)*4 + 0]);
	b10 = int(data[((j + by0)&noise_mask)*4 + 0]);
	b01 = int(data[((i + by1)&noise_mask)*4 + 0]);
	b11 = int(data[((j + by1)&noise_mask)*4 + 0]);

	q = &data[((b00 + bz0)&noise_mask)*4 + 1];
	a = rx0*q[0] + ry0*q[1] + rz0*q[2];
	q = &data[((b10 + bz0)&noise_mask)*4 + 1];
	b = rx1*q[0] + ry0*q[1] + rz0*q[2];

	q = &data[((b01 + bz0)&noise_mask)*4 + 1];
	c = rx0*q[0] + ry1*q[1] + rz0*q[2];
	q = &data[((b11 + bz0)&noise_mask)*4 + 1];
	d = rx1*q[0] + ry1*q[1] + rz0*q[2];

	q = &data[((b00 + bz1)&noise_mask)*4 + 1];
	e = rx0*q[0] + ry0*q[1] + rz1*q[2];
	q = &data[((b10 + bz1)&noise_mask)*4 + 1];
	f = rx1*q[0] + ry0*q[1] + rz1*q[2];

	q = &data[((b01 + bz1)&noise_mask)*4 + 1];
	g = rx0*q[0] + ry1*q[1] + rz1*q[2];
	q = &data[((b11 + bz1)&noise_mask)*4 + 1];
	h = rx1*q[0] + ry1*q[1] + rz1*q[2];

	k0 = a;
	k1 = b - a;
	k2 = c - a;
	k3 = e - a;
	k4 = - k1 - c + d;
	k5 = - k2 - e + g;
	k6 = - k1 - e + f;
	k7 = - k4 + e - f - g + h;

	return k0 + k1*u + k2*v + k3*w + k4*u*v + k5*v*w + k6*w*u + k7*u*v*w;
}

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
grad3f fBm(gvec3f point, float H, float lacunarity, float octaves, const noise3hdl &noise)
{

	grad3f            value;
	float frequency, remainder;
	static bool        first = true;
	static array<float> exponent_array;

	/* precompute and store spectral weights */
	if (first)
	{
		/* seize required memory for exponent_array */
		exponent_array.resize(octaves+1);
		frequency = 1.0;
		for (int i = 0; i <= octaves; i++)
		{
			/* compute weight for each frequency */
			exponent_array[i] = ::pow( frequency, -H );
			frequency *= lacunarity;
		}
		first = false;
	}

	value = 0.0;
	frequency = 1.0;

	/* inner loop of spectral construction */
	for (int i = 0; i < octaves; i++)
	{
		value += noise(point) * exponent_array[i];
		point *= lacunarity;
	}

	remainder = octaves - (int)octaves;
	if (remainder)
		value += remainder * noise(point) * exponent_array[(int)octaves];

	return value;
}


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
grad3f multifractal(gvec3f point, float H, float lacunarity, float octaves, float offset, const noise3hdl &noise)
{
	grad3f value;
	float            frequency, remainder;
	static bool        first = true;
	static array<float> exponent_array;

	/* precompute and store spectral weights */
	if (first)
	{
		/* seize required memory for exponent_array */
		exponent_array.resize(octaves+1);
		frequency = 1.0;
		for (int i = 0; i <= octaves; i++)
		{
			/* compute weight for each frequency */
			exponent_array[i] = ::pow( frequency, -H );
			frequency *= lacunarity;
		}
		first = false;
	}

	value = 1.0;
	frequency = 1.0;

	/* inner loop of multifractal construction */
	for (int i = 0; i < octaves; i++)
	{
		value *= offset * frequency * noise(point);
		point *= lacunarity;
	}

	remainder = octaves - (int)octaves;
	if (remainder)      /* add in ``octaves''  remainder */
		value += remainder * noise(point) * exponent_array[(int)octaves];

	return value;
}

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
grad3f ridge_noise(gvec3f point, float H, float lacunarity, float octaves, float offset, float gain, const noise3hdl &noise)
{
	grad3f result, signal, weight;
	float           frequency;
	static bool       first = true;
	static array<float> exponent_array;

	/* precompute and store spectral weights */
	if (first)
	{
		/* seize required memory for exponent_array */
		exponent_array.resize(octaves+1);
		frequency = 1.0;
		for (int i = 0; i <= octaves; i++)
		{
			/* compute weight for each frequency */
			exponent_array[i] = ::pow(frequency, -H);
			frequency *= lacunarity;
		}
		first = false;
	}

	/* get first octave */
	signal = noise(point);
	/* get absolute value of signal (this creates the ridges) */
	if (signal < 0.0f)
		signal = -signal;
	/* invert and translate (note that "offset" should be ~= 1.0) */
	signal = offset - signal;
	/* square the signal, to increase "sharpness" of ridges */
	signal *= signal;
	/* assign initial values */
	result = signal;
	weight = 1.0f;

	for (int i = 1; i < octaves; i++ )
	{
		/* increase the frequency */
		point *= lacunarity;

		/* weight successive contributions by previous signal */
		weight = signal * gain;
		if (weight > 1.0f)
			weight = 1.0f;
		else if (weight < 0.0f)
			weight = 0.0f;

		signal = noise(point);
		if (signal < 0.0f)
			signal = -signal;
		signal = offset - signal;
		signal *= signal;
		/* weight the contribution */
		signal *= weight;
		result += signal * exponent_array[i];
	}

	return result;
}

}
