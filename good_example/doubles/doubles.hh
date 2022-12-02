#ifndef doubles_hh_defd_153ec1f0_42fb_11ec_8153_6776448f2311
#define doubles_hh_defd_153ec1f0_42fb_11ec_8153_6776448f2311

#include <string>
#include <iosfwd>

class Doubles
{
    std::size_t d_size;
    std::size_t d_capacity;
    double *d_values;

public:
    ~Doubles();
    Doubles();
    Doubles(Doubles const &other);
    Doubles(Doubles &&tmp);
    Doubles &operator=(Doubles &&tmp);
    Doubles &operator=(Doubles const &other);
    void swap(Doubles &other);
    void resize(size_t count);
    void push_back(double value);
    void reserve(std::size_t newcap);
    double const &operator[](std::size_t idx) const;
    double &operator[](std::size_t idx);
    std::size_t size() const;
    std::size_t capacity() const;
private:
    friend std::istream &operator>>(std::istream &ins, Doubles &doubles);
    friend std::ostream &operator<<(std::ostream &outs, Doubles const &doubles);
};


inline Doubles::~Doubles()
{
    delete[] d_values;
}

inline std::size_t Doubles::size() const
{
    return d_size;
}

inline std::size_t Doubles::capacity() const
{
    return d_capacity;
}


#endif //doubles_hh_defd_153ec1f0_42fb_11ec_8153_6776448f2311
