#include "RadialMenu.h"

const Size RadialMenu::maxPreviewSize = Size(340.0f, 340.0f);

RadialMenu* RadialMenu::create()
{
	RadialMenu* radialMenu = new RadialMenu();

	radialMenu->autorelease();

	return radialMenu;
}

RadialMenu::RadialMenu()
{
	this->activeHackableObject = nullptr;
	this->hackableObjectPreview = nullptr;

	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 196));
	this->menuBackground = Sprite::create(Resources::Menus_HackerModeMenu_RadialMenu);
	this->hackableObjectPreviewNode = Node::create();
	this->dataButton = MenuSprite::create(Resources::Menus_HackerModeMenu_Ram, Resources::Menus_HackerModeMenu_RamHover, Resources::Menus_HackerModeMenu_RamClick);
	this->codeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CpuChip, Resources::Menus_HackerModeMenu_CpuChipHover, Resources::Menus_HackerModeMenu_CpuChipClick);
	this->returnButton = MenuSprite::create(Resources::Menus_HackerModeMenu_Return, Resources::Menus_HackerModeMenu_ReturnHover, Resources::Menus_HackerModeMenu_ReturnClick);

	this->codeMenu = CodeMenu::create();
	this->dataMenu = DataMenu::create();

	this->codeMenu->setVisible(false);
	this->dataMenu->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->menuBackground);
	this->addChild(this->hackableObjectPreviewNode);
	this->addChild(this->dataButton);
	this->addChild(this->codeButton);
	this->addChild(this->returnButton);
	this->addChild(this->codeMenu);
	this->addChild(this->dataMenu);

	this->initializePositions();
	this->initializeListeners();
}

RadialMenu::~RadialMenu()
{
}

void RadialMenu::onHackableEdit(EventCustom* eventArgs)
{
	HackableEvents::HackableObjectEditArgs* args = (HackableEvents::HackableObjectEditArgs*)(eventArgs->getUserData());

	// Remove existing preview image
	this->hackableObjectPreviewNode->removeAllChildren();

	// Set target hackable object
	this->activeHackableObject = args->hackableObject;
	this->hackableObjectPreview = args->previewSprite;
	this->setVisible(true);

	if (hackableObjectPreview != nullptr)
	{
		// Position preview image and scale it
		Size visibleSize = Director::getInstance()->getVisibleSize();

		this->hackableObjectPreview->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

		Size originalSize = this->hackableObjectPreview->getContentSize();
		Size overFlowSize = originalSize - RadialMenu::maxPreviewSize;

		if (overFlowSize.width > 0.0f && overFlowSize.width >= overFlowSize.height)
		{
			this->hackableObjectPreview->setScale(RadialMenu::maxPreviewSize.width / originalSize.width);
		}
		else if (overFlowSize.height > 0.0f)
		{
			this->hackableObjectPreview->setScale(RadialMenu::maxPreviewSize.height / originalSize.height);
		}

		this->hackableObjectPreview->setOpacity(196);

		this->hackableObjectPreviewNode->addChild(this->hackableObjectPreview);
	}

	GameUtils::focus(this);
}

void RadialMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->layerColor->setContentSize(Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
	this->menuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->dataButton->setPosition(Vec2(visibleSize.width / 2.0f - 320.0f, visibleSize.height / 2.0f));
	this->codeButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 320.0f));
}

void RadialMenu::initializeListeners()
{
	this->dataButton->setClickCallback(CC_CALLBACK_1(RadialMenu::onDataMenuOpen, this));
	this->codeButton->setClickCallback(CC_CALLBACK_1(RadialMenu::onCodeMenuOpen, this));
	this->returnButton->setClickCallback(CC_CALLBACK_1(RadialMenu::onClose, this));

	EventListenerCustom* hackableEditListener = EventListenerCustom::create(HackableEvents::HackableObjectEditEvent, CC_CALLBACK_1(RadialMenu::onHackableEdit, this));
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(RadialMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hackableEditListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void RadialMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->setVisible(false);
		GameUtils::focus(this->getParent());
		event->stopPropagation();
		break;
	}
}

void RadialMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);
	GameUtils::focus(this->getParent());
}

void RadialMenu::onCodeMenuOpen(MenuSprite* menuSprite)
{
	this->codeMenu->open(this->activeHackableObject);
}

void RadialMenu::onDataMenuOpen(MenuSprite* menuSprite)
{
	this->dataMenu->open(this->activeHackableObject);
}
