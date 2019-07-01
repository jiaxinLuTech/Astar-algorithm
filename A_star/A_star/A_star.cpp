#include "A_star.h"
#include <iostream>
#include <algorithm>
using namespace std;
void A_star::Map::addCollision(Point coordinates)//添加墙
{
	walls.push_back(coordinates);
}

void A_star::Map::removeCollision(Point coordinates)//删除墙
{
	vector<Point>::iterator it = walls.begin();
	while(it != walls.end())
	{
		if (coordinates.x == (*it).x && coordinates.y == (*it).y)
		{
			walls.erase(it);
		}
		it++;
	}
}

void A_star::Map::clearCollisions()//清除墙
{
	walls.clear();
}

A_star::Point A_star::Map::getDelta(Point source, Point target)
{
	return{ abs(source.x - target.x),  abs(source.y - target.y) };
}

int A_star::Map::manhattan(Point source, Point target)//曼哈顿距离
{
	//auto delta = std::move(getDelta(source, target));//以非常简单的方式将左值引用转换为右值引用，不懂为什么这么做
	Point delta = getDelta(source, target);
	return static_cast<int>(10 * (delta.x + delta.y));
}

bool A_star::Map::Detect_collision(Point coordinates)//是否是墙
{
	if (coordinates.x >= 0 && coordinates.x <= size_.x &&
		coordinates.y >= 0 && coordinates.y <= size_.y)
	{
		vector<Point>::iterator it = walls.begin();
		while (it != walls.end())
		{
			if (coordinates.x == (*it).x && coordinates.y == (*it).y)
			{
				return true;
			}
			it++;
		}
		return false;
	}
	else
	return true;
}

void A_star::Map::releaseNodes(vector<Node*> nodes)//移除节点
{
	for (auto it = nodes.begin(); it != nodes.end();) {
		delete *it;
		it = nodes.erase(it);
	}
}

A_star::Node* A_star::Map::findNodeOnList(vector<Node*> nodes, Point coordinates)//判断是否 在列表中
{
	for (auto node : nodes) {
		//Point s = node->coordinates_;
		if (node->coordinates_.x == coordinates.x && node->coordinates_.y == coordinates.y) {
			return node;
		}
	}
	return nullptr;
}

vector<A_star::Point> A_star::Map::findPath(Point source, Point target)//寻路
{
	vector<Point> path;
	if(Detect_collision(source) || Detect_collision(target))//判断起点和终点是否是墙
	{
		cout << "please input orgin and target again" << endl;
		return path;
	}
	Node *current = nullptr;
	vector<A_star::Node*> openSet, closedSet;
	openSet.push_back(new Node(source));

	while (!openSet.empty()) {
		current = *openSet.begin();
		for (auto node : openSet) {
			if (node->Get_score() <= current->Get_score()) {
				current = node;
			}
		}

		if (current->coordinates_.x == target.x && current->coordinates_.y == target.y) {
			break;
		}

		closedSet.push_back(current);
		openSet.erase(std::find(openSet.begin(), openSet.end(), current));

		for (int i = 0; i < directions; ++i) {
			Point newCoordinates((current->coordinates_.x + current->direction[i].x),(current->coordinates_.y + current->direction[i].y));
			if (Detect_collision(newCoordinates) ||
				findNodeOnList(closedSet, newCoordinates)) {//判断墙和是否在关闭队列里面
				continue;
			}

			int totalCost = current->G + ((i < 4) ? 10 : 14);

			Node *successor = findNodeOnList(openSet, newCoordinates);
			if (successor == nullptr) {//不在开队列里面
				successor = new Node(newCoordinates, current);
				successor->G = totalCost;
				successor->H = manhattan(successor->coordinates_, target);
				openSet.push_back(successor);
			}
			else if (totalCost < successor->G) {//已经在开队列里了
				successor->parent_ = current;
				successor->G = totalCost;
			}
		}
	}
	
	while (current != nullptr) {
		path.push_back(current->coordinates_);
		current = current->parent_;
	}

	releaseNodes(openSet);
	releaseNodes(closedSet);

	return path;
}