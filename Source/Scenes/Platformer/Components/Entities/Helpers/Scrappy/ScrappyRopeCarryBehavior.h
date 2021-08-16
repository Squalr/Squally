#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;

class ScrappyRopeCarryBehavior : public GameComponent
{
public:
	static ScrappyRopeCarryBehavior* create(GameObject* owner);

	void setCarriedObject(GameObject* target);
	void setRopeHorizontalVelocity(float horizontalVelocity);

	static const std::string MapKey;

protected:
	ScrappyRopeCarryBehavior(GameObject* owner);
	virtual ~ScrappyRopeCarryBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	GameObject* carriedObject = nullptr;
	cocos2d::Sprite* rope = nullptr;
	cocos2d::Sprite* ropeWaist = nullptr;
	float ropeRotation = 0.0f;

	static const float FixedRopeDistance;
};
