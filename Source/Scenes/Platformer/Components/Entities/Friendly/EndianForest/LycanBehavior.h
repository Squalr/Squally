#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class RewardPoolLycan;
class Scrappy;
class Squally;

class LycanBehavior : public GameComponent
{
public:
	static LycanBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LycanBehavior(GameObject* owner);
	virtual ~LycanBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	RewardPoolLycan* rewardPool = nullptr;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
