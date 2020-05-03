#include "HexEditingTab.h"

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
#include "Entities/Platformer/Special/Shopkeeper.h"
#include "Menus/Tutorials/HexusStoreMenu.h"
#include "Menus/Tutorials/TutorialEntry.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HexEditingTab* HexEditingTab::create()
{
	HexEditingTab* instance = new HexEditingTab();

	instance->autorelease();

	return instance;
}

HexEditingTab::HexEditingTab()
{
	this->hexEditingGold = this->createEntry(TutorialSaveKeys::SaveKeyHexEditGold);

	ValueMap properties = ValueMap();
	this->shopkeeper = this->hexEditingGold->addEntity(Shopkeeper::deserialize(properties), Vec2(-24.0f, 32.0f));

	this->shopkeeper->setScale(0.65f);
}

HexEditingTab::~HexEditingTab()
{
}

void HexEditingTab::onEnter()
{
	super::onEnter();
}

void HexEditingTab::initializeListeners()
{
	super::initializeListeners();

	this->hexEditingGold->setClickCallback([=]()
	{
		this->loadHexEditingGoldTutorial();
	});
}

void HexEditingTab::initializePositions()
{
	super::initializePositions();
}

void HexEditingTab::loadHexEditingGoldTutorial()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return HexusStoreMenu::getInstance(); }));
}
