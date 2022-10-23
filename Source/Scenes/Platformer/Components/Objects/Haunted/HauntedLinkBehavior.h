#pragma once

#include "Engine/Components/GameComponent.h"

class AlchemyLab;
class Anvil;
class PlatformerEntity;
class ShopItem;

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

	PlatformerEntity* linkedEntity = nullptr;
	ShopItem* ownerAsItem = nullptr;
	AlchemyLab* ownerAsAlchemyLab = nullptr;
	Anvil* ownerAsAnvil = nullptr;
	std::string linkedTag;

	static const std::string PropertyLinkedTag;
};
