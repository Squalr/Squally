#pragma once
#include <set>

#include "Engine/Components/Component.h"

class HackableObject;

class DartLauncherClippyNopBehavior : public Component
{
public:
	static DartLauncherClippyNopBehavior* create(GameObject* owner);

	static const std::string MapKey;
	
protected:
	DartLauncherClippyNopBehavior(GameObject* owner);
	virtual ~DartLauncherClippyNopBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	HackableObject* object;
};
