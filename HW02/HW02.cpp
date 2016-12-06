#include "stdafx.h"
#include "HW02.h"
using namespace std;

Point::Point() :x(0.0), y(0.0) {}//#2 用initialize list初始化
Point::Point(float xco, float yco) : x(xco), y(yco) {}//#3
Point::~Point() {}//#4


//#5
void Point::Set_data(float xData, float yData) {
	x = xData;
	y = yData;
}
//#6 
float Point::operator[](int i)const {
	if (i == 0)//針對引數格式0 1
		return x;
	else if (i == 1)
		return y;
	else {
		cout << "引數錯誤";
		return 0;
	}
}
//#7 
std::istream& operator >> (std::istream& is, Point& point) {
	is >> point.x >> point.y;
	return is;
}
//#8
std::ostream& operator<<(std::ostream& os, const Point& point) {

	os << "(" << point.x << "," << point.y << ")";
	return os;
}


int FindPosition(const Point&, const Point& CenterPoint); //回傳點相對於中心方向  左上 右上 左下 右下 分別對應 0 1 2 3
//#14 三參數建構
QuadtreeNode::QuadtreeNode(const Point& PointData, const Point& CenterPointData, const float BorderLength) : data(&PointData), separate_point(CenterPointData),size(BorderLength) {}

//#15 複製建構
QuadtreeNode::QuadtreeNode(const QuadtreeNode& TreeNode) : separate_point(TreeNode.separate_point), size(TreeNode.size){
	
	data = TreeNode.data; 
	for (int i = 0; i < 4; i++){ //尋訪每個node
		if (TreeNode.nextNode[i] != NULL) //若有資料則複製
			nextNode[i] = new QuadtreeNode(*(TreeNode.nextNode[i]));
		else
			nextNode[i] = NULL;	//沒有就設為null
	}

}

//#16
QuadtreeNode::~QuadtreeNode() {
	//cout << "\n解構在這";
	if (nextNode[0] != NULL){  //尋訪每個node，非null就delete掉
		delete nextNode[0];
		nextNode[0] = NULL;
	}
	if (nextNode[1] != NULL){
		delete nextNode[1];
		nextNode[1] = NULL;
	}
	if (nextNode[2] != NULL){
		delete nextNode[2];
		nextNode[2] = NULL;
	}
	if (nextNode[3] != NULL){
		delete nextNode[3];
		nextNode[3] = NULL;
	}
	
	

}

//#17
bool QuadtreeNode::InsertPoint(const Point& InsertPoint) {

	//QuadtreeNode *newnode = new QuadtreeNode;
	int position = 0;

	position = FindPosition(InsertPoint, separate_point);
	
	if (data != NULL || nextNode[position] == NULL) { //當data不為空，或目標子結點是空的就進入創建
		if (data != NULL){//若data不為空則進入，若data是空的則直接創建					
			if (position == FindPosition(*data, separate_point)){//若當前data在下層的位置與insertpoint相同，表示會連續進入下層空間，此時會覆蓋原本的data值並讓該點消失，所以使用原data值在下層占據一節點
				nextNode[position] = new QuadtreeNode(*data, Point(separate_point[0] + (position % 2 * 2 - 1)*size / 4, separate_point[1] + (position / 2 * -2 + 1)*size / 4), size / 2);
				nextNode[position]->InsertPoint(InsertPoint);
				//data->~Point();
				data = NULL;
				return 0;
			}
			else{
				position = FindPosition(*data, separate_point);
				nextNode[position] = new QuadtreeNode(*data, Point(separate_point[0] + (position % 2 * 2 - 1)*size / 4, separate_point[1] + (position / 2 * -2 + 1)*size / 4), size / 2);
				//data->~Point();
				data = NULL;
			}
		}
		position = FindPosition(InsertPoint, separate_point);
		nextNode[position] = new QuadtreeNode(InsertPoint, Point(separate_point[0] + (position % 2 * 2 - 1)*size / 4, separate_point[1] + (position / 2 * -2 + 1)*size / 4), size / 2);
 		return 0;
	}
	else {	//目標子結點不為空，代表該點在被占據情況下，必須於該節點插入
		position = FindPosition(InsertPoint, separate_point);

		nextNode[position]->InsertPoint(InsertPoint);
	}

	return 0;
}
//#18
const Point* QuadtreeNode::FindClosestPoint(const Point& InsertPoint)const{

	int position = 0;

	position = FindPosition(InsertPoint, separate_point);

	if (nextNode[position] != NULL)//空間不為空時則進入下層尋找，直到找到空為止
		nextNode[position]->FindClosestPoint(InsertPoint);
	else 
		return data;
}

int FindPosition(const Point& InsertPoint, const Point& CenterPoint){//回傳點相對於中心方向  左上 右上 左下 右下 分別對應 0 1 2 3

	int position = 0;

	if (InsertPoint[0]<=CenterPoint[0]){
		if (InsertPoint[1]>=CenterPoint[1])
			position = 0;
		else
			position = 2;
	}
	else{
		if (InsertPoint[1]>=CenterPoint[1])
			position = 1;
		else
			position = 3;
	}

	return position;
}