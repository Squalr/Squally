#pragma once

#include "Engine/Hackables/HackableObject.h"

class GridObject : public HackableObject
{
public:
	int getInitialGridIndex();
	int getGridIndex();
	void setInitialGridIndex(int gridIndex);
	virtual void setGridIndex(int gridIndex);

protected:
	GridObject(const cocos2d::ValueMap& properties);
	virtual ~GridObject();

private:
	typedef HackableObject super;

	int initialGridIndex;
	int gridIndex;
};
