#ifndef HW01_02_H
#define HW01_02_H

#include <iostream>
class Point//宣告point
{
private: //#1
	float x;
	float y;
public:
	Point();//#2
	Point(float, float);//#3
	~Point();//#4
	void Set_data(float, float);//#5
	float operator[](int i)const;//#6
	friend std::istream& operator >> (std::istream&, Point&);//#7
	friend std::ostream& operator <<(std::ostream&, const Point&);//#8
};

class QuadtreeNode//宣告treenode
{
private:
	const Point* data; //#9
	QuadtreeNode* nextNode[4]; //#10
	const Point separate_point; //#11
	const float size;//#12
public:
	QuadtreeNode()=delete;//#13
	QuadtreeNode(const Point&, const Point&, const float);//#14
	QuadtreeNode(const QuadtreeNode&);//#15
	~QuadtreeNode();//#16
	bool InsertPoint(const Point&);//#17 插入節點
	const Point* FindClosestPoint(const Point&)const;//#18 尋找最近節點
};

#endif 