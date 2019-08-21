#include "CipherStateVictory.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Platformer/Combat/Rewards.h"
#include "Strings/Menus/Okay.h"

using namespace cocos2d;

CipherStateVictory* CipherStateVictory::create()
{
	CipherStateVictory* instance = new CipherStateVictory();

	instance->autorelease();

	return instance;
}

CipherStateVictory::CipherStateVictory() : super(CipherState::StateType::Victory)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->rewardsMenu = Sprite::create(UIResources::Combat_VictoryMenu);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Platformer_Combat_Rewards::create());
	this->rewardsScroll = ScrollPane::create(Size(480.0f, 640.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->activeCipherState = nullptr;

	LocalizedLabel*	okayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Okay::create());
	LocalizedLabel*	okayLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Okay::create());

	this->okayButton = ClickableTextNode::create(okayLabel, okayLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	this->titleLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->backdrop);
	this->addChild(this->rewardsMenu);
	this->addChild(this->titleLabel);
	this->addChild(this->rewardsScroll);
	this->addChild(this->okayButton);
}

CipherStateVictory::~CipherStateVictory()
{
}

void CipherStateVictory::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void CipherStateVictory::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backdrop->setPosition(Vec2(-visibleSize.width / 2.0f, -visibleSize.height / 2.0f));
	this->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->titleLabel->setPositionY(392.0f);
	this->okayButton->setPositionY(-392.0f);
}

void CipherStateVictory::initializeListeners()
{
	super::initializeListeners();

	this->okayButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				CipherState::updateState(this->activeCipherState, CipherState::StateType::GameEnd);
				CipherEvents::TriggerExitCipher(CipherEvents::CipherExitArgs(true));
			}),
			nullptr
		));
	});
}

void CipherStateVictory::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateVictory::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	this->activeCipherState = cipherState;

	this->giveRewards(cipherState);

	this->setVisible(true);
}

void CipherStateVictory::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateVictory::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);

	this->setVisible(false);
}

void CipherStateVictory::giveRewards(CipherState* cipherState)
{
	int index = 0;

	std::vector<std::string> rewards = cipherState->puzzleData->getRewards();
	std::vector<std::string> bonusRewards = cipherState->puzzleData->getBonusRewards();
	std::vector<Item*> items = std::vector<Item*>();
	bool getBonusRewards = cipherState->puzzleData->isHardModeEnabled();

	for (auto it = rewards.begin(); it != rewards.end(); it++)
	{
		PlatformerItemDeserializer::getInstance()->deserialize(InventoryEvents::RequestItemDeserializationArgs(*it, [&](Item* item)
		{
			items.push_back(item);
		}));
	}

	if (getBonusRewards)
	{
		for (auto it = bonusRewards.begin(); it != bonusRewards.end(); it++)
		{
			PlatformerItemDeserializer::getInstance()->deserialize(InventoryEvents::RequestItemDeserializationArgs(*it, [&](Item* item)
			{
				items.push_back(item);
			}));
		}
	}

	for (auto it = items.begin(); it != items.end(); it++, index++)
	{
		Inventory* playerInventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);

		playerInventory->forceInsert(*it);	
	}

	for (auto it = items.begin(); it != items.end(); it++, index++)
	{
		ClickableNode* itemIcon = ClickableNode::create((*it)->getIconResource(), (*it)->getIconResource());
		int x = index % 3;
		int y = index / 3;

		itemIcon->setPosition(Vec2((x - 1) * 144.0f, y * -144.0f - 32.0f));

		this->rewardsScroll->addChild(itemIcon);
	}
}
