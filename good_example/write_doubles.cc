#include "main.ih"

void write_raw_doubles(std::filesystem::path const &filename, Doubles const &doubles)
{
    // Open output
    ofstream output(filename);
    if (!output)
        cerr << "Couldn't open " << filename << " for writing.\n";

    // Write binary values
    output.write(reinterpret_cast<char const *>(&doubles[0]), doubles.size() * sizeof(double));
    output.close();
}
