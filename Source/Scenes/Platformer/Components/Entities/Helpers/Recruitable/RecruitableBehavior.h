#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
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

	void displayOptions();

	PlatformerEntity* entity = nullptr;
	Squally* squally = nullptr;
};
