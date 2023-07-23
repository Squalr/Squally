#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class RewardPoolLycan;
class Scrappy;
class Squally;

class DrakBehavior : public GameComponent
{
public:
	static DrakBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DrakBehavior(GameObject* owner);
	virtual ~DrakBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void setPostText();

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
