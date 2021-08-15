#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class LiftBase : public GameObject
{
public:

protected:
	LiftBase(cocos2d::ValueMap& properties, cocos2d::CSize collisionSize, std::string railArt);
	virtual ~LiftBase();

	enum class MovementDirection
	{
		UpDown,
		LeftRight
	};

	void initializePositions() override;
	void onEnter() override;
	virtual float getPadding();
	virtual cocos2d::Vec2 getRailsOffset();

	float width = 0.0f;
	float height = 0.0f;
	MovementDirection movementDirection = MovementDirection::UpDown;
	cocos2d::Node* railingNode = nullptr;
	cocos2d::Node* liftNode = nullptr;
	CollisionObject* liftCollision = nullptr;

private:
	typedef GameObject super;

	float speedPer256px = 0.0f;
	cocos2d::Sprite* railing = nullptr;

	static const std::string PropertySpeed;
};
