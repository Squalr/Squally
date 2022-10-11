#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class PoseidonBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
