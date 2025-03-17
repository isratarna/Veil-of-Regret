#pragma once
class Pos
{
public:
	int x, y;
	Pos(int x, int y) : x(x), y(y) {}
	~Pos() = default;
	void setX(int x)
	{
		this->x = x;
	}
	void setY(int y)
	{
		this->y = y;
	}
	int getX() { return x; }
	int getY() { return y; }
};