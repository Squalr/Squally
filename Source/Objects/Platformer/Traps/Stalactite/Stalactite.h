#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class Stalactite : public GameObject
{
public:
	static Stalactite* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Stalactite(cocos2d::ValueMap& properties);
	virtual ~Stalactite();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

private:
	typedef GameObject super;

	void applyGravity(float dt);

	bool isFalling;

	cocos2d::Sprite* sprite;
	CollisionObject* collision;
};
