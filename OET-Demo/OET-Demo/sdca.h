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
/*������*/
typedef enum {
	SUCCESS = 0,    //�ɹ�
	LOAD_DATA_ERROR = -1,   //�������ݴ���
	SD_CALCULATE_ERROR = -2,   //��������
	GD_CALCULATE_ERROR = -3,   //��϶������
	GET_TIME_ERROR = -4,    //��ȡʱ�����
	OPEN_DATA_ERROR = -5,	//�������ļ�����
	UNEXPECTED_ERROR = -99   //��������
}error_code;

/**
**������㷨�ڲ����ú���
**����ж�����
**/
int judgmentItem(vector<CellData> vecdata,
	vector<fun_point> &fun_points,
	vector<fun_point> &ex_points, 
	vector<DetectPoint> &resultpoint);
/**
**������㷨�ڲ����ú���
**ɨ�費�ϸ��
**/
int scanOddPoint(vector<CellData> vecdata,
	vector<fun_point> &ex_points, 
	vector<DetectPoint> &resultpoint);

/**
**������㷨�ڲ����ú���
**������Ȥ��
**/
int findFunPoint(vector<CellData> vecdata, vector<fun_point> &fun_points);
/**
**������㷨�ڲ����ú���
**������Ȥ��
**/
int handleFunPoint(vector<fun_point>& fun_points);

/**
**������㷨������
**���������ز��ϸ��
**Result_Points�����ؽṹ��
**conn_stand���м��ͷ����׼
**expand_stand�����ͽ�ͷ��׼
**/
int sdCalculate(vector<DetectPoint>& Result_Points,
	float conn_stand = 0.2, 
	float expand_stand = 0.5, 
	float camera_accuracy = 0.17);

/**���ݽ�������
**ȥ���ǹ��沿������
**/
vector<CellData> cutData(vector<CellData>);
/**���ݽ�������
**������㷨�ڲ����ú���
**/
int loadData(const char* filename);
