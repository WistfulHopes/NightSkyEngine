#pragma once

#define COORD_SCALE ((double)1000 / 0.43)

/**
 * Implementation of integer square root.
 */
uint32 isqrt_impl(uint64 const n, uint64 const xk);

/**
 * Takes the square root of an integer n without floats.
 * 
 * @param n The integer to take the square root of.
 * @return Returns the square root of n.
 */
uint32 isqrt(uint64 const n);
