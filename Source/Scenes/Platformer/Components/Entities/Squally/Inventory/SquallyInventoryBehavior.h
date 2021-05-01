#pragma once

#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

class Squally;

class SquallyInventoryBehavior : public EntityInventoryBehavior
{
public:
	static SquallyInventoryBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyInventoryBehavior(GameObject* owner);
	virtual ~SquallyInventoryBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityInventoryBehavior super;
	
	void saveState();

	Squally* squally;
};
