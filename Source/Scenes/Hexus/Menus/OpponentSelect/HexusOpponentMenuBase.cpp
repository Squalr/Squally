#include "HexusOpponentMenuBase.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/Menus/HexusDeckManagement.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/Store/HexusStoreMenu.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectOpponent.h"
#include "Strings/Hexus/Shop.h"
#include "Strings/Menus/Back.h"

using namespace cocos2d;

HexusOpponentMenuBase::HexusOpponentMenuBase(std::string chapterProgressSaveKey)
{
	this->chapterProgressSaveKey = chapterProgressSaveKey;
	this->opponents = std::vector<HexusOpponentPreview*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 840.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->background = Sprite::create(HexusResources::Menus_WoodBackground);
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
			NavigationEvents::NavigateBack();
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
			this->dependencies[*it] = nullptr;
		}
		else
		{
			this->dependencies[*it] = *prevIt;
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

	int index = 0;

	for (auto it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		int x = index % 3;
		int y = index / 3;

		(*it)->setPosition(Vec2(496.0f * float(x - 1), y * -480.0f - 240.0f));

		index++;
	}

	this->deckManagementButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f, visibleSize.height - 64.0f));
	this->shopButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f - 256.0f, visibleSize.height - 64.0f));
	this->opponentSelectLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 64.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void HexusOpponentMenuBase::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handled = true;

		NavigationEvents::NavigateBack();
	});

	this->deckManagementButton->setMouseClickCallback(CC_CALLBACK_0(HexusOpponentMenuBase::onDeckManagementClick, this));
	this->shopButton->setMouseClickCallback(CC_CALLBACK_0(HexusOpponentMenuBase::onShopClick, this));
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(HexusOpponentMenuBase::onBackClick, this));
}

void HexusOpponentMenuBase::onMouseOver(HexusOpponentPreview* opponent)
{
}

void HexusOpponentMenuBase::onBackClick()
{
	NavigationEvents::NavigateBack();
}

void HexusOpponentMenuBase::onDeckManagementClick()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusDeckManagement::getInstance()));
}

void HexusOpponentMenuBase::onShopClick()
{
	NavigationEvents::LoadScene(HexusStoreMenu::getInstance());
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

void HexusOpponentMenuBase::buildOpponentList()
{
	std::sort(this->opponents.begin(), this->opponents.end(), [](HexusOpponentPreview* a, const HexusOpponentPreview* b) -> bool
	{ 
		return a->hexusOpponentData->strength < b->hexusOpponentData->strength; 
	});

	for (auto it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}

	if (!opponents.empty())
	{
		this->opponents.back()->hexusOpponentData->setIsLastInChapter();
	}
}
