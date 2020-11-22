#include "InputsOutputsPanel.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherConfig.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherState.h"
#include "Scenes/Cipher/Components/InputOutputItem.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

InputsOutputsPanel* InputsOutputsPanel::create()
{
	InputsOutputsPanel* instance = new InputsOutputsPanel();

	instance->autorelease();

	return instance;
}

InputsOutputsPanel::InputsOutputsPanel()
{
	this->currentCipherState = nullptr;
	this->inputsHeaderLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Inputs::create());
	this->outputsHeaderLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Outputs::create());
	this->scrollPane = ScrollPane::create(Size(312.0f + 40.0f, 318.0f - 12.0f * 2.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected, Size(0.0f, 24.0f), Size(12.0f, 12.0f));
	this->ioItemsNode = Node::create();
	this->ioSelectionMarker = Sprite::create(CipherResources::IOSelectionMarker);
	this->ioItems = std::vector<InputOutputItem*>();
	
	this->inputsHeaderLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->outputsHeaderLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->scrollPane->addChild(ioItemsNode);
	this->scrollPane->addChild(ioSelectionMarker);
	this->addChild(this->scrollPane);
	this->addChild(this->inputsHeaderLabel);
	this->addChild(this->outputsHeaderLabel);
}

InputsOutputsPanel::~InputsOutputsPanel()
{
}

void InputsOutputsPanel::onEnter()
{
	super::onEnter();
}

void InputsOutputsPanel::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->inputsHeaderLabel->setPosition(Vec2(visibleSize.width / 2.0f + CipherConfig::RightColumnCenter - 80.0f, visibleSize.height / 2.0f - 16.0f));
	this->outputsHeaderLabel->setPosition(Vec2(visibleSize.width / 2.0f + CipherConfig::RightColumnCenter + 80.0f, visibleSize.height / 2.0f - 16.0f));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f + CipherConfig::RightColumnCenter, visibleSize.height / 2.0f -  232.0f));

	for (int index = 0; index < int(this->ioItems.size()); index++)
	{
		this->ioItems[index]->setPosition(Vec2(16.0f, float(index) * -(56.0f + 8.0f) - 32.0f));
	}
}

void InputsOutputsPanel::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeActiveCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeActiveCipherArgs* args = static_cast<CipherEvents::CipherChangeActiveCipherArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->ioSelectionMarker->setPosition(Vec2(-128.0f, float(args->index) * -(56.0f + 8.0f) - 32.0f + 4.0f));
			
			if (args->autoScroll)
			{
				this->scrollPane->scrollToCenter(this->ioSelectionMarker, true, 0.5f);
			}
		}
	}));

	this->addEventListener(EventListenerCustom::create(CipherEvents::EventTryUnlockCurrentCipher, ([=](EventCustom* eventCustom)
	{
		CipherEvents::UnlockArgs* args = static_cast<CipherEvents::UnlockArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			if (args->cipherIndex < 0 || args->cipherIndex > (int)this->ioItems.size())
			{
				return;
			}

			if (args->success)
			{
				this->ioItems[args->cipherIndex]->setStatusPassed();
			}
			else
			{
				this->ioItems[args->cipherIndex]->setStatusFailed();
			}
		}
	})));
}

void InputsOutputsPanel::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	this->currentCipherState = cipherState;

	switch(cipherState->stateType)
	{
		case CipherState::StateType::LoadInitialState:
		{
			this->loadPuzzleData();
			break;
		}
		case CipherState::StateType::TransitionUnlocking:
		{
			for (auto next : this->ioItems)
			{
				next->disableInteraction();
				next->clearStatus();
			}

			this->selectInputOutputPairAtIndex(0);

			this->scrollPane->disableInteraction();
			this->scrollPane->setScrollPercentage(0.0f, true, 0.35f);
			break;
		}
		case CipherState::StateType::Neutral:
		{
			for (auto next : this->ioItems)
			{
				next->enableInteraction();
			}

			this->scrollPane->enableInteraction();
		}
		default:
		{
			break;
		}
	}
}

void InputsOutputsPanel::loadPuzzleData()
{
	this->ioItems.clear();
	this->ioItemsNode->removeAllChildren();
	
	for (int index = 0; index < int(this->currentCipherState->inputOutputMap.size()); index++)
	{
		InputOutputItem* ioItem = InputOutputItem::create(
			std::get<0>(this->currentCipherState->inputOutputMap[index]),
			std::get<1>(this->currentCipherState->inputOutputMap[index]),
			[=](InputOutputItem*)
		{
			this->selectInputOutputPairAtIndex(index);
		});

		this->ioItemsNode->addChild(ioItem);

		this->ioItems.push_back(ioItem);
	}

	this->initializePositions();
	this->scrollPane->updateScrollBounds();

	this->selectInputOutputPairAtIndex(0);
}

void InputsOutputsPanel::selectInputOutputPairAtIndex(int index)
{
	if (index < 0 || index > int(this->currentCipherState->inputOutputMap.size()) || int(this->currentCipherState->inputOutputMap.size()) == 0)
	{
		return;
	}

	CipherEvents::TriggerChangeActiveCipher(CipherEvents::CipherChangeActiveCipherArgs(
		std::get<0>(this->currentCipherState->inputOutputMap[index]),
		std::get<1>(this->currentCipherState->inputOutputMap[index]),
		index
	));
}
