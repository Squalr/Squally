#pragma once

#include "Engine/Hackables/HackableObject.h"

class GridObject : public HackableObject
{
public:
	int getGridIndex();
	void setGridIndex(int gridIndex);

protected:
	GridObject(const cocos2d::ValueMap& properties);
	~GridObject();

private:
	typedef HackableObject super;

	int gridIndex;
};
