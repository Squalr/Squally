#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

namespace cocos2d
{
	class Sprite;
}

class WorldSound;

class IOUDrop : public Collectable
{
public:
	static IOUDrop* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	IOUDrop(cocos2d::ValueMap& properties);
	virtual ~IOUDrop();

	void initializeListeners() override;

private:
	typedef Collectable super;

	cocos2d::Sprite* iou;

	WorldSound* collectSound;
};
