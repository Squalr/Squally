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
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/Inputs.h"
#include "Strings/Cipher/Outputs.h"

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
	this->scrollPane = ScrollPane::create(Size(312.0f, 312.0f - 12.0f * 2.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected, Size(0.0f, 32.0f), Size(12.0f, 12.0f));
	this->ioPanelsNode = Node::create();
	this->ioSelectionMarker = Sprite::create(CipherResources::IOSelectionMarker);
	this->inputLabels = std::vector<LocalizedLabel*>();
	this->outputLabels = std::vector<LocalizedLabel*>();
	
	this->inputsHeaderLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->outputsHeaderLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->scrollPane->addChild(ioPanelsNode);
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

	this->inputsHeaderLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 80.0f, visibleSize.height / 2.0f - 16.0f));
	this->outputsHeaderLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter + 80.0f, visibleSize.height / 2.0f - 16.0f));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f -  232.0f));
}

void InputsOutputsPanel::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeActiveCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeActiveCipherArgs* args = static_cast<CipherEvents::CipherChangeActiveCipherArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			int index = 0;

			for (index = 0; index < this->currentCipherState->inputOutputMap.size(); index++)
			{
				std::string input = std::get<0>(this->currentCipherState->inputOutputMap[index]);
				std::string output = std::get<1>(this->currentCipherState->inputOutputMap[index]);

				if (input == args->input && output == args->output)
				{
					break;
				}
			}

			this->ioSelectionMarker->setPosition(Vec2(-128.0f, float(index) * -(56.0f + 8.0f) + 4.0f));
			
			if (args->autoScroll)
			{
				this->scrollPane->scrollTo(-this->ioSelectionMarker->getPositionY(), true, 0.5f);
			}
		}
	}));
}

void InputsOutputsPanel::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
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
			this->scrollPane->setScrollPercentage(0.0f, true, 0.5f);
			break;
		}
		default:
		{
			break;
		}
	}
}

void InputsOutputsPanel::loadPuzzleData()
{
	this->inputLabels.clear();
	this->outputLabels.clear();
	this->ioPanelsNode->removeAllChildren();

	int index = 0;
	float scrollPaneWidth = this->scrollPane->getPaneSize().width;

	for (auto it = this->currentCipherState->inputOutputMap.begin(); it != this->currentCipherState->inputOutputMap.end(); it++, index++)
	{
		ClickableNode* ioPanel = ClickableNode::create(CipherResources::IOPanel, CipherResources::IOPanelSelected);
		LocalizedLabel* inputLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(std::get<0>(*it)));
		LocalizedLabel* outputLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(std::get<1>(*it)));

		inputLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
		outputLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

		ioPanel->setClickCallback([=](MouseEvents::MouseEventArgs*)
		{
			this->selectInputOutputPairAtIndex(index);
		});

		ioPanel->setContentSize(Size(scrollPaneWidth, 56.0f));

		ioPanel->setPosition(Vec2(16.0f, float(index) * -(56.0f + 8.0f)));
		inputLabel->setPosition(Vec2(-48.0f, float(index) * -(56.0f + 8.0f)));
		outputLabel->setPosition(Vec2(48.0f + 24.0f, float(index) * -(56.0f + 8.0f)));

		this->ioPanelsNode->addChild(ioPanel);
		this->ioPanelsNode->addChild(inputLabel);
		this->ioPanelsNode->addChild(outputLabel);

		this->inputLabels.push_back(inputLabel);
		this->outputLabels.push_back(outputLabel);
	}

	this->selectInputOutputPairAtIndex(0);
	this->scrollPane->updateScrollBounds();
}

void InputsOutputsPanel::selectInputOutputPairAtIndex(int index)
{
	if (index < 0 || index > this->currentCipherState->inputOutputMap.size())
	{
		return;
	}

	CipherEvents::TriggerChangeActiveCipher(CipherEvents::CipherChangeActiveCipherArgs(
		std::get<0>(this->currentCipherState->inputOutputMap[index]),
		std::get<1>(this->currentCipherState->inputOutputMap[index])
	));
}
