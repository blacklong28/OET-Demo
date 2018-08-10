#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct celldata {
	int num;
	float z1;
	float z2;
	char lat[32];
	char lon[32];
	char time[32];
};
struct fun_point {
	int num;
	int lineID;
	int point_class;//start 1;end 2;
	float sq1;
	float sh1;
	float sq2;
	float sh2;
};
vector<celldata> loadData(const char* filename);
void sdDetect(vector<celldata> vecdata);
void sdDetect20(vector<celldata> vecdata);

