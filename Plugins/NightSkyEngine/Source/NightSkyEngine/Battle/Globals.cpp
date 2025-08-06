#include "Globals.h"

uint32 isqrt_impl(
	uint64 const n,
	uint64 const xk)
{
	uint64 const xk1 = (xk + n / xk) / 2;
	return (xk1 >= xk) ? xk : isqrt_impl(n, xk1);
}

uint32 isqrt(uint64 const n)
{
	if (n == 0) return 0;
	if (n == 18446744073709551615ULL) return 4294967295U;
	return isqrt_impl(n, n);
}