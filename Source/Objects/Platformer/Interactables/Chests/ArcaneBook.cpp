#include "ArcaneBook.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Save/SaveManager.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArcaneBook::MapKey = "arcane-book";

ArcaneBook* ArcaneBook::create(ValueMap& properties)
{
	ArcaneBook* instance = new ArcaneBook(properties);

	instance->autorelease();

	return instance;
}

ArcaneBook::ArcaneBook(ValueMap& properties) : super(properties, CSize(128.0f, 112.0f))
{
	Sprite* arcaneBookSprite = Sprite::create("TODO");

	this->chestClosed->addChild(arcaneBookSprite);
}

ArcaneBook::~ArcaneBook()
{
}

void ArcaneBook::onEnter()
{
	super::onEnter();
	
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookArcane, Value(false)).asBool())
	{
		this->disable();
	}
}

bool ArcaneBook::tryOpen()
{
	// Instead of giving items, grant the spellbook
	this->broadcastMapEvent(this->getSendEvent(), ValueMap());
	SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookArcane, Value(true));
	Objectives::SetCurrentObjective(ObjectiveKeys::CVExploreSecretTunnel);
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
		Strings::Platformer_Spellbooks_SpellbookOfArcane::create(),
		ItemResources::Spellbooks_SpellBookArcane,
		SoundResources::Notifications_NotificationGood1
	));

	return true;
}
