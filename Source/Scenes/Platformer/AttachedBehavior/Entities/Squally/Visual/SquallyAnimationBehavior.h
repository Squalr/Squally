#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;
class SmartAnimationSequenceNode;

class SquallyAnimationBehavior : public AttachedBehavior
{
public:
	static SquallyAnimationBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyAnimationBehavior(GameObject* owner);
	virtual ~SquallyAnimationBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
