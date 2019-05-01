#pragma once

#include "Engine/Hackables/HackableObject.h"

class GridObject : public HackableObject
{
public:
	int getGridIndex();
	void setGridIndex(int gridIndex);

protected:
	GridObject(cocos2d::ValueMap& initProperties);
	~GridObject();

private:
	typedef HackableObject super;

	int gridIndex;
};
