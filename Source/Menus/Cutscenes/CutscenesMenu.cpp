#include "CutscenesMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Save/Collectables.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CutscenesMenu* CutscenesMenu::create()
{
	CutscenesMenu* instance = new CutscenesMenu();

	instance->autorelease();

	return instance;
}

CutscenesMenu::CutscenesMenu()
{
	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);
	
	this->addChild(this->returnButton);
}

CutscenesMenu::~CutscenesMenu()
{
}

void CutscenesMenu::onEnter()
{
	super::onEnter();
}

void CutscenesMenu::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CutscenesMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (GameUtils::getFocusedNode() != this)
		{
			return;
		}
		
		args->handle();

		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
}

void CutscenesMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CutscenesMenu::open(Cutscene cutscene)
{
}
