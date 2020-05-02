#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
};

class CollisionObject;

class FloatTutorialPortal : public Portal
{
public:
	static FloatTutorialPortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	FloatTutorialPortal(cocos2d::ValueMap& properties);
	virtual ~FloatTutorialPortal();
	
	void loadMap() override;

private:
	typedef Portal super;
};
