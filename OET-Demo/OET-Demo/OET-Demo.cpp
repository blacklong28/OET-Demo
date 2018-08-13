// OET-Demo.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sdca.h"

int main()
{
	printf("Demo start!\n");
	vector<celldata> original_data;
	vector<celldata> cut_data;
	original_data = loadData("D:\\OET\\data_output_n_ls.txt");
	printf("load end!\n");
	cut_data=cutData(original_data);
	//printf("core ==%d!\n",res);
	//if (res == 0) {
		sdDetect20(cut_data);
	//}
	
	
	/*
	double param, result;
	param = 5.0;
	result = exp(param);
	printf("The exponential value of %f is %f.\n", param, result);
	*/
	printf("Demo end!\n");
	//waitKey(0);
	system("pause");
    return 0;
}

