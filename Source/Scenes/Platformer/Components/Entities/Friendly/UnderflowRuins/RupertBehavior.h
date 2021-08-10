#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class RupertBehavior : public GameComponent
{
public:
	static RupertBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RupertBehavior(GameObject* owner);
	virtual ~RupertBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
