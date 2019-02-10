#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject;

class Squally : public PlatformerEntity
{
public:
	static Squally* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeySqually;
	static const int SquallyBaseHealth;
	static const int SquallyBaseSpecial;

protected:
	virtual void initializeCollisionEvents() override;

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerEntity super;
	Squally(cocos2d::ValueMap& initProperties);
	virtual ~Squally();

	void registerHackables();
	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	void setFlippedX(bool newIsFlipped);

	bool isFlipped;
	bool canJump;

	cocos2d::Vec2 squallyCollisionDefaultPosition;
	CollisionObject* squallyCollision;

	static const float squallyScale;
};
