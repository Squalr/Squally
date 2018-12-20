#pragma once
#include "cocos2d.h"

#include "Engine/Input/Input.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/NavigationEvents.h"

using namespace cocos2d;

class Squally : public PlatformerEntity
{
public:
	static Squally* deserialize(ValueMap* initProperties);
	static Squally* getInstance();

	Size getSize() override;

	static int health;

	static const std::string MapKeySqually;

protected:
	virtual void initializeCollisionEvents() override;

	Vec2 getButtonOffset() override;

private:
	Squally(ValueMap* initProperties);
	~Squally();

	void registerHackables();
	void onEnter() override;
	void update(float) override;
	void setFlippedX(bool newIsFlipped);

	bool isFlipped;
	bool canJump;

	CollisionObject* squallyCollision;

	static const float squallyScale;
	static Squally* squallyInstance;
};
