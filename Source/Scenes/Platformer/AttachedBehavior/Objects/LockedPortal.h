#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Inventory;
class Portal;

class LockedPortal : public AttachedBehavior
{
public:
	static LockedPortal* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;
	static const std::string MapKeyPropertyItemRequired;

protected:
	LockedPortal(GameObject* owner);
	virtual ~LockedPortal();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void checkForRequiredItem();

	Portal* portal;
	Inventory* playerInventory;
	std::string requiredItemName;
};
