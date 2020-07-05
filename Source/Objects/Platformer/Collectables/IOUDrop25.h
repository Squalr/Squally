#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

namespace cocos2d
{
	class Sprite;
}

class WorldSound;

class IOUDrop25 : public Collectable
{
public:
	static IOUDrop25* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	IOUDrop25(cocos2d::ValueMap& properties);
	virtual ~IOUDrop25();

	void initializeListeners() override;

private:
	typedef Collectable super;

	cocos2d::Sprite* iou;

	WorldSound* collectSound;
};
