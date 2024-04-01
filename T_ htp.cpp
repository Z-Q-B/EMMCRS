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

		char a='123';
		G1 P;

		start = clock();
		pfc.hash_and_map(P,&a);
		end = clock();
		time = double(end - start) / CLOCKS_PER_SEC;
		sum = sum + time;
}
	printf("%lf", sum/10000 );