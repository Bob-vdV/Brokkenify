
#include "doubles.ih"

void Doubles::reserve(size_t newcap)
{
    if (newcap <= d_capacity)
        return;       // Already big enough

    // Allocate new space.
    double *tmp_values = new double[newcap];
    d_capacity = newcap;
    
    // Copy the values.
    for (size_t ix = 0; ix != d_size; ++ix)
        tmp_values[ix] = d_values[ix];

    // Delete old pointer.
    delete[] d_values;
    d_values = tmp_values;
}
