// Program to convert text file containing doubles to binary.

#include "main.ih"

enum {
    ERROR = 1,
};

int usage(char const * const prog)
{
    char const usage_info[] = R"(
    <filename> is the name of the input file, a plain text file with double-
    precision floating-point values.
    [max] is the maximum number of values to put in the output binary file.)";

    std::cout << "Usage: " << prog << " <filename> [max]\n\n" << usage_info << "\n\n";
    return ERROR;
}


int main(int argc, char **argv)
{
    if (argc <= 1)
        return usage(argv[0]);

    // Determine input and output file names.
    string const input_filename(argv[1]);

    Doubles my_doubles = read_ascii_doubles(input_filename);

    // If this grows size, zeroes will be added.
    if (argc > 2)
        my_doubles.resize(stoull(argv[2]));
    
    write_raw_doubles(strip_extension(input_filename) + ".data", my_doubles);
}
