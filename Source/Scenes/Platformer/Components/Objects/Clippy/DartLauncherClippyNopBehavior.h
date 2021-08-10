#pragma once
#include <set>

#include "Engine/Components/GameComponent.h"

class HackableObject;

class DartLauncherClippyNopBehavior : public GameComponent
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
	typedef GameComponent super;

	HackableObject* object;
};
