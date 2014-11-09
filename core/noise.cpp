#include "noise.h"

namespace core
{

#define noise_curve(t, t2) (t2*t*(t*(t*6.0f-15.0f)+10.0f))
#define noise_curve1(t, t2) (30.0f*t2*(t * (t - 2.0f) + 1.0f))

noise1hdl::noise1hdl()
{
	seed = 0;
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

grad1f noise1hdl::operator()(vec1f n, float r, float m)
{
	grad1f ret;

	int bx0, bx1, b0, b1;
	float rx0, rx02, rx1, t;
	float k0, k1;
	float a, b;
	float u, du;

	t = n[0] + r;
    bx0 = int(t) & noise_mask;
    bx1 = (bx0+1) & noise_mask;
    rx0 = t - floor(t);
    rx1 = rx0 - 1.0;
    rx02 = rx0*rx0;

	u = noise_curve(rx0, rx02);
	du = noise_curve1(rx0, rx02);

	b0 = int(data[bx0*2 + 0]);
	b1 = int(data[bx1*2 + 0]);

	a = rx0 * data[b0*2 + 1];
	b = rx1 * data[b1*2 + 1];

	k0 = a;
	k1 = b - a;

	ret[1] = k0 + k1*u;
	ret[0] = du * k1 * m;

	return ret;
}

noise2hdl::noise2hdl()
{
	seed = 0;
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

grad2f noise2hdl::operator()(vec2f n, float r, float m)
{
	grad2f ret;

	int bx0, bx1, by0, by1, b00, b10, b01, b11, i, j;
	float *q;
	float rx0, rx02, rx1, ry0, ry02, ry1, t;
	float k0, k1, k2, k3;
	float a, b, c, d;
	float u, v, du, dv;

	t = n[0] + r;
    bx0 = int(t) & noise_mask;
    bx1 = (bx0+1) & noise_mask;
    rx0 = t - floor(t);
    rx1 = rx0 - 1.0;
    rx02 = rx0*rx0;

    t = n[1] + r;
    by0 = int(t) & noise_mask;
    by1 = (by0+1) & noise_mask;
    ry0 = t - floor(t);
    ry1 = ry0 - 1.0;
    ry02 = ry0*ry0;

	u = noise_curve(rx0, rx02);
	v = noise_curve(ry0, ry02);
	du = noise_curve1(rx0, rx02);
	dv = noise_curve1(ry0, ry02);

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

	ret[2] = k0 + k1*u + k2*v + k3*u*v;
	ret[0] = du * (k1 + k3*v) * m;
	ret[1] = dv * (k2 + k3*u) * m;

	return ret;
}

noise3hdl::noise3hdl()
{
	seed = 0;
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

grad3f noise3hdl::operator()(vec3f n, float r, float m)
{
	grad3f ret;
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11, i, j;
	float rx0, rx02, rx1, ry0, ry02, ry1, rz0, rz02, rz1, t;
	float k0, k1, k2, k3, k4, k5, k6, k7;
	float a, b, c, d, e, f, g, h;
	float *q;
	float u, v, w, du, dv, dw;

	t = n[0] + r;
    bx0 = int(t) & noise_mask;
    bx1 = (bx0+1) & noise_mask;
    rx0 = t - floor(t);
    rx1 = rx0 - 1.0;
    rx02 = rx0*rx0;

    t = n[1] + r;
    by0 = int(t) & noise_mask;
    by1 = (by0+1) & noise_mask;
    ry0 = t - floor(t);
    ry1 = ry0 - 1.0;
    ry02 = ry0*ry0;

    t = n[2] + r;
    bz0 = int(t) & noise_mask;
    bz1 = (bz0+1) & noise_mask;
    rz0 = t - floor(t);
    rz1 = rz0 - 1.0;
    rz02 = rz0*rz0;

	u = noise_curve(rx0, rx02);
	v = noise_curve(ry0, ry02);
	w = noise_curve(rz0, rz02);
	du = noise_curve1(rx0, rx02);
	dv = noise_curve1(ry0, ry02);
	dw = noise_curve1(rz0, rz02);

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

	ret[3] = k0 + k1*u + k2*v + k3*w + k4*u*v + k5*v*w + k6*w*u + k7*u*v*w;
	ret[0] = du * (k1 + k4*v + k6*w + k7*v*w) * m;
	ret[1] = dv * (k2 + k5*w + k4*u + k7*w*u) * m;
	ret[2] = dw * (k3 + k6*u + k5*v + k7*u*v) * m;

	return ret;
}

}