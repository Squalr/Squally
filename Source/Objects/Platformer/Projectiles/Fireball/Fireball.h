#pragma once

#include "Objects/Platformer/Projectiles/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;

class Fireball : public ThrownObject
{
public:
	static Fireball* create(PlatformerEntity* owner, PlatformerAttack* attack);

protected:
	Fireball(PlatformerEntity* owner, PlatformerAttack* attack);
	virtual ~Fireball();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	void setFireballSpeed();
};
