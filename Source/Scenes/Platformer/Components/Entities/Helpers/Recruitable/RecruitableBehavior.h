#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class RecruitableBehavior : public GameComponent
{
public:
	static RecruitableBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RecruitableBehavior(GameObject* owner);
	virtual ~RecruitableBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void updateStateForCurrentHelper(std::string currentHelperName, bool playAnims);

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
