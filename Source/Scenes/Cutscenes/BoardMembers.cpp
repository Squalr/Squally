#include "BoardMembers.h"

const Vec2 BoardMembers::panOffset = Vec2(-608.0f, 256.0f);

BoardMembers* BoardMembers::create()
{
	BoardMembers* instance = new BoardMembers();

	instance->autorelease();

	return instance;
}

BoardMembers::BoardMembers()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(Resources::Cutscenes_BoardMembers_BoardMembers);

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneBoardMembers, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->addChild(this->background);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

BoardMembers::~BoardMembers()
{
}

void BoardMembers::onEnter()
{
	Cutscene::onEnter();

	this->dialogue->showNextDialogue();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void BoardMembers::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void BoardMembers::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(BoardMembers::onDialogueShown, this));
}

void BoardMembers::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void BoardMembers::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void BoardMembers::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			if (!this->dialogue->showNextDialogue())
			{
				NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneVaporLabs);
			}
		}),
		nullptr
	));
}
