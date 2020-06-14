#include "fast_inv_sqrt.h"

// From https://en.wikipedia.org/wiki/Fast_inverse_square_root
//
// > ...fast inverse square root implementation from Quake III Arena, stripped
// > of C preprocessor directives, but including the exact original comment
// > text
//
// Originally from https://github.com/id-Software/Quake-III-Arena/blob/dbe4ddb10315479fc00086f08e25d968b4b43c49/code/game/q_math.c#L549-L572
//
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

// Same as Q_rsqrt, but use int32_t instead of long.
//
// Should have the same time as the original when compiled for 32-bit.
float quake_3_inv_sqrt_int32( float number )
{
	int32_t i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( int32_t * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

// Compute the inverse square root of a non-negative number.
//
//     fast_inv_sqrt(25) // 0.2 == 1/√25
//
// This directly computes an approximation by utilizing the structure of
// IEEE 754-1985 32-bit floating-point numbers.
//
//       s (sign-bit)             M (mantissa)
//       |       E (8-bit exponent)  |
//       |       |                   |
//     +----+----------+------------------------+
//     | 31 | 30 - 23  | 22 - 0                 |
//     +----+----------+------------------------+
//
// For example, to compute the decimal representation x of an IEE 754 formatted
// number:
//
// Let B = 127 (exponent bias) and L = 2^23 (mantissa length)
//
//     x = (-1)^s (1 + M) 2^(E - B)
//
// For example, 2.25 in IEE 754 is
//
//     00111110100000000000000000000000
//
//     s = 0
//     E = 011111010 = 125
//     M = 00000000000000000000000 = 0
//
//     x = (-1)^(0) (1 + 0) 2^(125 - 127) = 1(1)2^(-2) = 0.25
//
// We can also define the following
//
//     m = M / L    (the mantissa as a floating point)
//     e = E - B    (the integer part of x is 2^e)
//
// Then
//
//     x = (1 + m)2^e
//     x interpreted as an integer = M + LE
//
// We want to find the inverse square root, that is
//
//     y = 1/√x = x^(-1/2)
//
// We see that
//
//     log2(y) = (-1/2)log2(x)
//
// Replacing x and y with their floating-point components
//
//     log2(1 + m_y) + e_y = (-1/2)(log2(1 + m_x) + e_x)
//
// We see that each side has a term like log(1 + v), where v ∈ [0, 1). For such
// v, log(1 + v) is approximately equal to a straight line, so we substitute
//
//     log(1 + v) ≈ v + σ
//
// Where σ is some constant that we pick.
//
// So
//
//     m_y + σ + e_y =~ (-1/2)(m_x + σ + e_y)
//
// Substituting back the integer components
//
//     M_y/L + σ + E_y - B =~ (-1/2)(M_x/L + σ + E_x - B)
//     M_y/L + E_y =~ (-1/2)(M_x/L + σ + E_x - B) -σ + B
//     M_y/L + E_y =~ (-1/2)(M_x/L + σ + E_x) - (3/2)(-σ - B)
//     M_y + LE_y =~ (3/2)L(B - σ) - (1/2)(M_x + LE_x)
//
// Notice we now have the integer representations of y and x on both sides of
// the equation. Let I_n be the integer representation of n, then
//
//     I_y =~ (3/2)L(B - σ) - (1/2)I_x
//
// That is, the integer representation of y is equal to some constant minus one
// half the integer representation of x.
//
// Using σ = 0.0450465, we get
//
//     (3/2)L(B - σ) = (3/2)(2^23)(B - 0.0450465) = 1597463007 = 0x5f3759df
//
// We also use use Newton's Method to increase the accuracy
//
// > If x_n is an approximation to the solution of f(x) = 0 and if f'(x_n) ≠ 0,
// > then the next approximation is given by
// >
// >     x_(n+1) = x_n - f(x_n)/f'(x_n)  ,  n >= 0
//
// The positive roots of the inverse square root function are solutions to
//
//     f(x)  = 1/x^2 - x_0 = 0         (x_0 is the inital guess)
//
//     f(x)  = 1/x^2 - x_0
//     f'(x) = -2 x^(-2 - 1) = 2/x^3
//
//     f(x_n+1) = x_n - f(x_n)/f'(x_n)
//              = x_n - [1/x^2 - x_0] / [2/x^3]
//              ... (todo)
//              = [x_n (3 - x_0 (x_n^2))] / 2
//              = x_n ((3/2) - (x_0/2)(x_n^2))
//
// References:
//
// - https://chortle.ccsu.edu/assemblytutorial/Chapter-30/ass30_17.html
// - https://www.h-schmidt.net/FloatConverter/IEEE754.html
// - http://h14s.p5r.org/2012/09/0x5f3759df.html?mwh=1
// - https://en.wikipedia.org/wiki/Fast_inverse_square_root
//
float fast_inv_sqrt(float number)
{
  // interpret the bits of the floating-point input as an integer
	int32_t I_x = *(int32_t *)&number;

  // approximate the integer representation of the inverse square root
	int32_t I_y = 0x5f3759df - (I_x >> 1);

  // cast the integer representation back to floating point
  float y = *(float *)&I_y;

  // use Newton's method to increase accuracy
	y = y * (1.5F - ((number * 0.5F) * y * y)); // 1st iteration
  y = y * (1.5F - ((number * 0.5F) * y * y)); // 2nd iteration

	return y;
}
