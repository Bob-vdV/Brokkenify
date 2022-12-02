
#include "doubles.ih"

Doubles::Doubles(Doubles const &other)
    : d_size(other.d_size)
    , d_capacity(other.d_size) // Not capacity: shrink to fit.
    , d_values(new double[d_capacity]) // Our own allocation
{
    for (size_t ix = 0; ix != d_size; ++ix)
        d_values[ix] = other.d_values[ix];     // Copy values.
}

