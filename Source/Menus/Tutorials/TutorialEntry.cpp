#include "TutorialEntry.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

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
	this->lockedLayer = LayerColor::create(Color4B(0, 0, 0, 127), 144, 144);
	this->content = Node::create();
	this->contentHost = Node::create();
	this->contentClip = SmartClippingNode::create(this->contentHost, 64.0f);
	this->frame = ClickableNode::create(UIResources::Menus_TutorialsMenu_TutorialEntry, UIResources::Menus_TutorialsMenu_TutorialEntrySelected);
	this->lockIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Lock);
	this->completeIcon = Sprite::create(UIResources::Menus_TutorialsMenu_CheckMark);

	this->lockedLayer->setPosition(Vec2(-72.0f, -72.0f));
	
	this->contentHost->addChild(this->content);
	this->contentHost->addChild(this->lockedLayer);
	this->addChild(this->back);
	this->addChild(this->contentClip);
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

	bool unlocked = this->prereq == nullptr || this->prereq->isComplete();

	if (!unlocked)
	{
		this->frame->disableInteraction(255);
	}
	else
	{
		this->frame->enableInteraction(255);
	}
	
	this->lockedLayer->setVisible(!unlocked);
	this->lockIcon->setVisible(!unlocked);
	this->completeIcon->setVisible(this->isComplete());
}

void TutorialEntry::initializeListeners()
{
	super::initializeListeners();
}

void TutorialEntry::initializePositions()
{
	super::initializePositions();

	this->back->setPosition(Vec2(6.0f, -4.0f));
	this->completeIcon->setPosition(Vec2(0.0f, -64.0f));
}

PlatformerEntity* TutorialEntry::addEntity(PlatformerEntity* entity, Vec2 offset)
{
	this->addContent(entity, offset);

	entity->setScale(0.75f);
	entity->setPosition(entity->getPosition() + Vec2(0.0f, -192.0f) + entity->getDialogueOffset());

	return entity;
}

Node* TutorialEntry::addContent(Node* content, Vec2 offset)
{
	this->content->addChild(content);

	this->content->setPosition(offset);

	return content;
}

bool TutorialEntry::isComplete()
{
	return SaveManager::getGlobalDataOrDefault(this->saveKey, Value(false)).asBool();
}

void TutorialEntry::setClickCallback(std::function<void()> clickCallback)
{
	this->frame->setMouseClickCallback([=](MouseEventArgs*)
	{
		if (clickCallback != nullptr)
		{
			clickCallback();
		}
	});
}