#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class LycanBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
