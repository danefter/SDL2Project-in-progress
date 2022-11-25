#pragma once
#include "ECS.h"

class TransformComponent : public Component
{
private:
	int xpos;
	int ypos;

public:

	TransformComponent()
	{
		xpos = 0;
		ypos = 0;
	}

	TransformComponent(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	//expose and set x and y positions
	int get_x() { return xpos; }
	int get_y() { return ypos; }

	//sets to 0 on instanciation
	void init() override
	{
		xpos = 0;
		ypos = 0;
	}
	//move component
	void update() override
	{
		xpos++;
		ypos++;
	}

	void set_pos(int x, int y)
	{
		xpos = x;
		ypos = y;
	}
};