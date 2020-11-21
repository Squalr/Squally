#include "CollectablesMenu.h"

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

CollectablesMenu* CollectablesMenu::create()
{
	CollectablesMenu* instance = new CollectablesMenu();

	instance->autorelease();

	return instance;
}

CollectablesMenu::CollectablesMenu()
{
	this->collectablesWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->saveKeys = std::vector<std::string>();
	this->sprites = std::vector<Sprite*>();
	this->lockedSprites = std::vector<Sprite*>();
	this->contentPane = ScrollPane::create(Size(1024.0f, 612.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->collectablesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Collectables_Collectables::create());
	this->returnClickCallback = nullptr;

	this->contentPane->setBackgroundColor(Color4B(0, 0, 0, 0));

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->collectablesLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->collectablesLabel->enableGlow(Color4B::BLACK);

	for (auto data : Collectables::getCollectableAnimalData())
	{
		this->registerCollectableAnimal(data.unlockedResource, data.lockedResource, data.saveKey);
	}
	
	this->addChild(this->collectablesWindow);
	this->addChild(this->contentPane);
	this->addChild(this->collectablesLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

CollectablesMenu::~CollectablesMenu()
{
}

void CollectablesMenu::onEnter()
{
	super::onEnter();

	this->updateCollectedVisualState();
}

void CollectablesMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->collectablesWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->contentPane->setPosition(Vec2(visibleSize.width / 2.0f + 24.0f, visibleSize.height / 2.0f - 44.0f));
	this->collectablesLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CollectablesMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
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

void CollectablesMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CollectablesMenu::open()
{
	this->updateCollectedVisualState();
}

void CollectablesMenu::updateCollectedVisualState()
{
	int collectedCount = 0;

	for (int index = 0; index < int(this->saveKeys.size()); index++)
	{
		if (SaveManager::GetProfileDataOrDefault(this->saveKeys[index], Value(false)).asBool())
		{
			collectedCount++;
			this->sprites[index]->setVisible(true);
			this->lockedSprites[index]->setVisible(false);
		}
		else
		{
			this->sprites[index]->setVisible(false);
			this->lockedSprites[index]->setVisible(true);
		}
	}
}

void CollectablesMenu::registerCollectableAnimal(std::string resource, std::string resourceLocked, std::string saveKey)
{
	Sprite* next = Sprite::create(resource);
	Sprite* nextLocked = Sprite::create(resourceLocked);

	this->contentPane->addChild(next);
	this->contentPane->addChild(nextLocked);

	int x = this->sprites.size() % 5;
	int y = this->sprites.size() / 5;

	Vec2 position = Vec2((float(x) + 0.5f) * 192.0f + 16.0f - this->contentPane->getPaneSize().width / 2.0f, float(y) * -212.0f - 128.0f);

	next->setPosition(position);
	nextLocked->setPosition(position);

	this->saveKeys.push_back(saveKey);
	this->sprites.push_back(next);
	this->lockedSprites.push_back(nextLocked);
}
