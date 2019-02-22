#include "Consumable.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Consumable::Consumable(LocalizedString* name, std::string iconResource) : super(name, iconResource)
{
}

Consumable::~Consumable()
{
}
