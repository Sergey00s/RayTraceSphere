#include "minirt.h"




double random_double() 
{
    // Returns a random real in [0,1).
    return (double)rands() / (MYRAND_MAX + 1);
}

double random_doubles(double min, double max) 
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

unsigned rands()
{
    static unsigned short lfsr = 0xACE1u;
    static unsigned bit;
     bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
    return (lfsr =  (lfsr >> 1) | (bit << 15)) % MYRAND_MAX;
}


t_vec3 random_f() 
{
        return vec3(random_double(), random_double(), random_double());
}

t_vec3 my_random(double min, double max) 
{
        return vec3(random_doubles(min, max), random_doubles(min, max), random_doubles(min, max));
}


t_vec3 random_in_unit_sphere() 
{
    while (1) 
    {
        t_vec3 p = my_random(-1,1);
        if (length_squared(p) >= 1) 
            continue;
        return p;
    }
}