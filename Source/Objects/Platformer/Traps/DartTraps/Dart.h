#pragma once

#include "Engine/Physics/CollisionObject.h"

namespace cocos2d
{
	class Sprite;
}

class Dart : public CollisionObject
{
public:
	static Dart* create(float rotation, float speed, float visualRotation);

protected:
	Dart(float rotation, float speed, float visualRotation);
	~Dart();

private:
	typedef CollisionObject super;

	bool enabled;
	cocos2d::Sprite* dartSprite;
};
