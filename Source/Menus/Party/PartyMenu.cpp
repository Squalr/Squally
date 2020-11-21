#include "PartyMenu.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PartyMenu* PartyMenu::create()
{
	PartyMenu* instance = new PartyMenu();

	instance->autorelease();

	return instance;
}

PartyMenu::PartyMenu()
{
	this->partyWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->partyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Party_Party::create());
	this->statsBarsNode = Node::create();
	this->returnClickCallback = nullptr;
	this->partyStatsBars = std::vector<StatsBars*>();
	this->onSelect = nullptr;
	this->onExit = nullptr;
	this->chooseTargetNode = Node::create();
	this->chooseTargetFrame = Sprite::create(UIResources::Combat_ItemFrame);
	this->chooseTargetItemFrame = Sprite::create(UIResources::Combat_ItemsCircle);
	this->chooseTargetItemIcon = Sprite::create();
	this->chooseTargetLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Platformer_Combat_ChooseATarget::create());
	this->countString = ConstantString::create(std::to_string(0));
	this->countLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_TimesConstant::create()->setStringReplacementVariables(this->countString));
	this->selectionIndex = 0;

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelSelected = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelSelected->enableOutline(Color4B::BLACK, 2);
	returnLabelSelected->setTextColor(Color4B::YELLOW);
	returnLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelSelected->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Back::create());
	LocalizedLabel*	cancelLabelSelected = cancelLabel->clone();

	cancelLabel->enableOutline(Color4B::BLACK, 2);
	cancelLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabel->enableGlow(Color4B::BLACK);
	cancelLabelSelected->enableOutline(Color4B::BLACK, 2);
	cancelLabelSelected->setTextColor(Color4B::YELLOW);
	cancelLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabelSelected->enableGlow(Color4B::ORANGE);

	this->cancelButton = ClickableTextNode::create(
		cancelLabel,
		cancelLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	LocalizedLabel*	stuckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Party_Stuck::create());
	LocalizedLabel*	stuckLabelSelected = stuckLabel->clone();

	stuckLabel->enableOutline(Color4B::BLACK, 2);
	stuckLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	stuckLabel->enableGlow(Color4B::BLACK);
	stuckLabelSelected->enableOutline(Color4B::BLACK, 2);
	stuckLabelSelected->setTextColor(Color4B::YELLOW);
	stuckLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	stuckLabelSelected->enableGlow(Color4B::ORANGE);

	this->stuckButton = ClickableTextNode::create(
		stuckLabel,
		stuckLabelSelected,
		UIResources::Menus_Buttons_SmallGenericButton,
		UIResources::Menus_Buttons_SmallGenericButtonSelected);

	this->partyLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->partyLabel->enableGlow(Color4B::BLACK);
	this->chooseTargetLabel->enableOutline(Color4B::BLACK, 2);
	this->countLabel->enableOutline(Color4B::BLACK, 2);
	this->countLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->chooseTargetLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->chooseTargetNode->addChild(this->chooseTargetFrame);
	this->chooseTargetNode->addChild(this->chooseTargetItemFrame);
	this->chooseTargetNode->addChild(this->chooseTargetItemIcon);
	this->chooseTargetNode->addChild(this->countLabel);
	this->chooseTargetNode->addChild(this->chooseTargetLabel);
	this->addChild(this->partyWindow);
	this->addChild(this->partyLabel);
	this->addChild(this->statsBarsNode);
	this->addChild(this->closeButton);
	this->addChild(this->stuckButton);
	this->addChild(this->cancelButton);
	this->addChild(this->returnButton);
	this->addChild(this->chooseTargetNode);
}

PartyMenu::~PartyMenu()
{
}

void PartyMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->partyWindow, delay, duration);
	GameUtils::fadeInObject(this->partyLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->cancelButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void PartyMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->partyWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->statsBarsNode->setPosition(Vec2(visibleSize.width / 2.0f - 460.0f, visibleSize.height / 2.0f + 128.0f));
	this->partyLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->stuckButton->setPosition(Vec2(visibleSize.width / 2.0f + 384.0f, visibleSize.height / 2.0f - 288.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
	this->chooseTargetNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 416.0f));

	this->chooseTargetItemFrame->setPosition(Vec2(-136.0f, 0.0f));
	this->chooseTargetItemIcon->setPosition(Vec2(-136.0f, 0.0f));
	this->countLabel->setPosition(Vec2(-136.0f + 24.0f, -24.0f));
	this->chooseTargetLabel->setPosition(Vec2(-64.0f, 0.0f));
}

void PartyMenu::initializeListeners()
{
	super::initializeListeners();

	this->stuckButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		NotificationEvents::TriggerConfirmation(NotificationEvents::ConfirmationArgs(
			Strings::Menus_Party_StuckConfirm::create(),
			[=]()
			{
				PlatformerEvents::TriggerUnstuck();

				return true;
			},
			[=]()
			{
				return false;
			}
		));
	});

	this->cancelButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onCancelClick();
	});

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onReturnClick();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onCancelClick();
		this->onReturnClick();
	});
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_UP_ARROW, InputEvents::KeyCode::KEY_W }, [=](InputEvents::KeyboardEventArgs* args)
	{
		args->handle();
		
		this->trySelectPrevious();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_LEFT_ARROW, InputEvents::KeyCode::KEY_A }, [=](InputEvents::KeyboardEventArgs* args)
	{
		args->handle();
		
		this->trySelectPrevious();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_RIGHT_ARROW, InputEvents::KeyCode::KEY_D }, [=](InputEvents::KeyboardEventArgs* args)
	{
		args->handle();
		
		this->trySelectNext();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_DOWN_ARROW, InputEvents::KeyCode::KEY_S }, [=](InputEvents::KeyboardEventArgs* args)
	{
		args->handle();

		this->trySelectNext();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		this->performSelectionActions();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		this->onCancelClick();
		this->onReturnClick();
	});
}

void PartyMenu::disableUnstuck()
{
	this->stuckButton->disableInteraction(127);
}

void PartyMenu::open()
{
	this->buildAllStats();

	for (auto next : this->partyStatsBars)
	{
		next->disableInteraction();
		next->setClickCallback(nullptr);
	}

	// State for a normal open
	this->onSelect = nullptr;
	this->onExit = nullptr;
	this->cancelButton->setVisible(false);
	this->returnButton->setVisible(true);
	this->stuckButton->setVisible(true);
	this->chooseTargetNode->setVisible(false);
}

void PartyMenu::openForSelection(std::string iconResource, int count, std::function<bool(PlatformerEntity*)> canSelect, std::function<void(PlatformerEntity*)> onSelect, std::function<void()> onExit)
{
	this->buildAllStats();

	this->countString->setString(std::to_string(count));
	this->chooseTargetItemIcon->initWithFile(iconResource);

	for (auto next : this->partyStatsBars)
	{
		if (canSelect != nullptr && !canSelect(next->getStatsTarget()))
		{
			next->disableInteraction(127);

			continue;
		}

		next->enableInteraction();

		next->setMouseOverCallback([=](StatsBars* statsBars)
		{
			this->select(statsBars);
		});

		next->setClickCallback([=](StatsBars* statsBars)
		{
			for (auto next : this->partyStatsBars)
			{
				next->disableInteraction(next->getFrameOpaicty());
			}

			if (onSelect != nullptr)
			{
				onSelect(statsBars->getStatsTarget());
			}
		});
	}

	this->trySelectNext();

	// State for a selection based open
	this->onSelect = onSelect;
	this->onExit = onExit;
	this->cancelButton->setVisible(true);
	this->returnButton->setVisible(false);
	this->stuckButton->setVisible(false);
	this->chooseTargetNode->setVisible(true);
}

void PartyMenu::select(StatsBars* statsBars)
{
	int seekIndex = 0;

	for (auto next : this->partyStatsBars)
	{
		if (next != statsBars)
		{
			next->setSelected(false);
		}
		else
		{
			statsBars->setSelected(true);
			this->selectionIndex = seekIndex;
		}

		seekIndex++;
	}
}

void PartyMenu::buildAllStats()
{
	this->partyStatsBars.clear();
	this->statsBarsNode->removeAllChildren();

	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* entity)
	{
		this->buildStats(entity);
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerHelper>([&](PlatformerHelper* entity)
	{
		this->buildStats(entity);
	}));

	for (int index = 0; index < int(this->partyStatsBars.size()); index++)
	{
		this->partyStatsBars[index]->setPositionY((float)index * -224.0f);
	}
}

void PartyMenu::buildStats(PlatformerEntity* entity)
{
		StatsBars* statsBars = StatsBars::create(true, true);

		statsBars->setStatsTarget(entity);
		statsBars->toggleSelectionArrowVisibility(true);

		this->statsBarsNode->addChild(statsBars);
		this->partyStatsBars.push_back(statsBars);
}

int PartyMenu::getSelectionIndex()
{
	return this->selectionIndex;
}

void PartyMenu::setSelectionIndex(int index)
{
	if (index < int(this->partyStatsBars.size()) && this->partyStatsBars[index]->canSelect())
	{
		this->select(this->partyStatsBars[index]);
	}
}

void PartyMenu::trySelectNext()
{
	StatsBars* currentSelection = nullptr;

	for (auto it : this->partyStatsBars)
	{
		if (it->isSelected())
		{
			currentSelection = it;
			break;
		}
	}

	if (currentSelection == nullptr)
	{
		for (auto it : this->partyStatsBars)
		{
			if (it->canSelect())
			{
				this->select(it);
				return;
			}
		}
	}

	auto selectionIt = std::find(this->partyStatsBars.begin(), this->partyStatsBars.end(), currentSelection);

	if (selectionIt == this->partyStatsBars.end())
	{
		return;
	}

	for (auto it = selectionIt + 1; it != this->partyStatsBars.end(); it++)
	{
		if ((*it)->canSelect())
		{
			this->select((*it));
			return;
		}
	}

	for (auto it = this->partyStatsBars.begin(); it != selectionIt; it++)
	{
		if ((*it)->canSelect())
		{
			this->select((*it));
			return;
		}
	}
}

void PartyMenu::trySelectPrevious()
{
	StatsBars* currentSelection = nullptr;

	for (auto it : this->partyStatsBars)
	{
		if (it->isSelected())
		{
			currentSelection = it;
			break;
		}
	}

	if (currentSelection == nullptr)
	{
		for (auto it : this->partyStatsBars)
		{
			if (it->canSelect())
			{
				this->select(it);
				return;
			}
		}
	}

	auto selectionIt = std::find(this->partyStatsBars.begin(), this->partyStatsBars.end(), currentSelection);

	if (selectionIt == this->partyStatsBars.end())
	{
		return;
	}

	for (auto it = this->partyStatsBars.begin(); it != selectionIt; it++)
	{
		if ((*it)->canSelect())
		{
			this->select((*it));
			return;
		}
	}

	for (auto it = selectionIt + 1; it != this->partyStatsBars.end(); it++)
	{
		if ((*it)->canSelect())
		{
			this->select((*it));
			return;
		}
	}
}

void PartyMenu::performSelectionActions()
{
	for (auto it : this->partyStatsBars)
	{
		if (it->isSelected())
		{
			it->tryInteract();
			break;
		}
	}
}

void PartyMenu::onCancelClick()
{
	this->stopAllActions();

	if (this->onExit != nullptr && this->cancelButton->isVisible())
	{
		this->onExit();
	}
}

void PartyMenu::onReturnClick()
{
	this->stopAllActions();
	
	if (this->returnClickCallback != nullptr && this->returnButton->isVisible())
	{
		this->returnClickCallback();
	}
}

void PartyMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}
