#pragma once
#include <set>

#include "Engine/Components/GameComponent.h"

class HackableObject;

class PendulumBladeClippyAngleBehavior : public GameComponent
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
	typedef GameComponent super;

	HackableObject* object;
};
