#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class PhysicsBody;
	class Sprite;
}

class CollisionObject;
class HackableData;

class Dart : public HackableObject
{
public:
	static Dart* create(cocos2d::ValueMap* initProperties);

protected:
	Dart(cocos2d::ValueMap* initProperties);
	~Dart();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;

	void registerHackables();
	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	void dartHeatSeek();
	cocos2d::PhysicsBody* buildCollision();
};
