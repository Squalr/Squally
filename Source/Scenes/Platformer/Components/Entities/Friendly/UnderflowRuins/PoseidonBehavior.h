#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class PoseidonBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
