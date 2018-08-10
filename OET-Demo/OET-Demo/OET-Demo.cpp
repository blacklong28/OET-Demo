// OET-Demo.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sdca.h"

int main()
{
	printf("Demo start!\n");
	vector<celldata> mdata;
	mdata = loadData("D:\\OET\\data_output_n_w.txt");
	printf("load end!\n");
	sdDetect20(mdata);
	
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

