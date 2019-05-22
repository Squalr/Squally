#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class PhysicsBody;
	class Sprite;
}

class CollisionObject;

class Tent : public HackableObject
{
public:
	static Tent* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTent;

protected:
	Tent(cocos2d::ValueMap& initProperties);
	virtual ~Tent();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	cocos2d::PhysicsBody* createTentTopCollision();

	cocos2d::Sprite* tentBack;
	cocos2d::Sprite* tentFront;
	CollisionObject* topCollision;
	CollisionObject* healCollision;
};
