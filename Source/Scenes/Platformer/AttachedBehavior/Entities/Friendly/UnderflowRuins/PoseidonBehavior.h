#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class PoseidonBehavior : public AttachedBehavior
{
public:
	static PoseidonBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	PoseidonBehavior(GameObject* owner);
	virtual ~PoseidonBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
