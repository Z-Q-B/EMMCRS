using namespace std;
extern "C"
{
#include "miracl.h"
#include "mirdef.h"
}
#pragma comment(lib,"miracl.lib")
#include <cstring>
#include <iostream>

    int main() {
       
        miracl* mip = mirsys(5000, 16);
        mip->IOBASE = 16;
        clock_t start, end;
        double sum = 0.0;
      
        char p_str[] = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFF";
        char a_str[] = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFC";
        char b_str[] = "1C97BEFC54BD7A8B65ACF89F81D4D4ADC565FA45";
        char gx_str[] = "4A96B5688EF573284664698968C38BB913CBFC82";
        char gy_str[] = "23A628553168947D59DCC912042351377AC5FB32";

       big  p = mirvar(0);
       big  a = mirvar(0);
       big  b = mirvar(0);
       big  gx = mirvar(0);
       big  gy = mirvar(0);

        cinstr(p, p_str);
        cinstr(a, a_str);
        cinstr(b, b_str);
        cinstr(gx, gx_str);
        cinstr(gy, gy_str);

        ecurve_init(a, b, p, MR_BEST); 
        epoint* G = epoint_init();    

        if (!epoint_set(gx, gy, 1, G)) { 
            fprintf(stderr, "Error setting point G.\n");
            return 1;
        }
        epoint* result = epoint_init();
        for (int i = 0; i < 10000; i++) {

             big k = mirvar(0);
             bigbits(160, k);

            start = clock();
            ecurve_mult(k, G, result);  
            end = clock();

            double time = double(end - start) / CLOCKS_PER_SEC;
            sum = sum + time;
        }
        printf("ecc: %.3lf ms \n", sum / 10);

        mirkill(p);
        mirkill(a);
        mirkill(b);
        mirkill(gx);
        mirkill(gy);
        epoint_free(G);
        epoint_free(result);
        mirexit();

        return 0;
    }
