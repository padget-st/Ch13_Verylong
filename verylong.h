#pragma once
#include <iostream>
#include <string.h>
#include <stdlib.h>

constexpr int SZ = 1000;

enum class comp_rez {frst = -1, 
                    equal = 0, 
                    scnd = 1};

class Verylong
{
private:
    char vlstr[SZ];
    int vlen;
    bool m_negative;
    int set_negativity(char temp[], long len);
    Verylong multdigit(const int) const;
    Verylong mult10(const Verylong&) const;  
    Verylong(const char s[SZ], bool negative);
public:
    Verylong(); 
    Verylong(const char s[SZ]);
    Verylong(const long n);
    void putvl() const;
    void getvl();
    bool isNegative() const;
    comp_rez compare(const Verylong&) const;
    Verylong operator + (const Verylong&) const;
    Verylong operator * (const Verylong&) const;
    Verylong operator - (const Verylong&) const;
    Verylong operator / (const Verylong&) const;
};