#pragma once
#include <set>

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;

class PendulumBladeClippyAngle : public AttachedBehavior
{
public:
	static PendulumBladeClippyAngle* create(GameObject* owner);

	static const std::string MapKey;
	
protected:
	PendulumBladeClippyAngle(GameObject* owner);
	virtual ~PendulumBladeClippyAngle();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	HackableObject* object;
};
