#include "MemoryEditingTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/TutorialSelect/TutorialEntry.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

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
	this->knownValueFloat = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueInt, this->knownValueInt);
	this->unknownValueInt = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueInt, this->knownValueFloat);
	this->unknownValueFloat = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueInt, this->unknownValueInt);
	this->knownValueDouble = this->createEntry(TutorialSaveKeys::SaveKeyKnownValueInt, this->unknownValueFloat);
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

	});
}

void MemoryEditingTab::initializePositions()
{
	super::initializePositions();
}
