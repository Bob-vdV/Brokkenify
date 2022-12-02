
#include "doubles.ih"

// Returning a reference facilitates raw output of data.
double const &Doubles::operator[](std::size_t idx) const
{
    return d_values[idx]; // No range checking
}
