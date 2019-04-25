#include "CipherPuzzleSelectMenuBase.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectOpponent.h"
#include "Strings/Hexus/Shop.h"
#include "Strings/Menus/Back.h"

using namespace cocos2d;

CipherPuzzleSelectMenuBase::CipherPuzzleSelectMenuBase(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter chapter, std::string chapterProgressSaveKey)
{
	this->chapter = chapter;
	this->chapterProgressSaveKey = chapterProgressSaveKey;
	this->chests = std::vector<CipherPuzzlePreview*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 840.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->background = Sprite::create(HexusResources::Menus_WoodBackground);
	
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

	this->addChild(this->background);
	this->addChild(this->scrollPane);
	this->addChild(this->backButton);
}

CipherPuzzleSelectMenuBase::~CipherPuzzleSelectMenuBase()
{
}

void CipherPuzzleSelectMenuBase::onEnter()
{
	super::onEnter();

	if (!SaveManager::getGlobalDataOrDefault(this->chapterProgressSaveKey, cocos2d::Value(false)).asBool())
	{
		std::string lastOpponentWinsKey = "TODOOO"; //// this->chests.back()->hexusOpponentData->enemyNameKey;

		if (SaveManager::getGlobalDataOrDefault(lastOpponentWinsKey, cocos2d::Value(0)).asInt() > 0)
		{
			// Beat the last chest -- save that we beat the chapter and navigate back to chapter select
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
	std::vector<CipherPuzzlePreview*>::iterator prevIt;

	for (auto it = this->chests.begin(); it != this->chests.end(); prevIt = it, it++)
	{
		if (*it == this->chests.front())
		{
			this->dependencies[*it] = nullptr;
		}
		else
		{
			this->dependencies[*it] = *prevIt;
		}
	}

	for (auto it = this->chests.begin(); it != this->chests.end(); it++)
	{
		(*it)->disableInteraction();
	}

	this->loadProgress();
}

void CipherPuzzleSelectMenuBase::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 64.0f));

	int index = 0;

	for (auto it = this->chests.begin(); it != this->chests.end(); ++it)
	{
		int x = index % 3;
		int y = index / 3;

		(*it)->setPosition(Vec2(496.0f * float(x - 1), y * -480.0f - 240.0f));

		index++;
	}

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void CipherPuzzleSelectMenuBase::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCipherPuzzleSelect, [=](EventCustom* args)
	{
		NavigationEvents::NavigateCipherPuzzleSelectArgs* navArgs = (NavigationEvents::NavigateCipherPuzzleSelectArgs*)args->getUserData();

		if (navArgs->chapter == this->chapter)
		{
			GlobalDirector::loadScene(this);
		}
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(CipherPuzzleSelectMenuBase::onKeyPressed, this);
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(CipherPuzzleSelectMenuBase::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void CipherPuzzleSelectMenuBase::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void CipherPuzzleSelectMenuBase::onBackClick()
{
	NavigationEvents::navigateBack();
}

void CipherPuzzleSelectMenuBase::loadProgress()
{
	for (auto it = this->dependencies.begin(); it != this->dependencies.end(); it++)
	{
		CipherPuzzlePreview* chest = (*it).first;
		CipherPuzzlePreview* dependsOn = (*it).second;

		if (dependsOn == nullptr)
		{
			chest->enableInteraction();
			continue;
		}

		std::string dependencyKey = "TODO"; //// CipherPuzzlePreview::winsPrefix + dependsOn->hexusOpponentData->enemyNameKey;

		int wins = SaveManager::hasGlobalData(dependencyKey) ? SaveManager::getGlobalData(dependencyKey).asInt() : 0;

		if (wins > 0)
		{
			chest->enableInteraction();
		}
	}
}

void CipherPuzzleSelectMenuBase::buildOpponentList()
{
	for (auto it = this->chests.begin(); it != this->chests.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}

	if (!chests.empty())
	{
		//// this->chests.back()->hexusOpponentData->setIsLastInChapter();
	}
}
