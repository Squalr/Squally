#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyReceiveItemBehavior : public AttachedBehavior
{
public:
	static SquallyReceiveItemBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyReceiveItemBehavior(GameObject* owner);
	virtual ~SquallyReceiveItemBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
