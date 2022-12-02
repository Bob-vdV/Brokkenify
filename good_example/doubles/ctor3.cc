
#include "doubles.ih"

Doubles::Doubles(Doubles &&tmp)
    : d_size(tmp.d_size)
    , d_capacity(tmp.d_capacity) // not size!
    , d_values(tmp.d_values) // steal the pointer
{
    tmp.d_size = 0; // For reasons we'll see later.
    tmp.d_capacity = 0;
    tmp.d_values = nullptr; //Ensure its deletion won't hurt us.
}
