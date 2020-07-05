#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

namespace cocos2d
{
	class Sprite;
}

class WorldSound;

class IOUDrop5 : public Collectable
{
public:
	static IOUDrop5* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	IOUDrop5(cocos2d::ValueMap& properties);
	virtual ~IOUDrop5();

	void initializeListeners() override;

private:
	typedef Collectable super;

	cocos2d::Sprite* iou;

	WorldSound* collectSound;
};
