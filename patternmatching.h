#ifndef __PATTERNMATCHING_H_INCLUDED__
#define __PATTERNMATCHING_H_INCLUDED__

#include "mymath.h"
#include <string>
#include <vector>

class PatternMatching {
public:
    static std::vector<int> KMP(std::string text,std::string pattern);
    static std::vector<int> KR(std::string text,std::string pattern);
    static std::vector<int> MP(std::string text,std::string pattern);
    static std::vector<int> Z(std::string text,std::string pattern);
};

#endif