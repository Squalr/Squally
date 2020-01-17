#pragma once

#include "Engine/Hackables/HackableObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;

class Fireball : public HackableObject
{
public:
	static Fireball* create(PlatformerEntity* owner, PlatformerAttack* attack);

	ThrownObject* getProjectile();

protected:
	Fireball(PlatformerEntity* owner, PlatformerAttack* attack);
	virtual ~Fireball();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void setFireballSpeed();

	ThrownObject* fireball;
};
