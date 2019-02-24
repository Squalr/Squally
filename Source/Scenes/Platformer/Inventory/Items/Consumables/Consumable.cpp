#include "Consumable.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Consumable::Consumable() : super()
{
}

Consumable::~Consumable()
{
}

PlatformerAttack* Consumable::getAssociatedAttack()
{
	return this->associatedAttack;
}
