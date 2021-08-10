#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class AraBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
