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

	void enable();
	void disable();
	void toggleWarnOnAgro(bool warnOnAgro);
	void setAgroRangeX(float agroRange);
	void setAgroRangeY(float agroRange);

	static const std::string MapKeyAttachedBehavior;

protected:
	AgroBehavior(GameObject* owner);
	virtual ~AgroBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;
	cocos2d::Sprite* exclamation;

	bool isEnabled;
	bool isAgrod;
	bool warnOnAgro;
	float agroRangeX;
	float agroRangeY;
	float engageCooldown;

	static const float AgroRangeX;
	static const float AgroRangeY;
	static const float EngageCooldownMax;
};
