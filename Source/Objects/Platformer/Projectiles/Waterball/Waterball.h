#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class CollisionObject;
class SmartAnimationSequenceNode;

class Waterball : public Projectile
{
public:
	static Waterball* create(float waterballRotation, float speed);

	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	Waterball(float waterballRotation, float speed);
	virtual ~Waterball();

	void onEnter() override;

private:
	typedef Projectile super;

	SmartAnimationSequenceNode* waterballAnim = nullptr;
	float waterballSpeed = 0.0f;
};
