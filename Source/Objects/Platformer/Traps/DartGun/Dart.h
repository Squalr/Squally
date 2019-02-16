#pragma once

#include "Engine/Physics/CollisionObject.h"

namespace cocos2d
{
	class PhysicsBody;
	class Sprite;
}

class HackableData;

class Dart : public CollisionObject
{
public:
	static Dart* create(float rotation, float speed);

protected:
	Dart(float rotation, float speed);
	virtual	~Dart();

	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

	cocos2d::Sprite* dartSprite;
};
