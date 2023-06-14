#include "CutscenesMenu.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Scenes/Title/TitleScreen.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/LabelStack.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Save/Collectables.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/CutsceneResources.h"
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
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->cutsceneAnimation = SmartAnimationSequenceNode::create();
	this->crackCutsceneChime = Sound::create(SoundResources::Platformer_Cutscenes_CutsceneChime);
	this->credits = LabelStack::create(visibleSize, 32.0f);

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->credits->insert(this->buildHeader(ConstantString::create("Lead Programmer")));
	this->credits->insert(this->buildEntry(ConstantString::create("Zachary Canann")));
	this->credits->insertNewline();
	this->credits->insertNewline();
	this->credits->insert(this->buildHeader(ConstantString::create("Lead Artists")));
	this->credits->insert(this->buildEntry(ConstantString::create("EatCreatures")));
	this->credits->insert(this->buildEntry(ConstantString::create("Robert Brooks")));
	this->credits->insert(this->buildEntry(ConstantString::create("Rexard")));
	this->credits->insertNewline();
	this->credits->insertNewline();
	this->credits->insert(this->buildHeader(ConstantString::create("Programmers")));
	this->credits->insert(this->buildEntry(ConstantString::create("Nathaniel Lewis")));
	this->credits->insert(this->buildEntry(ConstantString::create("Matt Bucci")));
	this->credits->insertNewline();
	this->credits->insertNewline();
	this->credits->insert(this->buildHeader(ConstantString::create("Musicians")));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_AlexanderIvanov_AlexanderIvanov::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_Alkis_Alkis::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_AndreaBaroni_AndreaBaroni::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_Blacksmith_Blacksmith::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_Flutist_Flutist::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_GavinLuke_GavinLuke::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_KrazyKartoons_KrazyKartoons::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_Lemmonias_Lemmonias::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_Nosbertus_Nosbertus::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_TheoAndPaul_TheoAndPaul::create()));
	this->credits->insert(this->buildEntry(Strings::Menus_Music_Warmstone_Warmstone::create()));
	this->credits->insertNewline();
	this->credits->insertNewline();
	this->credits->insert(this->buildHeader(ConstantString::create("Artists")));
	this->credits->insert(this->buildEntry(ConstantString::create("2dvill")));
	this->credits->insert(this->buildEntry(ConstantString::create("2tailcomet")));
	this->credits->insert(this->buildEntry(ConstantString::create("Archanor Game Art")));
	this->credits->insert(this->buildEntry(ConstantString::create("AssetsBrush")));
	this->credits->insert(this->buildEntry(ConstantString::create("Avgusta")));
	this->credits->insert(this->buildEntry(ConstantString::create("Best game kits")));
	this->credits->insert(this->buildEntry(ConstantString::create("Blackhammer")));
	this->credits->insert(this->buildEntry(ConstantString::create("CGA")));
	this->credits->insert(this->buildEntry(ConstantString::create("CruizRF")));
	this->credits->insert(this->buildEntry(ConstantString::create("DanilChe")));
	this->credits->insert(this->buildEntry(ConstantString::create("Demsprod")));
	this->credits->insert(this->buildEntry(ConstantString::create("hallinniklas")));
	this->credits->insert(this->buildEntry(ConstantString::create("IpaxStudio")));
	this->credits->insert(this->buildEntry(ConstantString::create("Katiefhk")));
	this->credits->insert(this->buildEntry(ConstantString::create("KodiakGraphics")));
	this->credits->insert(this->buildEntry(ConstantString::create("The Game Assets Mine")));
	this->credits->insert(this->buildEntry(ConstantString::create("tokegameart")));
	this->credits->insertNewline();
	this->credits->insertNewline();
	this->credits->insert(this->buildHeader(ConstantString::create("Sound")));
	this->credits->insert(this->buildEntry(ConstantString::create("Epic Stock Media")));
	this->credits->insert(this->buildEntry(ConstantString::create("soundsparkllc")));
	this->credits->insertNewline();
	this->credits->insertNewline();
	this->credits->insert(this->buildHeader(ConstantString::create("Thank you for playing!")));
	this->credits->insert(this->buildEntry(ConstantString::create("I hope you learned a few things :^)")));

	this->credits->setVisible(false);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->returnButton->setOpacity(0);
	
	this->addChild(this->cutsceneAnimation);
	this->addChild(this->returnButton);
	this->addChild(this->crackCutsceneChime);
	this->addChild(this->credits);
}

CutscenesMenu::~CutscenesMenu()
{
}

void CutscenesMenu::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CutscenesMenu::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->credits->setPosition(Vec2(0.0f, -192.0f));
	this->cutsceneAnimation->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f, 96.0f));
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

void CutscenesMenu::update(float dt)
{
	super::update(dt);

	if (this->currentCutscene == Cutscene::Credits)
	{
		const float ScrollSpeed = 72.0f;

		this->credits->setPositionY(this->credits->getPositionY() + dt * ScrollSpeed);
	}
}

void CutscenesMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CutscenesMenu::open(Cutscene cutscene)
{
	this->currentCutscene = cutscene;

	switch(this->currentCutscene)
	{
		case Cutscene::CrackSmall:
		{
			this->crackCutsceneChime->play();
			this->cutsceneAnimation->playAnimation(CutsceneResources::CrackSmall_Cutscene_0000, 0.125f, true, [=]()
			{
				if (this->returnClickCallback != nullptr)
				{
					this->returnClickCallback();
				}
			});
			break;
		}
		case Cutscene::CrackMedium:
		{
			this->crackCutsceneChime->play();
			this->cutsceneAnimation->playAnimation(CutsceneResources::CrackMedium_Cutscene_0000, 0.125f, true, [=]()
			{
				if (this->returnClickCallback != nullptr)
				{
					this->returnClickCallback();
				}
			});
			break;
		}
		case Cutscene::CrackLarge:
		{
			this->crackCutsceneChime->play();
			this->cutsceneAnimation->playAnimation(CutsceneResources::CrackLarge_Cutscene_0000, 0.125f, true, [=]()
			{
				if (this->returnClickCallback != nullptr)
				{
					this->returnClickCallback();
				}
			});
			break;
		}
		case Cutscene::Credits:
		{
			this->returnClickCallback = [=]()
			{
				NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
			};

			this->runAction(Sequence::create(
				DelayTime::create(10.0f),
				CallFunc::create([=]()
				{
					this->returnButton->runAction(FadeTo::create(1.0f, 255));
				}),
				nullptr
			));
			this->credits->setVisible(true);
			break;
		}
	}
}

LocalizedLabel* CutscenesMenu::buildHeader(LocalizedString* inText)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, inText);

	label->enableOutline(Color4B::BLACK, 3);
	label->setColor(Color3B::WHITE);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setHorizontalAlignment(TextHAlignment::CENTER);

	return label;
}

LocalizedLabel* CutscenesMenu::buildEntry(LocalizedString* inText)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, inText);

	label->enableOutline(Color4B::BLACK, 3);
	label->setColor(Color3B::WHITE);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setHorizontalAlignment(TextHAlignment::CENTER);

	return label;
}
