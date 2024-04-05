#include "big.h"
#include "ecn.h"
#include "zzn.h"
#include <cstring>
#include <iostream>
#define AES_SECURITY 80
#define MR_PAIRING_SSP
#include "pairing_1.h"
using namespace std;
extern "C"
{
#include "miracl.h"
#include "mirdef.h"
}
#pragma comment(lib,"miracl.lib")
int main()
{
	double sum = 0.0;
	for (int i = 0; i < 10000; i++) {
		PFC pfc(AES_SECURITY);
		Big order = pfc.order();
		miracl* mip = get_mip();
		clock_t start, end;
		double time;

		Big  z;
		G1 P,P1;

		pfc.random(P);
		pfc.random(z);

		start = clock();
		P1 = pfc.mult(P, z);	
		end = clock();
		time = double(end - start) / CLOCKS_PER_SEC;
		sum = sum + time;
}
	printf("%lf", sum/10000 );

        return 0;
}
