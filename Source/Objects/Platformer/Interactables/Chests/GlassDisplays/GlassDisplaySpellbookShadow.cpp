#include "GlassDisplaySpellbookShadow.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Agnes.h"
#include "Events/DialogueEvents.h"
#include "Events/HexusEvents.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GlassDisplaySpellbookShadow::MapKey = "glass-display-spellbook-shadow";

GlassDisplaySpellbookShadow* GlassDisplaySpellbookShadow::create(cocos2d::ValueMap& properties)
{
	GlassDisplaySpellbookShadow* instance = new GlassDisplaySpellbookShadow(properties);

	instance->autorelease();

	return instance;
}

GlassDisplaySpellbookShadow::GlassDisplaySpellbookShadow(cocos2d::ValueMap& properties) : super(properties, CSize(169.0f, 331.0f))
{
	this->displayContentNode->addChild(Sprite::create(ItemResources::Spellbooks_SpellBookShadow));
}

GlassDisplaySpellbookShadow::~GlassDisplaySpellbookShadow()
{
}

void GlassDisplaySpellbookShadow::onEnter()
{
	super::onEnter();

	this->lock(false);

	ObjectEvents::WatchForObject<Agnes>(this, [=](Agnes* agnes)
	{
		if (!agnes->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->unlock(false);
			this->openDisplay(true);
		}
		else
		{
			agnes->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
			{
				if (!value.asBool())
				{
					this->unlock(false);
					this->openDisplay(true);
				}
			});
		}
	}, Agnes::MapKey);
}

void GlassDisplaySpellbookShadow::initializeListeners()
{
	super::initializeListeners();
}
		
bool GlassDisplaySpellbookShadow::tryOpen()
{
	if (!this->isDisplayOpened)
	{
		return false;
	}

	this->unlockAndGiveItems();

	return true;
}

void GlassDisplaySpellbookShadow::unlockAndGiveItems()
{
	this->open(true);
	
	SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookShadow, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
		Strings::Platformer_Spellbooks_SpellbookShadow::create(),
		ItemResources::Spellbooks_SpellBookShadow,
		SoundResources::Notifications_NotificationGood1
	));

	PlatformerEvents::TriggerUnlockQuickSwap();
}
