#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class RupertBehavior : public AttachedBehavior
{
public:
	static RupertBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RupertBehavior(GameObject* owner);
	virtual ~RupertBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
