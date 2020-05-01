#include "TutorialTabBase.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Tutorials/TutorialEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialTabBase::TutorialTabBase()
{
	this->description = Strings::Common_Empty::create();
	this->descriptionLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->description, Size(640.0f, 0.0f));
	this->entryNode = Node::create();
	this->entries = std::vector<TutorialEntry*>();

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
	this->entryNode->setPosition(Vec2(0.0f, -48.0f + 0.0f));

	const float SpacingX = 256.0f;
	const float SpacingY = 212.0f;
	
	for (int index = 0; index < int(this->entries.size()); index++)
	{
		TutorialEntry* next = this->entries[index];
		int xIndex = index % 3;
		int yIndex = index / 3;

		next->setPosition(Vec2(float(xIndex - 1) * SpacingX, -float(yIndex - 1) * SpacingY));
	}
}

TutorialEntry* TutorialTabBase::createEntry(std::string saveKey, TutorialEntry* prereq)
{
	TutorialEntry* entry = TutorialEntry::create(saveKey, prereq);

	this->entryNode->addChild(entry);
	this->entries.push_back(entry);

	return entry;
}
