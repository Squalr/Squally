#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

namespace cocos2d
{
	class Sprite;
}

class WorldSound;

class IOUDrop10 : public Collectable
{
public:
	static IOUDrop10* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	IOUDrop10(cocos2d::ValueMap& properties);
	virtual ~IOUDrop10();

	void initializeListeners() override;

private:
	typedef Collectable super;

	cocos2d::Sprite* iou;

	WorldSound* collectSound;
};
