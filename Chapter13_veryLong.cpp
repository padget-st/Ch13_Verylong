#include "verylong.h"

int main()
{
    Verylong v1("11111111573123"), v2("24343651235235356435764578"), v3("130000000"), v4;
    v4.getvl();
    v4.putvl();
    Verylong v5 = v4 / v1;
    
    v5.putvl();
}