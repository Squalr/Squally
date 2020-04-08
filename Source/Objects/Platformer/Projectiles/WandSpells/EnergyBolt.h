#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class SmartAnimationSequenceNode;
class WorldSound;

class EnergyBolt : public Projectile
{
public:
	static EnergyBolt* create();

	void runSpawnFX() override;

protected:
	EnergyBolt();
	virtual ~EnergyBolt();

	void onEnter() override;

private:
	typedef Projectile super;

	WorldSound* energySfx;

	SmartAnimationSequenceNode* energyBolt;
};
