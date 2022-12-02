
#include "doubles.ih"

void Doubles::push_back(double value)
{
    if (d_size == d_capacity)                           // cannot store?
        reserve(d_capacity == 0 ? 8 : 2 * d_capacity);  // double our space
    
    d_values[d_size++] = value;
}
