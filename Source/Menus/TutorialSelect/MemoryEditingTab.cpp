#include "MemoryEditingTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"

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
}

void MemoryEditingTab::initializePositions()
{
	super::initializePositions();
}
