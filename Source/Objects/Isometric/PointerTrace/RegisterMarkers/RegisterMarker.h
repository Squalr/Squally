#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class LocalizedString;
class MemoryGrid;

class RegisterMarker : public GridObject
{
public:
	void moveToRegister(MemoryGrid* memoryGrid);

protected:
	RegisterMarker();
	~RegisterMarker();

	virtual int getRegisterIndex() = 0;
	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

	cocos2d::Sprite* marker;
	LocalizedString* registerString;

private:
	typedef GridObject super;
	LocalizedLabel* registerLabel;
};
