#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class AlchemyLab;
class Anvil;
class PlatformerEntity;
class ShopItem;

class PetrificationLinkBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* linkedEntity;

	ShopItem* ownerAsItem;
	AlchemyLab* ownerAsAlchemyLab;
	Anvil* ownerAsAnvil;
	std::string linkedTag;

	static const std::string PropertyLinkedTag;
};
