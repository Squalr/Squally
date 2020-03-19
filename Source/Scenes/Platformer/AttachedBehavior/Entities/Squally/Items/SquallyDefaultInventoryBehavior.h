#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyDefaultInventoryBehavior : public AttachedBehavior
{
public:
	static SquallyDefaultInventoryBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyDefaultInventoryBehavior(GameObject* owner);
	virtual ~SquallyDefaultInventoryBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;
	
	void giveDefaultItems();

	Squally* squally;
};
