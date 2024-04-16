#include <iostream>
class Complex 
{
    int real;
    int imag;

 public: 
    Complex (int r, int i) : real(r), imag(i) {}
    Complex (void) : real(0), imag(0) {} 
    //Complex (const Complex &c) : real(c.real), imag(c.imag) {}
    
    Complex add (const Complex &c)
    {
        Complex res(*this);
        res.real += c.real;
        res.imag += c.imag;
        return res;
    }   

    void print () 
    {
        std::cout << real 
        << (imag > 0 ? "+" : "-")
        << abs(imag) << "i" << std::endl;

    }
};

int main () 
{
    Complex c1 (2, 3), c2(-4, 2);
    Complex res1 = c1.add(c2);
    Complex res2;
    res2 = c1.add(c2);

    res1.print();
    res2.print();
    return 0;
}