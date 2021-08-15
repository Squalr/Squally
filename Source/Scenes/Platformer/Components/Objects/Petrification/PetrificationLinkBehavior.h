#pragma once

#include "Engine/Components/GameComponent.h"

class AlchemyLab;
class Anvil;
class PlatformerEntity;
class ShopItem;

class PetrificationLinkBehavior : public GameComponent
{
public:
	static PetrificationLinkBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	PetrificationLinkBehavior(GameObject* owner);
	virtual ~PetrificationLinkBehavior();

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
