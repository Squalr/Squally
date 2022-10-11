#pragma once
#include <set>

#include "Engine/Components/GameComponent.h"

class HackableObject;

class IsSwimmingClippyBehavior : public GameComponent
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
	typedef GameComponent super;

	HackableObject* object = nullptr;
};
