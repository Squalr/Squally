#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;
class SmartAnimationSequenceNode;

class SquallyMouthBehavior : public AttachedBehavior
{
public:
	static SquallyMouthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyMouthBehavior(GameObject* owner);
	virtual ~SquallyMouthBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
