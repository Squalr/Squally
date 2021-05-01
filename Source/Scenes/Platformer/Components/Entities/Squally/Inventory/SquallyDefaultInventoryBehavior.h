#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyDefaultInventoryBehavior : public Component
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
	typedef Component super;
	
	void giveDefaultItems();

	Squally* squally;

	static bool GiveDeveloperItems;
};
