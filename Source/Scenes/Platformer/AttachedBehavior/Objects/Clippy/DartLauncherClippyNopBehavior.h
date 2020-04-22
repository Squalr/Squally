#pragma once
#include <set>

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;

class DartLauncherClippyNopBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	HackableObject* object;
};
