
#include "doubles.ih"

namespace {
    void *cast(Doubles *doubles);
}

void Doubles::swap(Doubles &other)
{
    enum
    {
        SIZE = sizeof(Doubles)
    };
    
    char buffer[SIZE];
    memcpy(buffer, cast(this), SIZE);
    memcpy(cast(this), cast(&other), SIZE);
    memcpy(cast(&other), buffer, SIZE);
}

namespace {

    void *cast(Doubles *doubles)
    {
        return static_cast<void *>(doubles);
    }
    
}
