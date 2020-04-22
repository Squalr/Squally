#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyRespawnBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;
	
	void respawn(float delay);

	bool isRespawning;

	Squally* squally;
};
