#include "Consumable.h"

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Consumable::Consumable(CurrencyInventory* cost) : super(cost)
{
}

Consumable::~Consumable()
{
}

PlatformerAttack* Consumable::cloneAssociatedAttack()
{
	return this->getAssociatedAttack()->clone();
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
