#pragma once

#include "Engine/Components/GameComponent.h"

class AlchemyLab;
class Anvil;
class PlatformerEntity;
class ShopItem;
class SmeltingPot;

class HauntedLinkBehavior : public GameComponent
{
public:
	static HauntedLinkBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	HauntedLinkBehavior(GameObject* owner);
	virtual ~HauntedLinkBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void activateAll();

	PlatformerEntity* linkedEntity = nullptr;
	ShopItem* ownerAsItem = nullptr;
	AlchemyLab* ownerAsAlchemyLab = nullptr;
	Anvil* ownerAsAnvil = nullptr;
	SmeltingPot* ownerAsSmeltingPot = nullptr;
	std::string linkedTag;

	static const std::string PropertyLinkedTag;
};
