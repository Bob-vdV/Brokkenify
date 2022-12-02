#include "main.ih"

std::uintmax_t count_doubles(std::filesystem::path const &filename)
{
    return file_size(filename) / sizeof(double);
}
