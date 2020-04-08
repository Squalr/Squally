#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class SmartAnimationSequenceNode;

class EnergyBolt : public Projectile
{
public:
	static EnergyBolt* create();

protected:
	EnergyBolt();
	virtual ~EnergyBolt();

	void onEnter() override;

private:
	typedef Projectile super;

	SmartAnimationSequenceNode* energyBolt;
};
