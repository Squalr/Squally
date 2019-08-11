#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyManaBehavior : public AttachedBehavior
{
public:
	static SquallyManaBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyManaBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyManaBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();

	Squally* squally;
};
