// HW02.cpp : 定義主控台應用程式的進入點。
//作者:國立成功大學機械所 陳紀融 N16054598

#include "stdafx.h"
#include "HW02.h"
#include <fstream>
#include <string>
#include <stdlib.h>  
#include <crtdbg.h>  
#include <iomanip>
#define _CRTDBG_MAP_ALLOC  
using namespace std;

int main()
{
	const char* filename = "Point_HW2.txt";
	fstream fin;
	string temp;
	int TotalPoint = 0;
	Point* PointArray=0;
	

	//下方讀檔

	cout << "簡答題答案:\n#4 point的解構，因為實作沒有new任何空間\n\n\n\n";

	fin.open(filename, ios::in);
	for (int i = 0; getline(fin, temp, '\n'); i++){ //字串處理取點及點個數將點取出存進point
		//cout << endl << temp << "\t" << temp.length();
		if (i == 0){
			TotalPoint = stoi(temp.substr(temp.find(":")+1, 2));
			
			PointArray = new Point[TotalPoint];

			fin >> PointArray[i];
			continue;
		}

		fin >> PointArray[i];//測試輸入運算子	
	}
	fin.close();

	cout << "\n陣列所有內容:";
	for (int i = 0; i < 20; i++)
		cout <<endl <<PointArray[i];//測試輸出運算子




	//用陣列第一個值建構
	QuadtreeNode OriginTree(PointArray[0], Point(0, 0), 200);
	Point PointInput;
	//其他insert進去
	for (int i = 1; i < 20; i++)
		OriginTree.InsertPoint(PointArray[i]);


	QuadtreeNode AnotherTree(OriginTree);
	cout << "\n輸入點座標:";
	if (cin >> PointInput){
		cout << "從樹中找出的closetpoint: " << fixed << setprecision(2)<< *(OriginTree.FindClosestPoint(PointInput)) << endl;
		cout << "測試複製建構從複製樹中找出的closetpoint: "<< fixed << setprecision(2)  << *(AnotherTree.FindClosestPoint(PointInput)) << endl;
	}
	else
		cout << "輸入錯誤程式結束" << endl;


	//解構子測試
	OriginTree.~QuadtreeNode();
	AnotherTree.~QuadtreeNode();
	


	delete[] PointArray;
	PointArray = NULL;

	
	_CrtDumpMemoryLeaks();
	system("pause");
    return 0;
}

