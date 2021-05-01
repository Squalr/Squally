#pragma once
#include <set>

#include "Engine/Components/Component.h"

class HackableObject;

class IsSwimmingClippyBehavior : public Component
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
	typedef Component super;

	HackableObject* object;
};
