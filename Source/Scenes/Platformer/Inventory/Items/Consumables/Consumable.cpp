#include "Consumable.h"

#include "Engine/Inventory/Inventory.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

#include "Resources/ItemResources.h"

using namespace cocos2d;

Consumable::Consumable(CurrencyInventory* cost, ItemMeta itemMeta) : super(cost, itemMeta)
{
	this->associatedAttack = nullptr;
}

Consumable::~Consumable()
{
}

PlatformerAttack* Consumable::cloneAssociatedAttack(PlatformerEntity* entity)
{
	PlatformerAttack* attack = this->cloneAssociatedAttack();

	this->bindItemUseCallback(attack, entity);

	return attack;
}

PlatformerAttack* Consumable::getAssociatedAttack(PlatformerEntity* entity)
{
	PlatformerAttack* attack = this->getAssociatedAttack();

	this->bindItemUseCallback(attack, entity);

	return attack;
}

PlatformerAttack* Consumable::cloneAssociatedAttack()
{
	PlatformerAttack* attack = this->getAssociatedAttack();

	return attack == nullptr ? nullptr : attack->clone();
}

PlatformerAttack* Consumable::getAssociatedAttack()
{
	if (this->associatedAttack == nullptr)
	{
		this->associatedAttack = this->createAssociatedAttack();

		if (this->associatedAttack != nullptr)
		{
			this->addChild(this->associatedAttack);
		}
	}

	return this->associatedAttack;
}

void Consumable::bindItemUseCallback(PlatformerAttack* attack, PlatformerEntity* entity)
{
	if (attack == nullptr)
	{
		return;
	}

	attack->registerAttackCompleteCallback([=]()
	{
		entity->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
		{
			Inventory* inventory = entityInventoryBehavior->getInventory();
			
			if (inventory == nullptr)
			{
				return;
			}

			inventory->tryRemove(this);
		});
	});
}
