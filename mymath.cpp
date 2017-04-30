#include "mymath.h"

long long MyMath::power(long long a, long long b) {
	if (b==0) return 1;
	long long ret=power(a,b/2);
	ret*=ret;
	if (b%2) ret*=a;
	return ret;
}

long long MyMath::modPower(long long a, long long b, long long mod) {
	if (b==0) return 1;
	long long ret=modPower(a,b/2,mod);
	ret=(ret*ret)%mod;
	if (b%2) ret=(ret*a)%mod;
	return ret;
}
