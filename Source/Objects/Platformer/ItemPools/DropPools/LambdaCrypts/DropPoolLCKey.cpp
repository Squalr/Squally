#include "DropPoolLCKey.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

DropPoolLCKey* DropPoolLCKey::create(SampleMethod sampleMethod, int min, int max)
{
	DropPoolLCKey* instance = new DropPoolLCKey(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

DropPoolLCKey::DropPoolLCKey(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "lc-key", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(AncientKey::create(), ItemChance::Probability::Guaranteed));
}

DropPoolLCKey::~DropPoolLCKey()
{
}
