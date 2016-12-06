#include "stdafx.h"
#include "HW02.h"
using namespace std;

Point::Point() :x(0.0), y(0.0) {}//#2 ��initialize list��l��
Point::Point(float xco, float yco) : x(xco), y(yco) {}//#3
Point::~Point() {}//#4


//#5
void Point::Set_data(float xData, float yData) {
	x = xData;
	y = yData;
}
//#6 
float Point::operator[](int i)const {
	if (i == 0)//�w��޼Ʈ榡0 1
		return x;
	else if (i == 1)
		return y;
	else {
		cout << "�޼ƿ��~";
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


int FindPosition(const Point&, const Point& CenterPoint); //�^���I�۹�󤤤ߤ�V  ���W �k�W ���U �k�U ���O���� 0 1 2 3
//#14 �T�Ѽƫغc
QuadtreeNode::QuadtreeNode(const Point& PointData, const Point& CenterPointData, const float BorderLength) : data(&PointData), separate_point(CenterPointData),size(BorderLength) {}

//#15 �ƻs�غc
QuadtreeNode::QuadtreeNode(const QuadtreeNode& TreeNode) : separate_point(TreeNode.separate_point), size(TreeNode.size){
	
	data = TreeNode.data; 
	for (int i = 0; i < 4; i++){ //�M�X�C��node
		if (TreeNode.nextNode[i] != NULL) //�Y����ƫh�ƻs
			nextNode[i] = new QuadtreeNode(*(TreeNode.nextNode[i]));
		else
			nextNode[i] = NULL;	//�S���N�]��null
	}

}

//#16
QuadtreeNode::~QuadtreeNode() {
	//cout << "\n�Ѻc�b�o";
	if (nextNode[0] != NULL){  //�M�X�C��node�A�Dnull�Ndelete��
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
	
	if (data != NULL || nextNode[position] == NULL) { //��data�����šA�ΥؼФl���I�O�Ū��N�i�J�Ы�
		if (data != NULL){//�Ydata�����ūh�i�J�A�Ydata�O�Ū��h�����Ы�					
			if (position == FindPosition(*data, separate_point)){//�Y��edata�b�U�h����m�Pinsertpoint�ۦP�A��ܷ|�s��i�J�U�h�Ŷ��A���ɷ|�л\�쥻��data�Ȩ������I�����A�ҥH�ϥέ�data�Ȧb�U�h�e�ڤ@�`�I
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
	else {	//�ؼФl���I�����šA�N����I�b�Q�e�ڱ��p�U�A������Ӹ`�I���J
		position = FindPosition(InsertPoint, separate_point);

		nextNode[position]->InsertPoint(InsertPoint);
	}

	return 0;
}
//#18
const Point* QuadtreeNode::FindClosestPoint(const Point& InsertPoint)const{

	int position = 0;

	position = FindPosition(InsertPoint, separate_point);

	if (nextNode[position] != NULL)//�Ŷ������Ůɫh�i�J�U�h�M��A������Ŭ���
		nextNode[position]->FindClosestPoint(InsertPoint);
	else 
		return data;
}

int FindPosition(const Point& InsertPoint, const Point& CenterPoint){//�^���I�۹�󤤤ߤ�V  ���W �k�W ���U �k�U ���O���� 0 1 2 3

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