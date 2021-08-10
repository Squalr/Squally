#pragma once
#include <set>

#include "Engine/Components/GameComponent.h"

class HackableObject;

class MechanicalFlailClippyAngleBehavior : public GameComponent
{
public:
	static MechanicalFlailClippyAngleBehavior* create(GameObject* owner);

	static const std::string MapKey;
	
protected:
	MechanicalFlailClippyAngleBehavior(GameObject* owner);
	virtual ~MechanicalFlailClippyAngleBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	HackableObject* object;
};
