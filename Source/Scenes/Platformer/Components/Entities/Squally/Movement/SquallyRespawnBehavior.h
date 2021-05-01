#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyRespawnBehavior : public Component
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
	typedef Component super;
	
	void respawn(float delay);
	void doRespawn();

	bool isRespawning;

	Squally* squally;
};
