
#include "doubles.ih"

void Doubles::resize(size_t new_size)
{
    if (new_size > d_capacity)
        reserve(new_size);

    // Set any added values to zero.
    for (size_t ix = 0; ix != new_size; ++ix)
        d_values[ix] = 0.0;

    d_size = new_size;
}
