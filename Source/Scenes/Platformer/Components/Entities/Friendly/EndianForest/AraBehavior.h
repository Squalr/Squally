#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class AraBehavior : public Component
{
public:
	static AraBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AraBehavior(GameObject* owner);
	virtual ~AraBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
