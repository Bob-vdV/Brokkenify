
#include "doubles.ih"

ostream &operator<<(ostream &outs, Doubles const &doubles)
{
    for (size_t ix = 0; ix != doubles.d_size; ++ix)
    {
        outs << doubles.d_values[ix] << ' '; // space for '1 2' vs. '12'
        if (!outs) 
            break;
    }
    return outs;
}
