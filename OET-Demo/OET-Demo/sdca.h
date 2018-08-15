#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define DEBUG
using namespace std;

struct CellData {
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
/*错误码*/
typedef enum {
	SUCCESS = 0,    //成功
	LOAD_DATA_ERROR = -1,   //加载数据错误
	SD_CALCULATE_ERROR = -2,   //面差检测错误
	GD_CALCULATE_ERROR = -3,   //间隙检测错误
	GET_TIME_ERROR = -4,    //获取时间错误
	OPEN_DATA_ERROR = -5,	//打开数据文件错误
	UNEXPECTED_ERROR = -99   //其他错误
}error_code;

/**
**面差检测算法内部调用函数
**面差判定函数
**/
int judgmentItem(vector<CellData> vecdata,
	vector<fun_point> &fun_points,
	vector<fun_point> &ex_points, 
	vector<DetectPoint> &resultpoint);
/**
**面差检测算法内部调用函数
**扫描不合格点
**/
int scanOddPoint(vector<CellData> vecdata,
	vector<fun_point> &ex_points, 
	vector<DetectPoint> &resultpoint);

/**
**面差检测算法内部调用函数
**查找兴趣点
**/
int findFunPoint(vector<CellData> vecdata, vector<fun_point> &fun_points);
/**
**面差检测算法内部调用函数
**处理兴趣点
**/
int handleFunPoint(vector<fun_point>& fun_points);

/**
**面差检测算法主函数
**计算面差并返回不合格点
**Result_Points：返回结构体
**conn_stand：中间接头面差标准
**expand_stand：膨胀接头标准
**/
int sdCalculate(vector<DetectPoint>& Result_Points,
	float conn_stand = 0.2, 
	float expand_stand = 0.5, 
	float camera_accuracy = 0.17);

/**数据解析函数
**去除非轨面部分数据
**/
vector<CellData> cutData(vector<CellData>);
/**数据解析函数
**面差检测算法内部调用函数
**/
int loadData(const char* filename);
