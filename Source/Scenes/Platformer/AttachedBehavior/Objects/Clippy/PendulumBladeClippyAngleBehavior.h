#pragma once
#include <set>

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;

class PendulumBladeClippyAngleBehavior : public AttachedBehavior
{
public:
	static PendulumBladeClippyAngleBehavior* create(GameObject* owner);

	static const std::string MapKey;
	
protected:
	PendulumBladeClippyAngleBehavior(GameObject* owner);
	virtual ~PendulumBladeClippyAngleBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	HackableObject* object;
};
