#pragma once

#include "Engine/Components/Component.h"

class Scrappy;
class Squally;
class PlatformerEntity;

class CurseOfTonguesTutorialBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
