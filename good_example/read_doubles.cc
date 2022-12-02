#include "main.ih"

Doubles read_ascii_doubles(std::filesystem::path const &filename)
{
    // Open input
    ifstream input(filename);
    if (!input)
    {
        cerr << "Couldn't open " << filename << " for reading.\n";
        // All we can do at this stage of the course.
    }
    
    Doubles my_doubles;

    // Read ascii values
    input >> my_doubles;
    if (!input.eof())
        cerr << "Expected all doubles in file.\n";
    input.close();

    return my_doubles;
}
