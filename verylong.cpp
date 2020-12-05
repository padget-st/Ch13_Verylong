#include "verylong.h"
#include <iomanip>

int Verylong::set_negativity(char temp[], long len)
{
    int i;
    if (temp[len - 1] == '-')
    {
        i = (len - 2);
        m_negative = true;
        temp[len - 1] = '\0';
    }
    else
    {
        i = (len - 1);
        m_negative = false;
    }
    return i;
}
//---------------------------------------------------------
Verylong::Verylong(const char s[SZ], bool negative)
{
    strcpy_s(vlstr, s);
    vlen = strlen(s);
    m_negative = negative;
}
//---------------------------------------------------------
Verylong::Verylong() : vlen(0), m_negative(false)
{
    vlstr[0] = '\0';
}
//---------------------------------------------------------
Verylong::Verylong(const char s[SZ])
{
    char temp[SZ];
    int len = strlen(s);
    strcpy_s(temp, s);
    _strrev(temp);
    bool flag = true;

    int i = set_negativity(temp, len);

    for (; i >= 0; i--)
    {
        if (temp[i] < '0' || temp[i] > '9')
            throw std::runtime_error("Wrong symbol");
        if (flag && temp[i] == '0')
            temp[i] = '\0';
        else flag = false;
    }
    strcpy_s(vlstr, temp);
    vlen = strlen(temp);
}
//---------------------------------------------------------
Verylong::Verylong(const long n) : m_negative(false)
{
    if (n < 0)
        m_negative = true;
    _ltoa_s(std::abs(n), vlstr, 10);
    _strrev(vlstr);
    vlen = strlen(vlstr);
}
//---------------------------------------------------------
void Verylong::putvl() const
{
    char temp[SZ];
    strcpy_s(temp, vlstr);

    if (temp[0] == '\0')
    {
       std::cout << '0' << '\n';
       return;
    }

    if (m_negative)
        std::cout << "-";

    std::cout << _strrev(temp) << std::endl;
}
//---------------------------------------------------------
void Verylong::getvl()
{
    char temp[SZ];
    
    std::cout << "Enter a -Verylong- number: ";
    while (1)
    {
        std::cin >> std::setw(SZ) >> temp;
        std::cin.ignore(SZ, '\n');
        int len = strlen(temp);
        _strrev(temp);
        bool flag = true;

        int i = set_negativity(temp, len);
        for (; i >= 0; i--)
        {
            if (temp[i] < '0' || temp[i] > '9')
            {
                std::cout << "Wrong symbol. Try again: ";
                continue;
            }
            if (flag && temp[i] == '0')
                temp[i] = '\0';
            else flag = false;
        }
        break;
    }
    strcpy_s(vlstr, temp);
    vlen = strlen(temp);
}
//---------------------------------------------------------
bool Verylong::isNegative() const
{
    return m_negative;
}
//---------------------------------------------------------
comp_rez Verylong::compare(const Verylong& v) const
{
    if (vlen > v.vlen)
        return comp_rez::frst;
    else if (vlen < v.vlen)
        return comp_rez::scnd;
    else
        for (int i = (vlen - 1); i >= 0; i--)
        {
            if (vlstr[i] > v.vlstr[i])
                return comp_rez::frst;
            else if (vlstr[i] < v.vlstr[i])
                return comp_rez::scnd;
        }
    return comp_rez::equal;
}
//---------------------------------------------------------
Verylong Verylong::operator + (const Verylong& v) const
{

    comp_rez comp_result = compare(v);
    Verylong vl_temp;
    if (comp_result == comp_rez::frst && m_negative != v.m_negative)
    {
        vl_temp = (Verylong(this->vlstr, false) - Verylong(v.vlstr, false));
        return Verylong(vl_temp.vlstr, m_negative);
    }
    else if (comp_result == comp_rez::scnd && m_negative != v.m_negative)
    {
        vl_temp = (Verylong(v.vlstr, false) - Verylong(this->vlstr, false));
        return Verylong(vl_temp.vlstr, v.m_negative);
    }

    char temp[SZ];
    bool negative = false;
    if (m_negative && v.m_negative)
        negative = true;

    int j;
    int maxlen = (vlen > v.vlen) ? vlen : v.vlen;
    int carry = 0;
    for (j = 0; j < maxlen; j++)
    {
        int d1 = (j > vlen - 1) ? 0 : vlstr[j] - '0';
        int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0';
        int digitsum = d1 + d2 + carry;
        if (digitsum >= 10)
        {
            digitsum -= 10; carry = 1;
        }
        else
            carry = 0;
        temp[j] = digitsum + '0';
    }
    if (carry == 1)
        temp[j++] = '1';
    temp[j] = '\0';
    return Verylong(temp, negative);
}
//---------------------------------------------------------
Verylong Verylong::operator * (const Verylong& v) const
{
    Verylong pprod;
    Verylong tempsum;
    for (int j = 0; j < v.vlen; j++)
    {
        int digit = v.vlstr[j] - '0';
        pprod = multdigit(digit);
        for (int k = 0; k < j; k++)
            pprod = mult10(pprod);
        tempsum = tempsum + pprod;
    }
    if (m_negative != v.m_negative)     
        return Verylong (tempsum.vlstr, true);
    else return tempsum;
}
//---------------------------------------------------------
Verylong Verylong::mult10(const Verylong& v) const
{
    char temp[SZ];
    for (int j = v.vlen - 1; j >= 0; j--)
        temp[j + 1] = v.vlstr[j];
    temp[0] = '0';
    temp[v.vlen + 1] = '\0';
    return Verylong(temp, false);
}
//---------------------------------------------------------
Verylong Verylong::multdigit(const int d2) const
{
    char temp[SZ];
    int j, carry = 0;
    for (j = 0; j < vlen; j++)
    {
        int d1 = vlstr[j] - '0';
        int digitprod = d1 * d2;
        digitprod += carry;
        if (digitprod >= 10)
        {
            carry = digitprod / 10;
            digitprod -= carry * 10;
        }
        else
            carry = 0;
        temp[j] = digitprod + '0';
    }
    if (carry != 0)
        temp[j++] = carry + '0';
    temp[j] = '\0';
    return Verylong(temp, false);
}
//---------------------------------------------------------
Verylong Verylong::operator - (const Verylong& v) const
{
    comp_rez comp_result = compare(v);
    Verylong vl_temp;
    if((comp_result == comp_rez::frst || comp_result == comp_rez::scnd) && m_negative != v.m_negative)
    {
        vl_temp = (Verylong(this->vlstr, false) + Verylong(v.vlstr, false));
        return Verylong(vl_temp.vlstr, m_negative);
    }
    else if (comp_result == comp_rez::scnd)
    {
        vl_temp = (Verylong(v.vlstr, !v.m_negative) - Verylong(vlstr, !m_negative));
        return vl_temp;
    }

    char temp[SZ];
    int j, carry = 0;
    bool negative = m_negative;

    int maxlen = (vlen > v.vlen) ? vlen : v.vlen;

    for (j = 0; j < maxlen; j++)
    {
        int d1 = (j > vlen - 1) ? 0 : this->vlstr[j] - '0';
        int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0';
        int digitsub = d1 - carry - d2;
        if (digitsub < 0)
        {
            digitsub += 10;
            carry = 1;
        }
        else
            carry = 0;
        temp[j] = digitsub + '0';
    }

    for (int i = j - 1; i >= 0; i--)
    {
        if (temp[i] != '0')
        {
            temp[i + 1] = '\0';
            break;
        }
        else temp[i] = '\0';
    }

    return Verylong(temp, negative);
}
//---------------------------------------------------------
Verylong Verylong::operator / (const Verylong& v) const
{
    if (v.vlen == 0 || (v.vlen == 1 && v.vlstr[0] == '0'))
        throw std::runtime_error("Disision by 0");
    if (compare(v) == comp_rez::scnd)
        return Verylong();

    char temp[SZ], str_num[SZ], vlstr_rev[SZ];
    strcpy_s(vlstr_rev, vlstr);
    _strrev(vlstr_rev);
    int count = 1, j = 0, i = 0;
    bool flag = true;
    comp_rez comp_result;

    for (; j < v.vlen; j++)
        str_num[j] = vlstr_rev[j];
    str_num[j] = '\0';

    Verylong vl_sum, vl_num(_strrev(str_num), false), vl_v(v.vlstr, false);
    while (flag)
    {
        vl_sum = vl_v;
        count = 1;
        comp_result = vl_num.compare(vl_v);

        switch (comp_result)
        {
        case comp_rez::equal:
        case comp_rez::frst:
        {   
            while (vl_sum.compare(vl_num) == comp_rez::scnd || vl_sum.compare(vl_num) == comp_rez::equal)
            {
                vl_sum = vl_sum + vl_v;
                ++count;
            }
            vl_sum = vl_sum - vl_v;
            vl_num = vl_num - vl_sum;
            --count;
            temp[i++] = char(count) + '0';
            if(vl_num.vlen == 0 && j < strlen(vlstr_rev))
                temp[i++] = '0';
            break;
        }
        case comp_rez::scnd:
        {
            if (j < strlen(vlstr_rev))
            {
                vl_num = (vl_num * 10) + (vlstr_rev[j++] - '0');
                if ((vl_num.vlen == 1 && vl_num.vlstr[0] == '0') && j < strlen(vlstr_rev))
                {
                    temp[i++] = '0';
                    vl_num = Verylong();
                }
                break;
            }
            else flag = false;
            break;
        }
        }
    }
    temp[i] = '\0';
    if (m_negative != v.m_negative)
        flag = true;
    return Verylong(_strrev(temp), flag);
 }