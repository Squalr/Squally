#pragma once
#include <set>

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;

class IsSwimmingClippyBehavior : public AttachedBehavior
{
public:
	static IsSwimmingClippyBehavior* create(GameObject* owner);

	static const std::string MapKey;
	
protected:
	IsSwimmingClippyBehavior(GameObject* owner);
	virtual ~IsSwimmingClippyBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	HackableObject* object;
};
