// HW02.cpp : �w�q�D���x���ε{�����i�J�I�C
//�@��:��ߦ��\�j�Ǿ���� ������ N16054598

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
	

	//�U��Ū��

	cout << "²���D����:\n#4 point���Ѻc�A�]����@�S��new����Ŷ�\n\n\n\n";

	fin.open(filename, ios::in);
	for (int i = 0; getline(fin, temp, '\n'); i++){ //�r��B�z���I���I�ӼƱN�I���X�s�ipoint
		//cout << endl << temp << "\t" << temp.length();
		if (i == 0){
			TotalPoint = stoi(temp.substr(temp.find(":")+1, 2));
			
			PointArray = new Point[TotalPoint];

			fin >> PointArray[i];
			continue;
		}

		fin >> PointArray[i];//���տ�J�B��l	
	}
	fin.close();

	cout << "\n�}�C�Ҧ����e:";
	for (int i = 0; i < 20; i++)
		cout <<endl <<PointArray[i];//���տ�X�B��l




	//�ΰ}�C�Ĥ@�ӭȫغc
	QuadtreeNode OriginTree(PointArray[0], Point(0, 0), 200);
	Point PointInput;
	//��Linsert�i�h
	for (int i = 1; i < 20; i++)
		OriginTree.InsertPoint(PointArray[i]);


	QuadtreeNode AnotherTree(OriginTree);
	cout << "\n��J�I�y��:";
	if (cin >> PointInput){
		cout << "�q�𤤧�X��closetpoint: " << fixed << setprecision(2)<< *(OriginTree.FindClosestPoint(PointInput)) << endl;
		cout << "���սƻs�غc�q�ƻs�𤤧�X��closetpoint: "<< fixed << setprecision(2)  << *(AnotherTree.FindClosestPoint(PointInput)) << endl;
	}
	else
		cout << "��J���~�{������" << endl;


	//�Ѻc�l����
	OriginTree.~QuadtreeNode();
	AnotherTree.~QuadtreeNode();
	


	delete[] PointArray;
	PointArray = NULL;

	
	_CrtDumpMemoryLeaks();
	system("pause");
    return 0;
}

