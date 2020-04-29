#include "TutorialEntry.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialEntry* TutorialEntry::create(std::string saveKey, TutorialEntry* prereq)
{
	TutorialEntry* instance = new TutorialEntry(saveKey, prereq);

	instance->autorelease();

	return instance;
}

TutorialEntry::TutorialEntry(std::string saveKey, TutorialEntry* prereq)
{
	this->saveKey = saveKey;
	this->prereq = prereq;
	this->back = Sprite::create(UIResources::Menus_TutorialsMenu_TutorialEntryBack);
	this->frame = ClickableNode::create(UIResources::Menus_TutorialsMenu_TutorialEntry, UIResources::Menus_TutorialsMenu_TutorialEntrySelected);
	this->lockIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Lock);
	this->completeIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Diamond);

	this->addChild(this->back);
	this->addChild(this->frame);
	this->addChild(this->lockIcon);
	this->addChild(this->completeIcon);
}

TutorialEntry::~TutorialEntry()
{
}

void TutorialEntry::onEnter()
{
	super::onEnter();

	this->lockIcon->setVisible(this->prereq != nullptr && !this->prereq->isComplete());
	this->completeIcon->setVisible(this->isComplete());
}

void TutorialEntry::initializeListeners()
{
	super::initializeListeners();
}

void TutorialEntry::initializePositions()
{
	super::initializePositions();

	this->back->setPosition(Vec2(8.0f, -4.0f));
}

bool TutorialEntry::isComplete()
{
	return SaveManager::getGlobalDataOrDefault(this->saveKey, Value(false)).asBool();
}

void TutorialEntry::setClickCallback(std::function<void()> clickCallback)
{
	this->frame->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (clickCallback != nullptr)
		{
			clickCallback();
		}
	});
}