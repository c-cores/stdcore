#include <gtest/gtest.h>

#include <std/math.h>

using namespace core;

TEST(math, degtorad)
{
	EXPECT_EQ(m_pi*0.25, degtorad(45));
	EXPECT_EQ(m_pi*0.50, degtorad(90));
	EXPECT_EQ(m_pi*0.75, degtorad(135));
	EXPECT_EQ(m_pi*1.00, degtorad(180));

	EXPECT_EQ(m_pi*1.25, degtorad(225));
	EXPECT_EQ(m_pi*1.50, degtorad(270));
	EXPECT_EQ(m_pi*1.75, degtorad(315));
	EXPECT_EQ(m_pi*2.00, degtorad(360));
}

TEST(math, radtodeg)
{
	EXPECT_EQ(radtodeg(m_pi*0.25), 45);
	EXPECT_EQ(radtodeg(m_pi*0.50), 90);
	EXPECT_EQ(radtodeg(m_pi*0.75), 135);
	EXPECT_EQ(radtodeg(m_pi*1.00), 180);

	EXPECT_EQ(radtodeg(m_pi*1.25), 225);
	EXPECT_EQ(radtodeg(m_pi*1.50), 270);
	EXPECT_EQ(radtodeg(m_pi*1.75), 315);
	EXPECT_EQ(radtodeg(m_pi*2.00), 360);
}

TEST(math, count_ones)
{
	EXPECT_EQ((uint32_t)0, count_ones(0));
	EXPECT_EQ((uint32_t)1, count_ones(1));
	EXPECT_EQ((uint32_t)1, count_ones(2));
	EXPECT_EQ((uint32_t)2, count_ones(3));
	EXPECT_EQ((uint32_t)1, count_ones(4));
	EXPECT_EQ((uint32_t)2, count_ones(5));
	EXPECT_EQ((uint32_t)2, count_ones(6));
	EXPECT_EQ((uint32_t)3, count_ones(7));
	EXPECT_EQ((uint32_t)1, count_ones(8));
	EXPECT_EQ((uint32_t)2, count_ones(9));
	EXPECT_EQ((uint32_t)2, count_ones(10));
	EXPECT_EQ((uint32_t)3, count_ones(11));
	EXPECT_EQ((uint32_t)2, count_ones(12));
	EXPECT_EQ((uint32_t)3, count_ones(13));
	EXPECT_EQ((uint32_t)3, count_ones(14));
	EXPECT_EQ((uint32_t)4, count_ones(15));
	EXPECT_EQ((uint32_t)32, count_ones((uint32_t)-1));
}

TEST(math, count_zeros)
{
	EXPECT_EQ((uint32_t)31, count_zeros(1));
	EXPECT_EQ((uint32_t)31, count_zeros(2));
	EXPECT_EQ((uint32_t)30, count_zeros(3));
	EXPECT_EQ((uint32_t)31, count_zeros(4));
	EXPECT_EQ((uint32_t)30, count_zeros(5));
	EXPECT_EQ((uint32_t)30, count_zeros(6));
	EXPECT_EQ((uint32_t)29, count_zeros(7));
	EXPECT_EQ((uint32_t)31, count_zeros(8));
	EXPECT_EQ((uint32_t)30, count_zeros(9));
	EXPECT_EQ((uint32_t)30, count_zeros(10));
	EXPECT_EQ((uint32_t)29, count_zeros(11));
	EXPECT_EQ((uint32_t)30, count_zeros(12));
	EXPECT_EQ((uint32_t)29, count_zeros(13));
	EXPECT_EQ((uint32_t)29, count_zeros(14));
	EXPECT_EQ((uint32_t)28, count_zeros(15));
	EXPECT_EQ((uint32_t)0, count_zeros((uint32_t)-1));
}

TEST(math, powi)
{
	EXPECT_EQ(1, powi(0, 0));
	EXPECT_EQ(0, powi(0, 1));
	EXPECT_EQ(0, powi(0, 2));
	EXPECT_EQ(0, powi(0, 3));

	EXPECT_EQ(1, powi(1, 0));
	EXPECT_EQ(1, powi(1, 1));
	EXPECT_EQ(1, powi(1, 2));
	EXPECT_EQ(1, powi(1, 3));

	EXPECT_EQ(1, powi(2, 0));
	EXPECT_EQ(2, powi(2, 1));
	EXPECT_EQ(4, powi(2, 2));
	EXPECT_EQ(8, powi(2, 3));

	EXPECT_EQ(1, powi(3, 0));
	EXPECT_EQ(3, powi(3, 1));
	EXPECT_EQ(9, powi(3, 2));
	EXPECT_EQ(27, powi(3, 3));
}

TEST(math, log2i)
{
	EXPECT_EQ(0, log2i(1));
	EXPECT_EQ(1, log2i(2));
	EXPECT_EQ(2, log2i(3));
	EXPECT_EQ(2, log2i(4));
	EXPECT_EQ(3, log2i(5));
	EXPECT_EQ(3, log2i(6));
	EXPECT_EQ(3, log2i(7));
	EXPECT_EQ(3, log2i(8));
}

TEST(math, abs)
{
	EXPECT_EQ(10.5, abs(10.5));
	EXPECT_EQ(10.5, abs(-10.5));
	EXPECT_EQ(10.5f, abs(10.5f));
	EXPECT_EQ(10.5f, abs(-10.5f));
	EXPECT_EQ(10, abs(10));
	EXPECT_EQ(10, abs(-10));
	EXPECT_EQ(0, abs(0));
}

TEST(math, minmax)
{
	EXPECT_EQ(5, min(5, 10));
	EXPECT_EQ(5, min(10, 5));
	EXPECT_EQ(5, min(5, 5));
	EXPECT_EQ(10.5, min(10.5, 10.6));
	EXPECT_EQ(-5, min(5, -5));

	EXPECT_EQ(10, max(5, 10));
	EXPECT_EQ(10, max(10, 5));
	EXPECT_EQ(5, max(5, 5));
	EXPECT_EQ(10.6, max(10.5, 10.6));
	EXPECT_EQ(5, max(5, -5));
}

TEST(math, clamp)
{
	EXPECT_EQ(5, clamp(3, 5, 10));
	EXPECT_EQ(10, clamp(20, 5, 10));
	EXPECT_EQ(7, clamp(7, 5, 10));

	EXPECT_EQ(5.2, clamp(3.1, 5.2, 10.5));
	EXPECT_EQ(10.5, clamp(20.1, 5.2, 10.5));
	EXPECT_EQ(7.2, clamp(7.2, 5.3, 10.5));

	EXPECT_EQ(5.2f, clamp(3.1f, 5.2f, 10.5f));
	EXPECT_EQ(10.5f, clamp(20.1f, 5.2f, 10.5f));
	EXPECT_EQ(7.2f, clamp(7.2f, 5.3f, 10.5f));
}

TEST(math, median)
{
	EXPECT_EQ(5, median(2, 5, 10));
	EXPECT_EQ(5, median(5, 5, 10));
	EXPECT_EQ(10, median(5, 10, 10));
	EXPECT_EQ(5.2, median(2.5, 5.2, 10.8));
	EXPECT_EQ(5.2, median(5.2, 5.2, 10.5));
	EXPECT_EQ(10.5, median(5.2, 10.5, 10.5));
	EXPECT_EQ(5.2f, median(2.5f, 5.2f, 10.8f));
	EXPECT_EQ(5.2f, median(5.2f, 5.2f, 10.5f));
	EXPECT_EQ(10.5f, median(5.2f, 10.5f, 10.5f));
}

TEST(math, evenodd)
{
	EXPECT_FALSE(is_even(1));
	EXPECT_TRUE(is_odd(1));
	EXPECT_TRUE(is_even(2));
	EXPECT_FALSE(is_odd(2));
	EXPECT_FALSE(is_even(3));
	EXPECT_TRUE(is_odd(3));
	EXPECT_TRUE(is_even(4));
	EXPECT_FALSE(is_odd(4));
	EXPECT_FALSE(is_even(5));
	EXPECT_TRUE(is_odd(5));
	EXPECT_TRUE(is_even(6));
	EXPECT_FALSE(is_odd(6));
	EXPECT_FALSE(is_even(7));
	EXPECT_TRUE(is_odd(7));
	EXPECT_TRUE(is_even(8));
	EXPECT_FALSE(is_odd(8));
}
