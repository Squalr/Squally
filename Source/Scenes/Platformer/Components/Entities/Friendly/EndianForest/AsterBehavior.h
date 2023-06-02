#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class AsterBehavior : public GameComponent
{
public:
	static AsterBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	AsterBehavior(GameObject* owner);
	virtual ~AsterBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
