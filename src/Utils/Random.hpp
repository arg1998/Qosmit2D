#include "defines.hpp"

#include <cstdlib> 
#include <ctime>



// generates a random integer in the range [min, max)
s32 RandomS32(s32 min, s32 max) {
    if(min == max) return min;
    return min + (rand() % (max - min));
}

// generates a random floating-point number in the range [0.0, 1.0]
f32 RandomFloat() {
    return static_cast<f32>(rand()) / static_cast<f32>(RAND_MAX);
}

// generates a random floating-point number in the range [-1.0, +1.0]
f32 RandomFloatSinged() {
    return RandomFloat() * 2.0f - 1.0f;
}
