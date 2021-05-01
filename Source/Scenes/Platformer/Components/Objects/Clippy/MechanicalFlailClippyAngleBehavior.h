#pragma once
#include <set>

#include "Engine/Components/Component.h"

class HackableObject;

class MechanicalFlailClippyAngleBehavior : public Component
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
	typedef Component super;

	HackableObject* object;
};
