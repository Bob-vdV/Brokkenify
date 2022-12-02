
#include "doubles.ih"

double &Doubles::operator[](std::size_t idx)
{
    return d_values[idx];
}
