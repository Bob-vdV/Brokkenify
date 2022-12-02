
#include "doubles.ih"

Doubles &Doubles::operator=(Doubles &&tmp)
{
    swap(tmp);
    return *this;
}
