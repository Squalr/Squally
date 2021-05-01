#pragma once

#include "Engine/Components/Component.h"

class AlchemyLab;
class Anvil;
class PlatformerEntity;
class ShopItem;

class PetrificationLinkBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* linkedEntity;

	ShopItem* ownerAsItem;
	AlchemyLab* ownerAsAlchemyLab;
	Anvil* ownerAsAnvil;
	std::string linkedTag;

	static const std::string PropertyLinkedTag;
};
