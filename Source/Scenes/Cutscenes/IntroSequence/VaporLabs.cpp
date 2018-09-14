#include "VaporLabs.h"

const Vec2 VaporLabs::panOffset = Vec2(-512.0f, 24.0f);

VaporLabs* VaporLabs::create()
{
	VaporLabs* instance = new VaporLabs();

	instance->autorelease();

	return instance;
}

VaporLabs::VaporLabs()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentLayer = Node::create();
	this->sky = LayerGradient::create(Color4B(70, 0, 131, 255), Color4B(64, 0, 64, 255), Vec2(0.0f, 1.0f));
	this->starLayer = StarLayer::create(Size(480.0f, 256.0f));
	this->cityView = Sprite::create(Resources::Cutscenes_VaporLabs_CityView);
	this->background = Sprite::create(Resources::Cutscenes_VaporLabs_Lab);
	this->console = Sprite::create(Resources::Cutscenes_VaporLabs_Controls);
	this->monitor = Sprite::create(Resources::Cutscenes_VaporLabs_Monitor);
	this->scientist = Sprite::create(Resources::Cutscenes_VaporLabs_Scientist);
	this->siren = LayerColor::create(Color4B(255, 0, 0, 0));

	this->sky->setContentSize(Size(480.0f, 256.0f));

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneVaporLabs, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->contentLayer->addChild(this->sky);
	this->contentLayer->addChild(this->starLayer);
	this->contentLayer->addChild(this->cityView);
	this->contentLayer->addChild(this->background);
	this->contentLayer->addChild(this->console);
	this->contentLayer->addChild(this->scientist);
	this->contentLayer->addChild(this->monitor);
	this->addChild(this->contentLayer);
	this->addChild(this->siren);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

VaporLabs::~VaporLabs()
{
}

void VaporLabs::onEnter()
{
	Cutscene::onEnter();

	this->dialogue->showNextDialogue();

	this->runCutscene();
}

void VaporLabs::initializePositions()
{
	Cutscene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentLayer->setPosition(VaporLabs::panOffset);
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->starLayer->setPosition(Vec2(visibleSize.width / 2.0f - this->starLayer->getContentSize().width / 2.0f, visibleSize.height / 2.0f - this->starLayer->getContentSize().height / 2.0f));
	this->sky->setPosition(Vec2(visibleSize.width / 2.0f - this->sky->getContentSize().width / 2.0f, visibleSize.height / 2.0f - this->sky->getContentSize().height / 2.0f));
	this->cityView->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->console->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 164.0f));
	this->scientist->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 188.0f));
	this->monitor->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 320.0f));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void VaporLabs::initializeListeners()
{
	Cutscene::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(VaporLabs::onDialogueShown, this));
}

void VaporLabs::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(4.0f),
		CallFunc::create([=]() {
			if (!this->dialogue->showNextDialogue())
			{
				this->endCutscene();
			}
		}),
		nullptr
	));
}

void VaporLabs::runCutscene()
{
	this->contentLayer->runAction(EaseSineInOut::create(MoveTo::create(4.0f, Vec2::ZERO)));

	const float fadeSpeed = 0.75f;
	const int endFade = 96;
	const int startFade = 16;

	this->siren->runAction(Sequence::create(
		DelayTime::create(2.5f),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		FadeTo::create(fadeSpeed, endFade),
		FadeTo::create(fadeSpeed, startFade),
		nullptr
	));
}
