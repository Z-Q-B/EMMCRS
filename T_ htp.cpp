#include "big.h"
#include "ecn.h"
#include "zzn.h"
#include <cstring>
#include <iostream>
#define AES_SECURITY 80
#define MR_PAIRING_SSP
#include "pairing_1.h"
#include <random>
#include <string>
using namespace std;
extern "C"
{
#include "miracl.h"
#include "mirdef.h"
}
#pragma comment(lib,"miracl.lib")

std::string generateRandomString(size_t length) {
	const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	const size_t max_index = (sizeof(charset) - 1); 
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<size_t> distribution(0, max_index - 1);

	std::string random_string;
	for (size_t i = 0; i < length; ++i) {
		random_string += charset[distribution(generator)];
	}

	return random_string;
}

int main() {
    double sum = 0.0;
    double time=0.0;
    for (int i = 0; i < 10000; i++) {
        PFC pfc(AES_SECURITY);
        Big order = pfc.order();
        miracl* mip = get_mip();
        clock_t start, end;
        double time;

        std::string randomText = generateRandomString(12); 
        G1 P;

        start = clock();
        pfc.hash_and_map(P, (char*)randomText.c_str());
        end = clock();
        time = double(end - start) / CLOCKS_PER_SEC;
        sum += time;
    }

    printf("%lf", sum / 10000);

    return 0;
}
