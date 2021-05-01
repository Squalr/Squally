#pragma once

#include "Engine/Components/Component.h"

class Inventory;
class Portal;

class LockedPortal : public Component
{
public:
	static LockedPortal* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string PropertyItemRequired;
	static const std::string SaveKeyItemPresented;

protected:
	LockedPortal(GameObject* owner);
	virtual ~LockedPortal();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void checkForRequiredItem();

	Portal* portal;
	Inventory* playerInventory;
	std::string requiredItemName;
};
