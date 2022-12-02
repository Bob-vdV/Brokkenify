
#include "doubles.ih"

istream &operator>>(istream &ins, Doubles &doubles)
{
    Doubles tmp; //  A temporary

    double value;
    while (ins >> value)
        tmp.push_back(value); // Read into temporary

    // Keep old data if the stream was bad.
    if (!ins.bad()) // either fail() or eof()
        doubles.swap(tmp);

    return ins;
}
