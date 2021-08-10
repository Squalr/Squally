#pragma once

#include "Engine/Components/GameComponent.h"

class Scrappy;
class Squally;
class PlatformerEntity;

class CurseOfTonguesTutorialBehavior : public GameComponent
{
public:
	static CurseOfTonguesTutorialBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CurseOfTonguesTutorialBehavior(GameObject* owner);
	virtual ~CurseOfTonguesTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
