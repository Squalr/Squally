#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

namespace cocos2d
{
	class Sprite;
}

class MemoryGrid;

class RegisterMarker : public GridObject
{
public:
	void moveToRegister(MemoryGrid* memoryGrid);

protected:
	RegisterMarker();
	~RegisterMarker();

	virtual int getRegisterIndex() = 0;

	cocos2d::Sprite* marker;

private:
	typedef GridObject super;
};
