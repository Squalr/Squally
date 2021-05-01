#pragma once
#include <set>

#include "Engine/Components/Component.h"

class HackableObject;

class PendulumBladeClippyAngleBehavior : public Component
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
	typedef Component super;

	HackableObject* object;
};
