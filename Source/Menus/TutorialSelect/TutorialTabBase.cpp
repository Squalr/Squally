#include "TutorialTabBase.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/TutorialSelect/TutorialEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialTabBase::TutorialTabBase()
{
	this->description = Strings::Common_Constant::create();
	this->descriptionLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->description, Size(640.0f, 0.0f));
	this->entryNode = Node::create();
	this->entries = std::vector<TutorialEntry*>();

	this->createEntry();

	this->descriptionLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->entryNode);
	this->addChild(this->descriptionLabel);
}

TutorialTabBase::~TutorialTabBase()
{
}

void TutorialTabBase::onEnter()
{
	super::onEnter();
}

void TutorialTabBase::initializeListeners()
{
	super::initializeListeners();
}

void TutorialTabBase::initializePositions()
{
	super::initializePositions();

	this->descriptionLabel->setPosition(Vec2(0.0f, 144.0f));
}

TutorialEntry* TutorialTabBase::createEntry()
{
	TutorialEntry* entry = TutorialEntry::create();

	this->entryNode->addChild(entry);
	this->entries.push_back(entry);

	return entry;
}
