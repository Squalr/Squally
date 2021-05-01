#pragma once

#include "Engine/Components/Component.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;
class Scrappy;

class RopedMovementBehavior : public Component
{
public:
	static RopedMovementBehavior* create(GameObject* owner);

	void detach();

	static const std::string MapKey;

protected:
	RopedMovementBehavior(GameObject* owner);
	virtual ~RopedMovementBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef Component super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	cocos2d::Sprite* waistRope;

	bool isDetached;
};
