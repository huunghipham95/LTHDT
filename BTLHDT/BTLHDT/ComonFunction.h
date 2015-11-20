#include <stdio.h>
#include <boost\algorithm\string.hpp>
#include <iostream>
#include <vector>

using namespace std;

class ComonFunction
{
public:
	ComonFunction();
	~ComonFunction();
	static vector<string> string_split_csv(string s);
};

