#pragma once

#include "Scenes/Platformer/Components/Entities/Collision/EntityWeaponCollisionBehavior.h"

class PlatformerEntity;

class EnemyWeaponCollisionBehavior : public EntityWeaponCollisionBehavior
{
public:
	static EnemyWeaponCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyWeaponCollisionBehavior(GameObject* owner);
	virtual ~EnemyWeaponCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityWeaponCollisionBehavior super;
	
	PlatformerEntity* entity;
};
