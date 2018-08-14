#include "stdafx.h"
//#include <vector>
#include "sdca.h"
#include <math.h>
#include<algorithm>
using namespace std;

float mid_z1=0;
float mid_z2=0;
vector<celldata> loadData(const char* filename){
	vector<celldata> incsv;
	celldata intp;
	FILE *fp;
	fp = fopen(filename,"r");
	char lat_c[32];
	char lon_c[32];
	char time_c[32];
	int i = 0;
	while (1) {
		//fscanf(fp,"%d	%f	%f	%s	%s	%s\n",&intp.num, &intp.z1,&intp.z2, &lat_c, &lon_c, &time_c);
		//intp.lat = lat_c;
		//intp.lon = lon_c;
		//intp.time = time_c;
		//printf("data i=%d\n",i);
		fscanf(fp, "%d	%f	%f	%s	%s	%s\n", &intp.num, &intp.z1, &intp.z2, &intp.lat, &intp.lon, &intp.time);
		intp.num = i;
		incsv.push_back(intp);
		string time;
		time = intp.time;
		//cout << i << " " << incsv[i].z1 << " " << incsv[i].z2 << " " << incsv[i].lat << " " << incsv[i].lon<<" " << incsv[i].time << " " << endl;
		i++;
		if (feof(fp))break;
	}
	fclose(fp);
	return incsv;
}
int findFunPoint(vector<celldata> vecdata, vector<fun_point> &fun_points) {
	vector <celldata> element;
	float sq1 = 0;
	float sq2 = 0;
	float sh1 = 0;
	float sh2 = 0;
	//vector<fun_point> fun_points;//存放初始兴趣点
	fun_point point;//兴趣点

	//查找兴趣点存放于fun_points
	for (int i = 0; i + 19<vecdata.size(); i = i + 10)//size()容器中实际数据个数 
	{
		//cout << vecdata[i].z1 << " " << vecdata[i].z2 << " " << vecdata[i].time << " " << vecdata[i].lat << " " << vecdata[i].lon << endl;
		//copy(vecdata[i], vecdata[i+10], element.begin());
		element.assign(vecdata.begin() + i, vecdata.begin() + i + 20);
		//printf("element debug!\n");
		/*分析element的10组数据*/
		sh1 = 0;
		sh2 = 0;
		for (auto it = element.begin(); it != element.end(); it++) {

			sh1 = sh1 + (*it).z1;
			sh2 = sh2 + (*it).z2;
		}
		sh1 = sh1 / 20;
		sh2 = sh2 / 20;
		/*
		*###sh1-sq1 sh2-sq2：一条线前后差
		*###sq2 - sq1：两条线前差
		*###sh2 - sh1：两条线后差
		*/
		if (i == 0) {
			sq1 = sh1;
			sq2 = sh2;
		}
		else {
			/*
			if ( ((abs(sh1 - sq1) >= 10) ||  (abs(sh2 - sq2) >= 10) ) && (abs(sh2-sh1)>=100) &&  (abs(sq2 - sq1) <= 10) ) {
			printf("Waring i=%d\n", element[1].num);
			printf("sh1=%f,sq1=%f,sh2=%f,sq2=%f\n",sh1,sq1,sh2,sq2);
			}
			*/
			if ((abs(sh1 - sq1) >= 5) && (abs(sh2 - sq2) <= 1) && (abs(sq2 - sq1) < 10) && (abs(sh2 - sh1) > 1)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
#ifdef DEBUG
					printf("start1 i=%d", element[1].num);
#endif
					//start1.push_back(i);
					//findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					strcpy(point.lon, element[1].lon);
					strcpy(point.lat, element[1].lat);
					strcpy(point.time, element[1].time);
					//strncpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//strncpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//strncpy(point.time, element[1].time, strlen(element[1].time + 1));
					//memcpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//memcpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//memcpy(point.time, element[1].time, strlen(element[1].time + 1));
					point.lineID = 1;
					point.point_class = 1;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
#ifdef DEBUG
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
#endif
				}
			}//(abs(sh2 - sh1) < 1) &&   && (abs(sh2 - sh1) < 1)
			else if ((abs(sh1 - sq1) >= 5) && (abs(sh2 - sq2) <= 1) && (abs(sh2 - sh1) < 10) && (abs(sq2 - sq1) > 1)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					/*
					*###sh1-sq1 sh2-sq2：一条线前后差
					*###sq2 - sq1：两条线前差
					*###sh2 - sh1：两条线后差
					*/
					//end1.push_back(i);
					//findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					//point.lon = element[1].lon;
					strcpy(point.lon, element[1].lon);
					strcpy(point.lat, element[1].lat);
					strcpy(point.time, element[1].time);
					//strncpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//strncpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//strncpy(point.time, element[1].time, strlen(element[1].time + 1));
					//memcpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//memcpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//memcpy(point.time, element[1].time, strlen(element[1].time + 1));
					point.lineID = 1;
					point.point_class = 2;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
#ifdef DEBUG
					printf("end1   i=%d", element[1].num);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
#endif
				}
			}
			else if ((abs(sh2 - sq2) >= 5) && (abs(sh1 - sq1) <= 1) && (abs(sq2 - sq1) < 10) && (abs(sh2 - sh1) > 1)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
#ifdef DEBUG
					printf("start2 i=%d", element[1].num);
#endif
					//start2.push_back(i);
					//findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					strcpy(point.lon, element[1].lon);
					strcpy(point.lat, element[1].lat);
					strcpy(point.time, element[1].time);
					//strncpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//strncpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//strncpy(point.time, element[1].time, strlen(element[1].time + 1));
					//memcpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//memcpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//memcpy(point.time, element[1].time, strlen(element[1].time + 1));
					point.lineID = 2;
					point.point_class = 1;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
#ifdef DEBUG
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
#endif
				}

			}
			else if ((abs(sh2 - sq2) >= 5) && (abs(sh1 - sq1) <= 1) && (abs(sq2 - sq1) > 1) && (abs(sh2 - sh1) < 10)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
#ifdef DEBUG
					printf("end2   i=%d", element[1].num);
#endif
					//end2.push_back(i);
					//findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					strcpy(point.lon, element[1].lon);
					strcpy(point.lat, element[1].lat);
					strcpy(point.time, element[1].time);
					//memcpy(point.lon, element[1].lon, strlen(element[1].lon + 1));
					//memcpy(point.lat, element[1].lat, strlen(element[1].lat + 1));
					//memcpy(point.time, element[1].time, strlen(element[1].time + 1));
					point.lineID = 2;
					point.point_class = 2;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
#ifdef DEBUG
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
#endif
				}
			}
			sq1 = sh1;
			sq2 = sh2;

		}

	}
	return 0;
}
int handleFunPoint(vector<fun_point> &fun_points) {
	//情况一：
	for (int i = 0; i + 2<fun_points.size(); i++) {

		if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 && fun_points[i + 2].point_class == 2) {
			//fun_points.erase(fun_points.begin() + i + 1);
			if ((fun_points[i + 1].num - fun_points[i + 2].num) < 300 &&
				fun_points[i].lineID == fun_points[i + 1].lineID&&fun_points[i + 1].lineID == fun_points[i + 2].lineID) {
#ifdef DEBUG
				printf("end-end distance less than 300*0.17mm!!\n");
#endif
				fun_points.erase(fun_points.begin() + i + 1);
			}

		}

	}
	//情况二
	for (int i = 0; i + 2<fun_points.size(); i++) {

		if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 1 && fun_points[i + 2].point_class == 2) {
			//fun_points.erase(fun_points.begin() + i + 1);
			if ((fun_points[i].num - fun_points[i + 1].num) < 300 &&
				fun_points[i].lineID == fun_points[i + 1].lineID&&fun_points[i + 1].lineID == fun_points[i + 2].lineID) {
#ifdef DEBUG
				printf("start-start distance less than 300*0.17mm!!\n");
#endif
				fun_points.erase(fun_points.begin() + i + 1);
			}

		}

	}
	//情况三
	for (int i = 0; i + 1 < fun_points.size(); i++) {

		if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2) {
			if (abs(fun_points[i + 1].num - fun_points[i].num) < 100 &&
				fun_points[i].lineID == fun_points[i + 1].lineID) {
#ifdef DEBUG
				printf("start-end distance less than 100*0.17mm!!\n");
#endif

			}
		}

	}
	return 0;

}
void sdDetect20(vector<celldata> vecdata) {
	if (vecdata.size() < 1) {
		printf("data size error!\n");
		return;
	}
	vector<DetectPoint> Result_Points;//存放结果
	vector<fun_point> ex_points;//存放扫描排除点
	vector<fun_point> fun_points;//存放兴趣点
	//vector<fun_point> fun_points_init;//存放兴趣点
	int err = findFunPoint(vecdata, fun_points);

	/**处理得到的兴趣点
	**NEED UPDATE!!!
	**对各种情况的兴趣点进行分析（前提，数据已去除掉非轨面部分）
	**情况一：数据为start-end-end型
	**情况二：数据为start-start-end型
	**情况三：数据为start-end-start型，不处理 
	**处理的变量：fun_points
	**/
	int res = handleFunPoint(fun_points);

	
	float sdq = 0;//检测项前面深度值
	float sdh = 0;//检测项后面深度值
	//printf("start sd\n");
	for (int i = 0; i < fun_points.size()-1; i++) {
		DetectPoint resultpoint;
		resultpoint.loc_num = i;
		//string lat = fun_points[i].lat;
		//int lat_len = strlen(fun_points[i].lat);
		//lat.resize(10);
		resultpoint.latitude = fun_points[i].lat;
		resultpoint.longitude = fun_points[i].lon;
		//printf("num=%d,lineID=%d,point_class=%d,sq1=%f,sh1=%f,sq2=%f,sh2=%f\n",
		//	fun_points[i].num, fun_points[i].lineID, fun_points[i].point_class, fun_points[i].sq1, fun_points[i].sh1, fun_points[i].sq2, fun_points[i].sh2);
		if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 &&
			fun_points[i].lineID == 2 && fun_points[i + 1].lineID == 2) {

			if (abs(fun_points[i].num - fun_points[i + 1].num) <= 100) {
				for (int j = fun_points[i].num - 151; j + 50 < fun_points[i].num; j++) {
					sdq = sdq + vecdata[j].z2;
				}
				//printf("start cal sdh!\n");
				for (int k = fun_points[i + 1].num + 50; k < fun_points[i + 1].num + 151; k++) {
					sdh = sdh + vecdata[k].z2;
				}
				resultpoint.type = CONNECTOR_JOINT;
				resultpoint.stand_value = 0.2;
			}
			else {
				for (int j = fun_points[i].num - 301; j + 100 < fun_points[i].num; j++) {
					sdq = sdq + vecdata[j].z2;
				}
				//printf("start cal sdh!\n");
				for (int k = fun_points[i + 1].num + 100; k < fun_points[i + 1].num + 301; k++) {
					sdh = sdh + vecdata[k].z2;
				}
				resultpoint.type = EXPAND_JOINT;
				resultpoint.stand_value = 0.5;
			}
			ex_points.push_back(fun_points[i]);
			ex_points.push_back(fun_points[i + 1]);
			i++;
		}
		else if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 &&
				fun_points[i].lineID == 1 && fun_points[i + 1].lineID == 1) {
				//for (int j = fun_points[i].num - 301; j+100 < fun_points[i].num; j++) {
				//	sdq = sdq + vecdata[j].z1;
				//}
				//for (int k = fun_points[i + 1].num+100; k< fun_points[i + 1].num+301; k++) {
				//	sdh = sdh + vecdata[k].z1;
				//}
				if (abs(fun_points[i].num - fun_points[i + 1].num) <= 100) {
					for (int j = fun_points[i].num - 151; j + 50 < fun_points[i].num; j++) {
						sdq = sdq + vecdata[j].z1;
					}
					//printf("start cal sdh!\n");
					for (int k = fun_points[i + 1].num + 50; k< fun_points[i + 1].num + 151; k++) {
						sdh = sdh + vecdata[k].z1;
					}
					resultpoint.type = CONNECTOR_JOINT;
					resultpoint.stand_value = 0.2;
				}
				else {
					for (int j = fun_points[i].num - 301; j + 100 < fun_points[i].num; j++) {
						sdq = sdq + vecdata[j].z1;
					}
					//printf("start cal sdh!\n");
					for (int k = fun_points[i + 1].num + 100; k< fun_points[i + 1].num + 301; k++) {
						sdh = sdh + vecdata[k].z1;
					}
					resultpoint.type = EXPAND_JOINT;
					resultpoint.stand_value = 0.5;
				}
				ex_points.push_back(fun_points[i]);
				ex_points.push_back(fun_points[i + 1]);
				i++;
			}
			if (resultpoint.type == EXPAND_JOINT) {
				sdq = sdq / 200;
				sdh = sdh / 200;
			}
			else {
				sdq = sdq / 100;
				sdh = sdh / 100;
			}

			//resultpoint.type = CONNECTOR_JOINT;
			resultpoint.measure_value = abs(sdq-sdh);
			if (resultpoint.measure_value <= resultpoint.stand_value) {
				resultpoint.qualified = true;
			}
			else {
				resultpoint.qualified = false;
			}
			Result_Points.push_back(resultpoint);
			printf("sdq=%f,sdh=%f,type==%d,measure_value=%f,qualified==%d,lon==%s\n", sdq, sdh,resultpoint.type, resultpoint.measure_value, resultpoint.qualified, resultpoint.longitude.c_str());
			sdq = 0;
			sdh = 0;
		
	}
	//扫描异常点
	//扫描点前100个点均值与后100个点均值的面差
	//计算参数
	//输入参数：ex_points、vecdata、resultpoint指针（引用）
	//输出参数：resultpoint

	float threshold_mean = 0.1;//均值带前后阈值 阈值越大要求前后面相差越大。
	float threshold_variance = 0.125;//均值带方差和阈值 (1/2*threshold_mean)*(1/2*threshold_mean)*sd 阈值越小，要求前后越平整。
	int sd = 50;//均值带
	int ed = 5;//缓冲带

	float sum_z1_q = 0;
	float sum_z1_h = 0;
	float sum_z2_q = 0;
	float sum_z2_h = 0;
	float mean_z1_q = 0;
	float mean_z1_h = 0;
	float mean_z2_q = 0;
	float mean_z2_h = 0;
	float variance_z1_q = 0;
	float variance_z1_h = 0;
	float variance_z2_q = 0;
	float variance_z2_h = 0;
	for (int i=0; i+2<= ex_points.size(); i++) {
		//第一个区域
		if (i ==0) {
			for (int s = sd+ed; s + sd+ed+1 < ex_points[i].num; s=s+20) {
				//float sum = 0;
				sum_z1_q = 0;
				sum_z1_h = 0;
				sum_z2_q = 0;
				sum_z2_h = 0;
				mean_z1_q = 0;
				mean_z1_h = 0;
				mean_z2_q = 0;
				mean_z2_h = 0;
				variance_z1_q = 0;
				variance_z1_h = 0;
				variance_z2_q = 0;
				variance_z2_h = 0;
				for (int c = s-(sd+ed); c < s - ed;c++) {
					sum_z1_q = sum_z1_q + vecdata[c].z1;
					sum_z2_q = sum_z2_q + vecdata[c].z2;
				}
				for (int c = s+ed; c < s + sd+ed; c++) {
					sum_z1_h = sum_z1_h + vecdata[c].z1;
					sum_z2_h = sum_z2_h + vecdata[c].z2;
				}
				mean_z1_q = sum_z1_q / sd;
				mean_z1_h = sum_z1_h / sd;
				mean_z2_q = sum_z2_q / sd;
				mean_z2_h = sum_z2_h / sd;
				if (abs(mean_z1_q - mean_z1_h) >= threshold_mean &&abs(mean_z2_q - mean_z2_h) >= threshold_mean) {
					for (int c = s - (sd+ed); c < s - ed; c++) {
						variance_z1_q = variance_z1_q+pow(abs(vecdata[c].z1- mean_z1_q),2);
						variance_z2_q = variance_z2_q+pow(abs(vecdata[c].z2 - mean_z2_q), 2);
					}
					for (int c = s + ed; c < s + sd+ed; c++) {
						variance_z1_h = variance_z1_h + pow(abs(vecdata[c].z1 - mean_z1_h), 2);
						variance_z2_h = variance_z2_h + pow(abs(vecdata[c].z2 - mean_z2_h), 2);
					}
					if (variance_z1_q < threshold_variance&&variance_z2_q < threshold_variance&&variance_z1_h < threshold_variance&&variance_z2_h < threshold_variance) {
						printf("variance_z1_q=%f,variance_z1_h=%f,variance_z2_q=%f,variance_z2_h=%f\n", variance_z1_q, variance_z1_h, variance_z2_q, variance_z2_h);
						printf("sss==%d\n", s);
					}

					s = s + 199;
				}

			}
		}
		else if (i== ex_points.size()-1) {//最后一个区域
			for (int s = ex_points[i].num+sd+ed; s + sd+ed+1 < vecdata.size()-1; s = s + 20) {
				//float sum = 0;
				sum_z1_q = 0;
				sum_z1_h = 0;
				sum_z2_q = 0;
				sum_z2_h = 0;
				mean_z1_q = 0;
				mean_z1_h = 0;
				mean_z2_q = 0;
				mean_z2_h = 0;
				variance_z1_q = 0;
				variance_z1_h = 0;
				variance_z2_q = 0;
				variance_z2_h = 0;
				for (int c = s - (sd+ed); c < s - ed; c++) {
					sum_z1_q = sum_z1_q + vecdata[c].z1;
					sum_z2_q = sum_z2_q + vecdata[c].z2;
				}
				for (int c = s + ed; c < s + ed+sd; c++) {
					sum_z1_h = sum_z1_h + vecdata[c].z1;
					sum_z2_h = sum_z2_h + vecdata[c].z2;
				}
				mean_z1_q = sum_z1_q / sd;
				mean_z1_h = sum_z1_h / sd;
				mean_z2_q = sum_z2_q / sd;
				mean_z2_h = sum_z2_h / sd;
				if (abs(mean_z1_q - mean_z1_h) >= threshold_mean &&abs(mean_z2_q - mean_z2_h) >= threshold_mean) {
					for (int c = s - (sd+ed); c < s - ed; c++) {
						variance_z1_q = variance_z1_q + pow(abs(vecdata[c].z1 - mean_z1_q), 2);
						variance_z2_q = variance_z2_q + pow(abs(vecdata[c].z2 - mean_z2_q), 2);
					}
					for (int c = s + ed; c < s + ed+sd; c++) {
						variance_z1_h = variance_z1_h + pow(abs(vecdata[c].z1 - mean_z1_h), 2);
						variance_z2_h = variance_z2_h + pow(abs(vecdata[c].z2 - mean_z2_h), 2);
					}
					if (variance_z1_q < threshold_variance&&variance_z2_q < threshold_variance &&variance_z1_h < threshold_variance&&variance_z2_h < threshold_variance) {
						printf("variance_z1_q=%f,variance_z1_h=%f,variance_z2_q=%f,variance_z2_h=%f\n", variance_z1_q, variance_z1_h, variance_z2_q, variance_z2_h);
						printf("sss==%d\n", s);
					}
					s = s + 199;
				}

			}

		}
		else{//其他区域
			for (int s = ex_points[i].num+ed+sd; s + ed+sd+1 < ex_points[i+1].num; s++) {
				sum_z1_q = 0;
				sum_z1_h = 0;
				sum_z2_q = 0;
				sum_z2_h = 0;
				mean_z1_q = 0;
				mean_z1_h = 0;
				mean_z2_q = 0;
				mean_z2_h = 0;
				variance_z1_q = 0;
				variance_z1_h = 0;
				variance_z2_q = 0;
				variance_z2_h = 0;
				for (int c = s - (sd+ed); c < s - ed; c++) {
					sum_z1_q = sum_z1_q + vecdata[c].z1;
					sum_z2_q = sum_z2_q + vecdata[c].z2;
				}
				for (int c = s + ed; c < s + sd+ed; c++) {
					sum_z1_h = sum_z1_h + vecdata[c].z1;
					sum_z2_h = sum_z2_h + vecdata[c].z2;
				}
				mean_z1_q = sum_z1_q / sd;
				mean_z1_h = sum_z1_h / sd;
				mean_z2_q = sum_z2_q / sd;
				mean_z2_h = sum_z2_h / sd;
				if (abs(mean_z1_q - mean_z1_h) >= threshold_mean &&abs(mean_z2_q - mean_z2_h) >= threshold_mean) {
					for (int c = s - (sd+ed); c < s - ed; c++) {
						variance_z1_q = variance_z1_q + pow(abs(vecdata[c].z1 - mean_z1_q), 2);
						variance_z2_q = variance_z2_q + pow(abs(vecdata[c].z2 - mean_z2_q), 2);
					}
					for (int c = s + ed; c < s + ed+sd; c++) {
						variance_z1_h = variance_z1_h + pow(abs(vecdata[c].z1 - mean_z1_h), 2);
						variance_z2_h = variance_z2_h + pow(abs(vecdata[c].z2 - mean_z2_h), 2);
					}
					if (variance_z1_q < threshold_variance&&variance_z2_q < threshold_variance &&variance_z1_h < threshold_variance&&variance_z2_h < threshold_variance) {
						printf("variance_z1_q=%f,variance_z1_h=%f,variance_z2_q=%f,variance_z2_h=%f\n", variance_z1_q, variance_z1_h, variance_z2_q, variance_z2_h);
						printf("sss==%d\n", s);
					}
					s = s + 199;
				}
				
			}
			i++;
		}


	}
}

vector<celldata> cutData(vector<celldata> original_data) {
	//count(original_data);
	vector<float> z1;
	vector<float> z2;
	float mid1;
	float mid2;
	bool needCutStart = false;
	bool needCutEnd = false;
	double startCore = 0;
	int endCore = original_data.size();
	for (vector<celldata>::iterator it = original_data.begin(); it != original_data.end(); it++) {
		z1.push_back(it->z1);
		z2.push_back(it->z2);
	}

	//先判断是否需要掐头去尾
	if (count(z1.begin(), z1.begin() + 500, 0.0) > 100 && count(z2.begin(), z2.begin() + 500, 0.0) > 100) {
		needCutStart = true;
	}
	if (count(z1.end()-500, z1.end(), 0.0) > 100 && count(z2.end()-500, z2.end() , 0.0) > 100) {
		needCutEnd = true;
	}
	//计算中位数mid1、mid2
	sort(z1.begin(), z1.end());
	sort(z2.begin(), z2.end());
#ifdef DEBUG
	printf("z1 mid==%f,z2 mid==%f\n", z1[z1.size() / 2], z2[z2.size() / 2]);
#endif
	if ((z1[z1.size() / 2] - z2[z2.size() / 2]) <= 5) {
		mid1 = z1[z1.size() / 2];
		mid2 = z2[z2.size() / 2];
		mid_z1 = mid1;
		mid_z2 = mid2;
	}
	else {
		//return error;
	}
	//掐头 

	if (needCutStart) {
#ifdef DEBUG
		printf("Need cut start!!\n");
#endif
		int b = 0;
		int core = -1;
		//利用mid计算出dt，标记dt小于波动系数的开始坐标
		for (vector<celldata>::iterator it = original_data.begin(); it != original_data.end(); it++) {

			if (abs(it->z1 - mid1) > 5|| abs(it->z2 - mid2) > 5){
				b = 0;
				core = -1;
			}
			else {
				//printf("b=b+1=%d", b);
				b = b + 1;
				if (b == 1) {
					core = it->num;
				}

			}
			
			if (b == 1000) {
#ifdef DEBUG
				printf("startb=%d\n", core);
#endif
				startCore = core;
				break;
			}
			
		}
	}
	//去尾
	if (needCutEnd) {
#ifdef DEBUG
		printf("Need cut End!!\n");
#endif
		int b = 0;
		int core = -1;
		//利用mid计算出dt，标记dt小于波动系数(默认为5)的结束坐标
		for (vector<celldata>::reverse_iterator it = original_data.rbegin(); it != original_data.rend(); it++) {

			if (abs(it->z1 - mid1) > 5 || abs(it->z2 - mid2) > 5) {
				b = 0;
				core = -1;
			}
			else {
				//printf("b=b+1=%d", b);
				b = b + 1;
				if (b == 1) {
					core = it->num;
				}

			}

			if (b == 1000) {
#ifdef DEBUG
				printf("endb=%d\n", core);
#endif
				endCore = core;
				break;
			}

		}
		//for_each(original_data.begin(), original_data.begin() + original_data.size() / 2, ForDValue(mid));
	}
	vector<celldata> cut_data;
	cut_data.resize(endCore - startCore);
	//(*cutResult.resize(endCore - startCore);
	copy(original_data.begin()+ startCore, original_data.begin()+endCore, cut_data.begin());
	for (int i = 0; i < cut_data.size(); i++) {
		cut_data[i].num = i;
	}
	return cut_data;
}