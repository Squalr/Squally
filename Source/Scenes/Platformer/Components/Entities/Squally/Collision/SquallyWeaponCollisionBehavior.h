#pragma once

#include "Scenes/Platformer/Components/Entities/Collision/EntityWeaponCollisionBehavior.h"

class Squally;
class WorldSound;

class SquallyWeaponCollisionBehavior : public EntityWeaponCollisionBehavior
{
public:
	static SquallyWeaponCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyWeaponCollisionBehavior(GameObject* owner);
	virtual ~SquallyWeaponCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityWeaponCollisionBehavior super;

	void onWeaponChange();

	bool canEngage = true;
	Squally* squally = nullptr;
	WorldSound* impactSound = nullptr;
};
