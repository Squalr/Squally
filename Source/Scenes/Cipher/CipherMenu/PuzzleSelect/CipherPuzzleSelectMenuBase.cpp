#include "CipherPuzzleSelectMenuBase.h"

#include "cocos/2d/CCParticleSystemQuad.h"
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
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"

#include "Resources/CipherResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectOpponent.h"
#include "Strings/Hexus/Shop.h"
#include "Strings/Menus/Back.h"

using namespace cocos2d;

CipherPuzzleSelectMenuBase::CipherPuzzleSelectMenuBase(std::string chapterProgressSaveKey)
{
	this->chapterProgressSaveKey = chapterProgressSaveKey;
	this->chests = std::vector<CipherPuzzlePreview*>();
	this->nether = ParticleSystemQuad::create(ParticleResources::BlueNether);
	this->swirl = ParticleSystemQuad::create(ParticleResources::BlueStarCircle);
	this->backboard = Sprite::create(CipherResources::Menus_CipherBackboard);
	
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

	this->addChild(this->nether);
	this->addChild(this->swirl);
	this->addChild(this->backboard);
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
			NavigationEvents::NavigateBack();
			return;
		}
	}

	const float delay = 0.25f;
	const float duration = 0.35f;

	GameUtils::fadeInObject(this->backButton, delay, duration);

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);

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

	this->nether->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->swirl->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->backboard->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	int index = 0;

	for (auto it = this->chests.begin(); it != this->chests.end(); ++it)
	{
		int x = index % 4;
		int y = index / 4;

		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f * (float(x) - 1.5f), visibleSize.height / 2.0f + (float(y) - 0.5f) * -356.0f));

		index++;
	}

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void CipherPuzzleSelectMenuBase::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		args->handle();

		NavigationEvents::NavigateBack();
	});

	this->backButton->setMouseClickCallback(CC_CALLBACK_0(CipherPuzzleSelectMenuBase::onBackClick, this));
}

void CipherPuzzleSelectMenuBase::onBackClick()
{
		NavigationEvents::NavigateBack();
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

void CipherPuzzleSelectMenuBase::buildCipherList()
{
	for (auto it = this->chests.begin(); it != this->chests.end(); ++it)
	{
		this->addChild(*it);
	}

	if (!chests.empty())
	{
		//// this->chests.back()->hexusOpponentData->setIsLastInChapter();
	}
}

std::string CipherPuzzleSelectMenuBase::buildCipherJson(std::string rule, std::vector<std::string> inputs)
{
	const std::string templateJson = "{\"easy\":{\"rule\":\"{{rule}}\",\"inputs\":[{{inputs}}]},\"hard\":{\"rule\":\"{{rule}}\",\"inputs\":[{{inputs}}]},\"rewards\":[],\"bonus-rewards\":[]}";
	
	std::string inputsList = "";

	for (auto it = inputs.begin(); it != inputs.end(); it++)
	{
		inputsList += "\"" + (*it) + "\",";
	}

	inputsList = StrUtils::trim(inputsList, ",");
	std::string result = StrUtils::replaceAll(templateJson, "{{rule}}", rule);
	result = StrUtils::replaceAll(result, "{{inputs}}", inputsList);

	return result;
}
