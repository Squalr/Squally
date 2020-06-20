#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;
class Scrappy;

class RopedMovementBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	cocos2d::Sprite* waistRope;

	bool isDetached;
};
