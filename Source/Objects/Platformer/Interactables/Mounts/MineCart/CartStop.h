#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class WorldSound;

class CartStop : public GameObject
{
public:
	static CartStop* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CartStop(cocos2d::ValueMap& properties);
	virtual ~CartStop();

private:
	typedef GameObject super;

	CollisionObject* collision;
	cocos2d::Sprite* cartStop;
	WorldSound* colideSound;
};
