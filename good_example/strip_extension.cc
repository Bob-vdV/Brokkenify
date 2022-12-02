#include "main.ih"

string strip_extension(string const &filename)
{
    return filesystem::path(filename).stem();
}

