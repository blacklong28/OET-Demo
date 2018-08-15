// OET-Demo.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sdca.h"

int main()
{
	vector<DetectPoint> Result_Points;//´æ·Å½á¹û
	printf("Demo start!\n");
	vector<CellData> original_data;
	vector<CellData> cut_data;
	int res = loadData("D:\\OET\\data_output_n_ls.txt");
	printf("load end!\n");
	//cut_data=cutData(original_data);
	sdCalculate(Result_Points);
	size_t result_size = Result_Points.size();
	for (size_t i = 0; i < result_size; i++) {
		DetectPoint dp;
		memset(&dp, 0, sizeof(DetectPoint));
		dp = Result_Points.at(i);
		cout << "type:" << dp.type
			<< " num:" << dp.loc_num
			<< " lat:" << dp.latitude
			<< " lon:" << dp.longitude
			<< " stand_value:" << dp.stand_value
			<< " measure_value:" << dp.measure_value
			<< " qualified:" << dp.qualified
			<< endl;
	}
	printf("Demo end!\n");
	//waitKey(0);
	system("pause");
    return 0;
}

