#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyManaBehavior : public AttachedBehavior
{
public:
	static SquallyManaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyManaBehavior(GameObject* owner);
	virtual ~SquallyManaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();

	Squally* squally;
};
