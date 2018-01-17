#include "HUD.h"

HUD* HUD::create()
{
	HUD* hud = new HUD();

	hud->autorelease();

	return hud;
}

HUD::HUD()
{
	this->heart = Sprite::create(Resources::HUD_Heart);
	this->healthBarFrame = Sprite::create(Resources::HUD_HealthBarFrame);
	this->dialogNode = Node::create();

	this->hackableObjectsHud = Layer::create();
	this->dataCodeMenu = DataCodeMenu::create();

	this->dataCodeMenu->setVisible(false);

	this->hackableObjectsHud->addChild(this->dataCodeMenu, 999);
	this->addChild(this->healthBarFrame);
	this->addChild(this->heart);
	this->addChild(this->dialogNode);
	this->addChild(this->hackableObjectsHud);

	this->initializeListeners();
}

HUD::~HUD()
{
}

void HUD::onEnter()
{
	Node::onEnter();

	this->initializePositions();
}

void HUD::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->healthBarFrame->setPosition(Vec2(this->heart->getContentSize().width + this->healthBarFrame->getContentSize().width / 2, visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
	this->heart->setPosition(Vec2(this->heart->getContentSize().width / 2 + 16.0f, visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
}

void HUD::initializeListeners()
{
	EventListenerCustom* dialogListener = EventListenerCustom::create(DialogMenu::DialogOpenEvent, CC_CALLBACK_1(HUD::onDialogOpen, this));
	EventListenerCustom* hackableEditListener = EventListenerCustom::create(HackableObject::HackableObjectEditEvent, CC_CALLBACK_1(HUD::onHackableEdit, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hackableEditListener, this);
}

void HUD::registerHackableObject(HackableObject* hackableObject)
{
	if (hackableObject == nullptr)
	{
		return;
	}

	this->hackableObjectsHud->addChild(hackableObject);
}

void HUD::onHackableEdit(EventCustom* eventArgs)
{
	HackableObject::HackableObjectEditArgs*  args = (HackableObject::HackableObjectEditArgs*)(eventArgs->getUserData());

	Utils::pause(Director::getInstance()->getRunningScene());

	this->addChild(Mouse::claimInstance());

	this->dataCodeMenu->activate(args);
}

void HUD::onDialogOpen(EventCustom* event)
{
	DialogMenu::DialogOpenArgs* args = static_cast<DialogMenu::DialogOpenArgs*>(event->getUserData());

	this->dialogNode->removeAllChildren();
	this->dialogNode->addChild(args->dialogMenu);
}
