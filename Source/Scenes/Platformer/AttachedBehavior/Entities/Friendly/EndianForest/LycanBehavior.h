#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class LycanBehavior : public AttachedBehavior
{
public:
	static LycanBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	LycanBehavior(GameObject* owner);
	virtual ~LycanBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;
};
