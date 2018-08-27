#include "VaporCorp.h"

const Vec2 VaporCorp::panOffset = Vec2(-608.0f, 256.0f);

VaporCorp* VaporCorp::create()
{
	VaporCorp* instance = new VaporCorp();

	instance->autorelease();

	return instance;
}

VaporCorp::VaporCorp()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentLayer = Node::create();
	this->sky = LayerGradient::create(Color4B(70, 0, 131, 255), Color4B(64, 0, 64, 255), Vec2(0.0f, 1.0f));
	this->starLayer = StarLayer::create();
	this->cityView = Sprite::create(Resources::Cutscenes_VaporCorp_CityView);
	this->background = Sprite::create(Resources::Cutscenes_VaporCorp_Lab);
	this->console = Sprite::create(Resources::Cutscenes_VaporCorp_Controls);
	this->monitor = Sprite::create(Resources::Cutscenes_VaporCorp_Monitor);
	this->scientist = Sprite::create(Resources::Cutscenes_VaporCorp_Scientist);

	this->sky->setContentSize(Size(480.0f, 256.0f));

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneNeonCity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->contentLayer->addChild(this->sky);
	this->addChild(this->starLayer);
	this->contentLayer->addChild(this->cityView);
	this->contentLayer->addChild(this->background);
	this->contentLayer->addChild(this->console);
	this->contentLayer->addChild(this->scientist);
	this->contentLayer->addChild(this->monitor);
	this->addChild(this->contentLayer);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

VaporCorp::~VaporCorp()
{
}

void VaporCorp::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->cutscenePan();
}

void VaporCorp::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentLayer->setPosition(VaporCorp::panOffset);
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->sky->setPosition(Vec2(visibleSize.width / 2.0f - this->sky->getContentSize().width / 2.0f, visibleSize.height / 2.0f - this->sky->getContentSize().height / 2.0f));
	this->cityView->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->console->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 164.0f));
	this->scientist->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 188.0f));
	this->monitor->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 320.0f));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void VaporCorp::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(VaporCorp::onDialogueShown, this));
}

void VaporCorp::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void VaporCorp::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void VaporCorp::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			this->dialogue->showNextDialogue();
		}),
		nullptr
	));
}

void VaporCorp::cutscenePan()
{
	this->contentLayer->runAction(EaseSineInOut::create(MoveTo::create(5.0f, Vec2::ZERO)));
}
