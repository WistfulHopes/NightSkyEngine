#pragma once

#define COORD_SCALE ((double)1000 / 0.43)

uint32 isqrt_impl(uint64 const n, uint64 const xk);

uint32 isqrt(uint64 const n);
