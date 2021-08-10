#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyDefaultInventoryBehavior : public GameComponent
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
	typedef GameComponent super;
	
	void giveDefaultItems();

	Squally* squally = nullptr;

	static bool GiveDeveloperItems;
};
