#include "stdafx.h"
//#include <vector>
#include "sdca.h"
#include <math.h>

vector<celldata> incsv;
vector<celldata> loadData(const char* filename){
	
	celldata intp;
	FILE *fp;
	fp = fopen(filename,"r");
	int i = 0;
	while (1) {
		fscanf(fp,"%d	%f	%f	%s	%s	%s\n",&intp.num, &intp.z1,&intp.z2,&intp.lat, &intp.lon,&intp.time);
		
		//printf("data i=%d\n",i);
		intp.num = i;
		incsv.push_back(intp);
		//cout << i << " " << incsv[i].z1 << " " << incsv[i].z2 << " " << incsv[i].lat << " " << incsv[i].lon<<" " << incsv[i].time << " " << endl;
		i++;
		if (feof(fp))break;
	}
	fclose(fp);
	return incsv;
}

void sdDetect(vector<celldata> vecdata) {
	if (vecdata.size() < 1) {
		printf("data size error!\n");
		return;
	}
	vector <celldata> element;
	float sq1 = 0;
	float sq2 = 0;
	float sh1 = 0;
	float sh2 = 0;
	vector<int> start1;
	vector<int> end1;
	vector<int> start2;
	vector<int> end2;

	vector<int> check_start1;
	vector<int> check_end1;
	vector<int> check_start2;
	vector<int> check_end2;


	vector<int> findTP;
	vector<fun_point> fun_points;
	vector<fun_point> start;
	vector<fun_point> end;
	//vector<fun_point,fun_point> fun_regions;
	fun_point point;
	for (int i = 0; i+9<vecdata.size(); i=i+5)//size()容器中实际数据个数 
	{
		//cout << vecdata[i].z1 << " " << vecdata[i].z2 << " " << vecdata[i].time << " " << vecdata[i].lat << " " << vecdata[i].lon << endl;
		//copy(vecdata[i], vecdata[i+10], element.begin());
		element.assign(vecdata.begin()+i, vecdata.begin()+i+10);
		//printf("element debug!\n");
		/*分析element的10组数据*/
		//
		//
		//for(i=1,i<)
		sh1 = 0;
		sh2 = 0;
		for (auto it = element.begin(); it != element.end(); it++) {

			sh1 = sh1+(*it).z1;
			sh2 = sh2 + (*it).z2;
		}
		sh1 = sh1 / 10;
		sh2 = sh2 / 10;
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
			if ( (abs(sh1 - sq1) >= 5) && (abs(sh2 - sq2) <= 1) && (abs(sq2 - sq1) < 10) && (abs(sh2 - sh1) > 1) ){
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					printf("start1 i=%d", element[1].num);
					//start1.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 1;
					point.point_class = 1;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);

					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}
			}//(abs(sh2 - sh1) < 1) &&   && (abs(sh2 - sh1) < 1)
			else if ( (abs(sh1 - sq1) >= 5) && (abs(sh2 - sq2) <= 1) && (abs(sh2 - sh1) < 10) && (abs(sq2 - sq1) > 1) ) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					/*
					*###sh1-sq1 sh2-sq2：一条线前后差
					*###sq2 - sq1：两条线前差
					*###sh2 - sh1：两条线后差
					*/
					//end1.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 1;
					point.point_class = 2;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);

					printf("end1   i=%d", element[1].num);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}
			}
			else if( (abs(sh2 - sq2) >= 5) && (abs(sh1 - sq1) <= 1) && (abs(sq2 - sq1) < 10) && (abs(sh2 - sh1) > 1)){
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					printf("start2 i=%d", element[1].num);
					//start2.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 2;
					point.point_class = 1;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}

			}
			else if ((abs(sh2 - sq2) >= 5) && (abs(sh1 - sq1) <= 1) && (abs(sq2 - sq1) > 1) && (abs(sh2 - sh1) < 10)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					printf("end2   i=%d", element[1].num);
					//end2.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 2;
					point.point_class = 2;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}
			}
			sq1 = sh1;
			sq2 = sh2;

		}

		}
		int k = 1;
		printf("debug\n");
		for (int i = 0; i+2<fun_points.size(); i++) {
			//各种情况分析（前提，数据已经去除掉非轨面部分）
			//情况一：数据开头就为end，此情况需要
			//情况二：数据开头为start，下一个为同一条线的end，这种情况需要分析区间均值、区间宽度
			//若再下一个也为end，需要分析两个的sh，若后一个更接近start的sq，则将下一个end点去除。
			//情况三：数据开头为start，下一个为其他线的end
			if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 && fun_points[i + 2].point_class == 2) {
				fun_points.erase(fun_points.begin() + i+1);
				k++;
			//	i = i + 1;
				//printf(" num=%d\n", fun_regions[k], sh1, sq2, sh2);
			}
			else if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 && fun_points[i + 2].point_class == 1) {

				k++;
			}

		
		
		}
		for (int i = 0; i < fun_points.size(); i++) {
			printf("num=%d,lineID=%d,point_class=%d,sq1=%f,sh1=%f,sq2=%f,sh2=%f\n",
				fun_points[i].num, fun_points[i].lineID, fun_points[i].point_class, fun_points[i].sq1, fun_points[i].sh1, fun_points[i].sq2, fun_points[i].sh2);
		}

}
void sdDetect20(vector<celldata> vecdata) {
	if (vecdata.size() < 1) {
		printf("data size error!\n");
		return;
	}
	vector <celldata> element;
	float sq1 = 0;
	float sq2 = 0;
	float sh1 = 0;
	float sh2 = 0;
	vector<int> start1;
	vector<int> end1;
	vector<int> start2;
	vector<int> end2;

	vector<int> check_start1;
	vector<int> check_end1;
	vector<int> check_start2;
	vector<int> check_end2;


	vector<int> findTP;
	vector<fun_point> fun_points;
	vector<fun_point> start;
	vector<fun_point> end;
	//vector<fun_point,fun_point> fun_regions;
	fun_point point;
	for (int i = 0; i + 19<vecdata.size(); i = i + 10)//size()容器中实际数据个数 
	{
		//cout << vecdata[i].z1 << " " << vecdata[i].z2 << " " << vecdata[i].time << " " << vecdata[i].lat << " " << vecdata[i].lon << endl;
		//copy(vecdata[i], vecdata[i+10], element.begin());
		element.assign(vecdata.begin() + i, vecdata.begin() + i + 20);
		//printf("element debug!\n");
		/*分析element的10组数据*/
		//
		//
		//for(i=1,i<)
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
					printf("start1 i=%d", element[1].num);
					//start1.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 1;
					point.point_class = 1;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);

					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
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
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 1;
					point.point_class = 2;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);

					printf("end1   i=%d", element[1].num);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}
			}
			else if ((abs(sh2 - sq2) >= 5) && (abs(sh1 - sq1) <= 1) && (abs(sq2 - sq1) < 10) && (abs(sh2 - sh1) > 1)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					printf("start2 i=%d", element[1].num);
					//start2.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 2;
					point.point_class = 1;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}

			}
			else if ((abs(sh2 - sq2) >= 5) && (abs(sh1 - sq1) <= 1) && (abs(sq2 - sq1) > 1) && (abs(sh2 - sh1) < 10)) {
				if ((sh1 + sh2 + sq1 + sq2) >= 950) {
					printf("end2   i=%d", element[1].num);
					//end2.push_back(i);
					findTP.push_back(i);
					//存入兴趣点
					point.num = element[1].num;
					point.lineID = 2;
					point.point_class = 2;
					point.sh1 = sh1;
					point.sq1 = sq1;
					point.sh2 = sh2;
					point.sq2 = sq2;
					fun_points.push_back(point);
					printf(" sq1=%f,sh1=%f,sq2=%f,sh2=%f\n", sq1, sh1, sq2, sh2);
				}
			}
			sq1 = sh1;
			sq2 = sh2;

		}

	}
	int k = 1;
	printf("debug\n");
	for (int i = 0; i + 2<fun_points.size(); i++) {
		//各种情况分析（前提，数据已经去除掉非轨面部分）
		//情况一：数据开头就为end，此情况需要
		//情况二：数据开头为start，下一个为同一条线的end，这种情况需要分析区间均值、区间宽度
		//若再下一个也为end，需要分析两个的sh，若后一个更接近start的sq，则将下一个end点去除。
		//情况三：数据开头为start，下一个为其他线的end
		if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 && fun_points[i + 2].point_class == 2) {
			fun_points.erase(fun_points.begin() + i + 1);
			k++;
			//	i = i + 1;
			//printf(" num=%d\n", fun_regions[k], sh1, sq2, sh2);
		}
		else if (fun_points[i].point_class == 1 && fun_points[i + 1].point_class == 2 && fun_points[i + 2].point_class == 1) {

			k++;
		}



	}
	float sdq = 0;
	float sdh = 0;
	//printf("start sd\n");
	for (int i = 0; i < fun_points.size()-1; i++) {
		//printf("num=%d,lineID=%d,point_class=%d,sq1=%f,sh1=%f,sq2=%f,sh2=%f\n",
		//	fun_points[i].num, fun_points[i].lineID, fun_points[i].point_class, fun_points[i].sq1, fun_points[i].sh1, fun_points[i].sq2, fun_points[i].sh2);
		if (fun_points[i].point_class == 1&& fun_points[i+1].point_class==2) {
			if (fun_points[i].lineID == 2 && fun_points[i + 1].lineID == 2) {
				for (int j = fun_points[i].num - 301; j+100 < fun_points[i].num; j++) {
					sdq = sdq + vecdata[j].z2;
				}
				//printf("start cal sdh!\n");
				for (int k = fun_points[i + 1].num+100; k< fun_points[i + 1].num+301; k++) {
					sdh = sdh + vecdata[k].z2;
				}
			}
			else if (fun_points[i].lineID == 1 && fun_points[i + 1].lineID == 1) {
				for (int j = fun_points[i].num - 301; j+100 < fun_points[i].num; j++) {
					sdq = sdq + vecdata[j].z1;
				}
				for (int k = fun_points[i + 1].num+100; k< fun_points[i + 1].num+301; k++) {
					sdh = sdh + vecdata[k].z1;
				}
				
			}

			sdq = sdq / 200;
			sdh = sdh / 200;
			printf("sdq==%f,sdh==%f\n",sdq,sdh);
			sdq = 0;
			sdh = 0;
			
		}
	}
	//计算面差
	//start前100个点均值与end后100个点面差
	//两组面差值相近才有效

	
}