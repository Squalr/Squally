#include "RubyBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/RubyBomb/ThrowRubyBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RubyBomb::SaveKey = "ruby-bomb";
const int RubyBomb::DamageMin = 70;
const int RubyBomb::DamageMax = 75;

RubyBomb* RubyBomb::create()
{
	RubyBomb* instance = new RubyBomb();

	instance->autorelease();

	return instance;
}

RubyBomb::RubyBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 75 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

RubyBomb::~RubyBomb()
{
}

bool RubyBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

Item* RubyBomb::clone()
{
	return RubyBomb::create();
}

LocalizedString* RubyBomb::getString()
{
	return Strings::Items_Consumables_Combat_RubyBomb::create();
}

const std::string& RubyBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T7_RubyBomb;
}

const std::string& RubyBomb::getIdentifier()
{
	return RubyBomb::SaveKey;
}

PlatformerAttack* RubyBomb::createAssociatedAttack()
{
	return ThrowRubyBomb::create(PlatformerAttack::Priority::Common);
}
