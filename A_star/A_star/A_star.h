#pragma once
#include <vector>
using namespace std;
namespace A_star
{
	struct Point
	{
		int x, y;
		Point(int x_ = 0, int y_ = 0) { x = x_; y = y_; };
	};
	struct Node
	{
		int G, H;
		Point coordinates_;
		Node *parent_;
		vector<Point> direction = {
			{-1,0},{1,0},{0,-1},{0,1},
			{-1,-1},{-1,1},{1,-1},{1,1}
		};

		Node(Point coordinates, Node *parent = nullptr)
		{
			coordinates_.x = coordinates.x;
			coordinates_.y = coordinates.y;

			parent_ = parent;
			G = 0;
			H = 0;
		};
		int Get_score() { return G + H; };

	};
	class Map
	{
	public:
	vector<Node*> NodeSet;
	vector<Point> walls;
	Point size_;
	int directions;

	void Set_diag_move(bool enable) { directions = (enable ? 8 : 4); };

	void Set_size(Point size) { size_ = size; };
	void addCollision(Point coordinates);
	void removeCollision(Point coordinates);
	void clearCollisions();

	void releaseNodes(vector<Node*> nodes);
	Node* findNodeOnList(vector<Node*> nodes_, Point coordinates_);
	Point getDelta(Point source, Point target);

	int manhattan(Point source, Point target);

	bool Detect_collision(Point coordinates);

	vector<A_star::Point> findPath(Point source, Point target);

	};
	


};
