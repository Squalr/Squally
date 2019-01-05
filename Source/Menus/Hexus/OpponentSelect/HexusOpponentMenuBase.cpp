#include "HexusOpponentMenuBase.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/UIResources.h"

#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectOpponent.h"
#include "Strings/Hexus/Shop.h"
#include "Strings/Menus/Back.h"

using namespace cocos2d;

HexusOpponentMenuBase::HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter, std::string chapterProgressSaveKey)
{
	this->chapter = chapter;
	this->chapterProgressSaveKey = chapterProgressSaveKey;
	this->opponents = std::vector<HexusOpponentPreview*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 840.0f), Color4B(0, 0, 0, 196));
	this->background = Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->opponentSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hexus_SelectOpponent::create());

	LocalizedLabel* manageDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_ManageCards::create());
	LocalizedLabel* manageDeckLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_ManageCards::create());
	
	manageDeckLabel->enableOutline(Color4B::BLACK, 2);
	manageDeckLabelHover->enableOutline(Color4B::BLACK, 2);

	this->deckManagementButton = ClickableTextNode::create(
		manageDeckLabel,
		manageDeckLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	LocalizedLabel* shopLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Shop::create());
	LocalizedLabel* shopLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Shop::create());

	shopLabel->enableOutline(Color4B::BLACK, 2);
	shopLabelHover->enableOutline(Color4B::BLACK, 2);

	this->shopButton = ClickableTextNode::create(
		shopLabel,
		shopLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel* backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	this->opponentSelectLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->scrollPane);
	this->addChild(this->opponentSelectLabel);
	this->addChild(this->deckManagementButton);
	this->addChild(this->shopButton);
	this->addChild(this->backButton);
}

HexusOpponentMenuBase::~HexusOpponentMenuBase()
{
}

void HexusOpponentMenuBase::onEnter()
{
	super::onEnter();

	if (!SaveManager::getGlobalDataOrDefault(this->chapterProgressSaveKey, cocos2d::Value(false)).asBool())
	{
		std::string lastOpponentWinsKey = HexusOpponentData::winsPrefix + this->opponents.back()->hexusOpponentData->enemyNameKey;

		if (SaveManager::getGlobalDataOrDefault(lastOpponentWinsKey, cocos2d::Value(0)).asInt() > 0)
		{
			// Beat the last opponent -- save that we beat the chapter and navigate back to chapter select
			SaveManager::saveGlobalData(this->chapterProgressSaveKey, cocos2d::Value(true));
			NavigationEvents::navigateBack(1);
			return;
		}
	}

	const float delay = 0.25f;
	const float duration = 0.35f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);
	GameUtils::fadeInObject(this->backButton, delay, duration);

	// Just assume linear dependencies for now
	this->dependencies.clear();
	std::vector<HexusOpponentPreview*>::iterator prevIt;

	for (auto it = this->opponents.begin(); it != this->opponents.end(); prevIt = it, it++)
	{
		if (*it == this->opponents.front())
		{
			this->dependencies.emplace((*it), nullptr);
		}
		else
		{
			this->dependencies.emplace((*it), (*prevIt));
		}
	}

	for (auto it = this->opponents.begin(); it != this->opponents.end(); it++)
	{
		(*it)->disableInteraction();
	}

	this->loadProgress();
}

void HexusOpponentMenuBase::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 64.0f));

	Size scrollPaneSize = this->scrollPane->getPaneSize();

	int index = 0;

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		int x = index % 3;
		int y = (this->opponents.size() - 1 - index + (3 - this->opponents.size() % 3)) / 3 - (this->opponents.size() % 3 == 0 ? 1 : 0);

		(*it)->setPosition(Vec2(scrollPaneSize.width / 2.0f - 496.0f + 496.0f * x, y * 480.0f + 240.0f));

		index++;
	}

	this->scrollPane->fitSizeToContent();
	this->deckManagementButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f, visibleSize.height - 64.0f));
	this->shopButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f - 256.0f, visibleSize.height - 64.0f));
	this->opponentSelectLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 64.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void HexusOpponentMenuBase::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusOpponentSelect, [=](EventCustom* args)
	{
		NavigationEvents::NavigateHexusOpponentSelectArgs* navArgs = (NavigationEvents::NavigateHexusOpponentSelectArgs*)args->getUserData();

		if (navArgs->chapter == this->chapter)
		{
			GlobalDirector::loadScene(this);
		}
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusOpponentMenuBase::onKeyPressed, this);
	this->deckManagementButton->setClickCallback(CC_CALLBACK_1(HexusOpponentMenuBase::onDeckManagementClick, this));
	this->shopButton->setClickCallback(CC_CALLBACK_1(HexusOpponentMenuBase::onShopClick, this));
	this->backButton->setClickCallback(CC_CALLBACK_1(HexusOpponentMenuBase::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void HexusOpponentMenuBase::onMouseOver(HexusOpponentPreview* opponent)
{
}

void HexusOpponentMenuBase::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void HexusOpponentMenuBase::onBackClick(ClickableNode* menuSprite)
{
	NavigationEvents::navigateBack();
}

void HexusOpponentMenuBase::onDeckManagementClick(ClickableNode* menuSprite)
{
	NavigationEvents::navigateHexusDeckManagement();
}

void HexusOpponentMenuBase::onShopClick(ClickableNode* menuSprite)
{
	NavigationEvents::navigateHexusShop();
}

void HexusOpponentMenuBase::loadProgress()
{
	for (auto it = this->dependencies.begin(); it != this->dependencies.end(); it++)
	{
		HexusOpponentPreview* opponent = (*it).first;
		HexusOpponentPreview* dependsOn = (*it).second;

		if (dependsOn == nullptr)
		{
			opponent->enableInteraction();
			continue;
		}

		std::string dependencyKey = HexusOpponentData::winsPrefix + dependsOn->hexusOpponentData->enemyNameKey;

		int wins = SaveManager::hasGlobalData(dependencyKey) ? SaveManager::getGlobalData(dependencyKey).asInt() : 0;

		if (wins > 0)
		{
			opponent->enableInteraction();
		}
	}
}
