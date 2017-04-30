#include "patternmatching.h"
//Hashing primes for KR-fingerprints, of size 10^9 so their squares fit in a single long long as well 
//as primes.
long long A=911382323,B=972663749;

/*
Z-algorithm pseudocode from KKKK- Antti Laaksonen. Rest of algorithm pseudocodes from lecture slides by 
Juha Kärkkäinen for course String Processing Algorithms.
*/

//Knuth-Morris-Pratt-algorithm O(n)-time algorithm. Improved version of MP by accouting for previously 
//seen mismatches too.
std::vector<int> PatternMatching::KMP(std::string text, std::string pattern) {
	std::vector<int> matches;
	//construct KMP-automaton
	//simulate
	return matches;
}

//Karp-Rabin hashing using primes A and B as well as rolling hash. Relatively slow O(n)-time algorithm,n=text length.
std::vector<int> PatternMatching::KR(std::string text, std::string pattern) {
	long long patternHash=0,hash=0;
	for (size_t i=0;i<pattern.length();i++) {
		patternHash=((patternHash*A)+pattern[i])%B;
		hash=((hash*A)+text[i])%B;
	}
	long long p=MyMath::modPower(A,pattern.length(),B);
	std::vector<int> matches;
	for (size_t j=0;j<text.length()-pattern.length()+1;j++) {
		if (hash==patternHash) {
			matches.push_back(j);
		}

		hash=hash*A+text[j+pattern.length()];
		hash-=(p*text[j])%B;
		if (hash<0) hash+=B;
		hash%=B;
	}

	return matches;
}

//Morris-Pratt O(n) algorithm, never moves backwards in text and uses fail-function to keep track 
//of longest possible match. Only "remembers" previous matches.
std::vector<int> PatternMatching::MP(std::string text, std::string pattern) {
	std::vector<int> matches;
	int n=(int)text.length();
	int m=(int)pattern.length();
	int fail[m+1];
	int i=-1,j=0;
	fail[0]=-1;
	while(j<m) {
		if (i==-1 || pattern[i]==pattern[j]) {
			i++;j++;fail[j]=i;
		} else {
			i=fail[i];
		}
	}

	i=0;j=0;
	while(j<n) {
		if (i==-1 || text[j]==pattern[i]) {
			i++;j++;
		} else {
			i=fail[i];
		}
		if (i==m) matches.push_back(j-m);
	}
	return matches;
}

//Keeps track of window [x,y] where values have been tested to match [0,y-x]. z-array contains integer z[i] 
//which tells how long prefix matches substring starting from index i.
std::vector<int> PatternMatching::Z(std::string text,std::string pattern) {
	std::vector<int> matches;
	int x=1,y=1,m=(int)pattern.length();
	pattern+="#"+text;
	int n=(int)pattern.length();
	int z[n];
	z[0]=0;
	for (int i=1;i<n;i++) {
		if (z[i-x]+i<y) {
			z[i]=std::min(z[i-x],n-i);
		} else {
			int j=y+1;
			z[i]=0;
			if (pattern[i]==pattern[0]) z[i]++;
			while(j<n && pattern[j-i]==pattern[j]) {
				z[i]++;
				j++;
			}
			y=j;
			x=i;
		}
		if (z[i]==m) matches.push_back(i-m-1);
	}
	return matches;
}