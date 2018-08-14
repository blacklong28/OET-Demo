#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define DEBUG
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
	char lat[32];
	char lon[32];
	char time[32];
};
/*检测点类型*/
typedef enum {
	CONNECTOR_JOINT,            //中间接头
	EXPAND_JOINT                //膨胀接头
}TrackJointType;
/*检测结果结构体*/
typedef struct {
	int loc_num;                //位置编号
	TrackJointType type;        //检测点类型
	float stand_value;          //标准值
	float measure_value;        //测量值
	string latitude;            //纬度
	string longitude;           //经度
	bool qualified;             //是否合格
}DetectPoint;
vector<celldata> loadData(const char* filename);
int findFunPoint(vector<celldata> vecdata, vector<fun_point> &fun_points);
int handleFunPoint(vector<fun_point>& fun_points);
void sdDetect20(vector<celldata> vecdata);
vector<celldata> cutData(vector<celldata>);

