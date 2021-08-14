#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class Projectile;
class Squally;
class WorldSound;

class AgroBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Squally* squally = nullptr;
	cocos2d::Sprite* exclamation = nullptr;
	WorldSound* agroBeep = nullptr;

	bool isEnabled = false;
	bool isAgrod = false;
	bool chaseOnAgro = true;
	bool warnOnAgro = true;
	float agroRangeX = 0.0f;
	float agroRangeY = 0.0f;
	float agroRangeZ = 0.0f;
	float engageCooldown = 0.0f;
	float initCooldown = 0.0f;

	static const float AgroRangeX;
	static const float AgroRangeY;
	static const float AgroRangeZ;
	static const float EngageCooldownMax;
};
