#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyDefaultInventoryBehavior : public AttachedBehavior
{
public:
	static SquallyDefaultInventoryBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyDefaultInventoryBehavior(GameObject* owner);
	virtual ~SquallyDefaultInventoryBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void giveDefaultItems();

	Squally* squally;
};
