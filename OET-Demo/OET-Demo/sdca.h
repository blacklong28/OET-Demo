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
/*��������*/
typedef enum {
	CONNECTOR_JOINT,            //�м��ͷ
	EXPAND_JOINT                //���ͽ�ͷ
}TrackJointType;
/*������ṹ��*/
typedef struct {
	int loc_num;                //λ�ñ��
	TrackJointType type;        //��������
	float stand_value;          //��׼ֵ
	float measure_value;        //����ֵ
	string latitude;            //γ��
	string longitude;           //����
	bool qualified;             //�Ƿ�ϸ�
}DetectPoint;
vector<celldata> loadData(const char* filename);
int findFunPoint(vector<celldata> vecdata, vector<fun_point> &fun_points);
int handleFunPoint(vector<fun_point>& fun_points);
void sdDetect20(vector<celldata> vecdata);
vector<celldata> cutData(vector<celldata>);

