#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class Squally;

class AgroBehavior : public AttachedBehavior
{
public:
	static AgroBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	AgroBehavior(GameObject* owner);
	~AgroBehavior();

	void initializePositions() override;
	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;
	cocos2d::Sprite* exclamation;

	bool isAgrod;
	float engageCooldown;

	static const float AgroRangeX;
	static const float AgroRangeY;
	static const float EngageCooldownMax;
};
