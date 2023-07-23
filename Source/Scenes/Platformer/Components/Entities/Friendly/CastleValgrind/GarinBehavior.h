#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class RewardPoolLycan;
class Scrappy;
class Squally;

class GarinBehavior : public GameComponent
{
public:
	static GarinBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GarinBehavior(GameObject* owner);
	virtual ~GarinBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void setPostText();

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
