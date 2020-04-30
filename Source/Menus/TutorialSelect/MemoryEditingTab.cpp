#include "MemoryEditingTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Menus/TutorialSelect/TutorialEntry.h"
#include "Menus/TutorialSelect/TutorialSelectMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

MemoryEditingTab* MemoryEditingTab::create()
{
	MemoryEditingTab* instance = new MemoryEditingTab();

	instance->autorelease();

	return instance;
}

MemoryEditingTab::MemoryEditingTab()
{
	this->knownValueInt = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueInt);
	this->knownValueFloat = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueFloat, this->knownValueInt);
	this->unknownValueInt = this->createEntry(TutorialSaveKeys::SaveKeyUnknownValueInt, this->knownValueFloat);
	this->unknownValueFloat = this->createEntry(TutorialSaveKeys::SaveKeyUnknownValueFloat, this->unknownValueInt);
	this->knownValueDouble = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueDouble, this->unknownValueFloat);
}

MemoryEditingTab::~MemoryEditingTab()
{
}

void MemoryEditingTab::onEnter()
{
	super::onEnter();
}

void MemoryEditingTab::initializeListeners()
{
	super::initializeListeners();

	this->knownValueInt->setClickCallback([=]()
	{
		this->loadKnownValueIntTutorial();
	});

	this->knownValueFloat->setClickCallback([=]()
	{
		this->loadKnownValueFloatTutorial();
	});

	this->unknownValueInt->setClickCallback([=]()
	{
		this->loadUnknownValueIntTutorial();
	});

	this->unknownValueFloat->setClickCallback([=]()
	{
		this->loadUnknownValueFloatTutorial();
	});

	this->knownValueDouble->setClickCallback([=]()
	{
		this->loadKnownValueDoubleTutorial();
	});
}

void MemoryEditingTab::initializePositions()
{
	super::initializePositions();
}

void MemoryEditingTab::loadKnownValueIntTutorial()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		const int UNUSED_SAVE_PROFILE = 99;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
		
		PlatformerMap* map = PlatformerMap::create(MapResources::Tutorials_KnownValueInt32);

		return map;
	}));
}

void MemoryEditingTab::loadKnownValueFloatTutorial()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		const int UNUSED_SAVE_PROFILE = 99;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
		
		PlatformerMap* map = PlatformerMap::create(MapResources::Tutorials_KnownValueFloat);

		return map;
	}));
}

void MemoryEditingTab::loadUnknownValueIntTutorial()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		const int UNUSED_SAVE_PROFILE = 99;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
		
		PlatformerMap* map = PlatformerMap::create(MapResources::Tutorials_UnknownValueInt32);

		return map;
	}));
}

void MemoryEditingTab::loadUnknownValueFloatTutorial()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		const int UNUSED_SAVE_PROFILE = 99;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
		
		PlatformerMap* map = PlatformerMap::create(MapResources::Tutorials_UnknownValueFloat);

		return map;
	}));
}

void MemoryEditingTab::loadKnownValueDoubleTutorial()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		const int UNUSED_SAVE_PROFILE = 99;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
		
		PlatformerMap* map = PlatformerMap::create(MapResources::Tutorials_KnownValueDouble);

		return map;
	}));
}
