
#include "doubles.ih"

Doubles &Doubles::operator=(Doubles const &other)
{
    Doubles copy(other); // Keep own data until succesful copy.
    swap(copy);
    return *this;
}
