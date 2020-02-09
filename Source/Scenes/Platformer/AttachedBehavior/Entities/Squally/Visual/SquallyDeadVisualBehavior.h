#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;
class SmartAnimationSequenceNode;

class SquallyDeadVisualBehavior : public AttachedBehavior
{
public:
	static SquallyDeadVisualBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyDeadVisualBehavior(GameObject* owner);
	virtual ~SquallyDeadVisualBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
