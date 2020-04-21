#pragma once
#include <set>

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;

class MechanicalFlailClippyAngleBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	HackableObject* object;
};
