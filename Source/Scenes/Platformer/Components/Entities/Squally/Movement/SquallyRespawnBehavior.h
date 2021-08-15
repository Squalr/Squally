#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyRespawnBehavior : public GameComponent
{
public:
	static SquallyRespawnBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyRespawnBehavior(GameObject* owner);
	virtual ~SquallyRespawnBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void respawn(float delay);
	void doRespawn();

	bool isRespawning = false;
	Squally* squally = nullptr;
};
