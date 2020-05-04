#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class Projectile;
class Squally;

class AgroBehavior : public AttachedBehavior
{
public:
	static AgroBehavior* create(GameObject* owner);

	void enable();
	void disable();
	bool hasAgro();
	PlatformerEntity* getAgroTarget();
	void toggleWarnOnAgro(bool warnOnAgro);
	void toggleChaseOnAgro(bool chaseOnAgro);
	void setAgroRangeX(float agroRange);
	void setAgroRangeY(float agroRange);

	static const std::string MapKey;

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
	bool chaseOnAgro;
	bool warnOnAgro;
	float agroRangeX;
	float agroRangeY;
	float agroRangeZ;
	float engageCooldown;

	static const float AgroRangeX;
	static const float AgroRangeY;
	static const float AgroRangeZ;
	static const float EngageCooldownMax;
};
