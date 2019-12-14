#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class TempleGreenDoor : public Portal
{
public:
	static TempleGreenDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTempleGreenDoor;

protected:
	TempleGreenDoor(cocos2d::ValueMap& properties);
	virtual ~TempleGreenDoor();

	void initializePositions() override;

private:
	typedef Portal super;

	cocos2d::Sprite* door;
};
