#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyRespawnBehavior : public GameComponent
{
public:
	static SquallyRespawnBehavior* create(GameObject* owner);

	void respawn(float delay = 1.5f);
	void respawnWithMapReload(float delay = 1.5f);

	static const std::string MapKey;

protected:
	SquallyRespawnBehavior(GameObject* owner);
	virtual ~SquallyRespawnBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void doRespawn();

	bool isRespawning = false;
	bool fullMapReload = false;
	Squally* squally = nullptr;
};
