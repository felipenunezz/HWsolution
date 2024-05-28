#include <iostream>

class Fraction 
{
	int num;
	int den;


public:

	Fraction() : num(0), den(1) {}
	Fraction(int _num, int _den) : num(_num), den(_den) {}
	Fraction(const Fraction& other) : num(other.num), den(other.den) {}
	Fraction(const std::string& fractionStr);


	~Fraction() {}

    Fraction& operator=(const Fraction& other);


    bool operator==(int value) const;
    bool operator!=(int value) const;
    bool operator>(int value) const;
    bool operator<(int value) const;
    bool operator>=(int value) const;
    bool operator<=(int value) const;

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;


    Fraction operator+(int value) const;
    Fraction operator-(int value) const;
    Fraction operator*(int value) const;
    Fraction operator/(int value) const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction& operator+=(int value);
    Fraction& operator-=(int value);
    Fraction& operator*=(int value);
    Fraction& operator/=(int value);

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) 
    {
        os << frac.num << '/' << frac.den;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Fraction& frac) 
    {
        char colon;
        is >> frac.num >> colon >> frac.den;
        frac.simplify();
        return is;

    }


    Fraction simplify() 
    {
        int del = gcd(num, den);
        
        this->num /= del;
        this->den /= del;

        return *this;
    }

private:

    int gcd(int a, int b) const 
    {

        while (a != b) 
        {
            if (a > b) a %= b;
            if (b > a) b %= a;
        }
        return a;
    }
};

Fraction::Fraction(const std::string& fractionStr) 
{
	//TBD
}

Fraction& Fraction::operator=(const Fraction& other) { this->num = other.num; this->den = other.den; return *this; }


bool Fraction::operator==(int value) const { return num == value * den; }
bool Fraction::operator!=(int value) const { return num != value * den; }
bool Fraction::operator>(int value) const   { return num > value * den; }
bool Fraction::operator<(int value) const   { return num < value * den; }
bool Fraction::operator>=(int value) const { return num >= value * den; }
bool Fraction::operator<=(int value) const { return num <= value * den; }

bool Fraction::operator==(const Fraction& other) const { return num * other.den == other.num * den; }
bool Fraction::operator!=(const Fraction& other) const { return num * other.den != other.num * den; }
bool Fraction::operator>(const Fraction& other) const  { return num * other.den  > other.num * den; }
bool Fraction::operator<(const Fraction& other) const  { return num * other.den  < other.num * den; }
bool Fraction::operator>=(const Fraction& other) const { return num * other.den >= other.num * den; }
bool Fraction::operator<=(const Fraction& other) const { return num * other.den <= other.num * den; }


Fraction Fraction::operator+(int value) const { Fraction temp(num, den); temp.num = num + value * den; return temp.simplify(); }
Fraction Fraction::operator-(int value) const { Fraction temp(num, den); temp.num = num - value * den; return temp.simplify(); }
Fraction Fraction::operator*(int value) const { Fraction temp(num, den); temp.num = num * value; return temp.simplify(); }
Fraction Fraction::operator/(int value) const { Fraction temp(num, den); temp.den = den * value; return temp.simplify(); }

Fraction Fraction::operator+(const Fraction& other) const { Fraction temp(num, den); temp.num = num * other.den + other.num * den; temp.den = other.den * den; return temp.simplify(); }
Fraction Fraction::operator-(const Fraction& other) const { Fraction temp(num, den); temp.num = num * other.den - other.num * den; temp.den = other.den * den; return temp.simplify(); }
Fraction Fraction::operator*(const Fraction& other) const { Fraction temp(num, den); temp.num = num * other.num; temp.den = den * other.den; return temp.simplify(); }
Fraction Fraction::operator/(const Fraction& other) const { Fraction temp(num, den); temp.num = num * other.den; temp.den = den * other.num; return temp.simplify(); }

Fraction& Fraction::operator+=(int value) { this->num = num + value * den; this->simplify(); return *this; }
Fraction& Fraction::operator-=(int value) { this->num = num - value * den; this->simplify(); return *this; }
Fraction& Fraction::operator*=(int value) { this->num = num * value; this->simplify(); return *this; }
Fraction& Fraction::operator/=(int value) { this->den = den * value; this->simplify(); return *this; }

Fraction& Fraction::operator+=(const Fraction& other) { this->num = num * other.den + other.num * den; this->den *= other.den; this->simplify(); return *this; }
Fraction& Fraction::operator-=(const Fraction& other) { this->num = num * other.den - other.num * den; this->den *= other.den; this->simplify(); return *this; }
Fraction& Fraction::operator*=(const Fraction& other) { this->num *= other.num; this->den *= other.den; this->simplify(); return *this; }
Fraction& Fraction::operator/=(const Fraction& other) { this->num *= other.den; this->den *= other.num; this->simplify(); return *this; }



main () 
{
	return 0;
}