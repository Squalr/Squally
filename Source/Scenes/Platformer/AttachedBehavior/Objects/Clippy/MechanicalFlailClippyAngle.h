#pragma once
#include <set>

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;

class MechanicalFlailClippyAngle : public AttachedBehavior
{
public:
	static MechanicalFlailClippyAngle* create(GameObject* owner);

	static const std::string MapKey;
	
protected:
	MechanicalFlailClippyAngle(GameObject* owner);
	virtual ~MechanicalFlailClippyAngle();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	HackableObject* object;
};
