#include "SquallyUploadSpace.h"

const Vec2 SquallyUploadSpace::panOffset = Vec2(-608.0f, 256.0f);

SquallyUploadSpace* SquallyUploadSpace::create()
{
	SquallyUploadSpace* instance = new SquallyUploadSpace();

	instance->autorelease();

	return instance;
}

SquallyUploadSpace::SquallyUploadSpace()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->starLayer = StarLayer::create(Size(visibleSize.width * 2.0f, visibleSize.height));
	this->mars = Sprite::create(Resources::Cutscenes_IntroSpace_Mars);
	this->beam = Node::create();
	this->satellite = Sprite::create(Resources::Cutscenes_SquallyUploadSpace_Satellite);
	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneSquallyUploadSpace, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));

	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->mars->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->beam->setCascadeOpacityEnabled(true);
	this->beam->setOpacity(0);

	this->addChild(InputManager::claimInstance());

	this->addChild(this->starLayer);
	this->addChild(this->mars);
	this->addChild(this->beam);
	this->addChild(this->satellite);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

SquallyUploadSpace::~SquallyUploadSpace()
{
}

void SquallyUploadSpace::onEnter()
{
	Cutscene::onEnter();

	this->dialogue->showNextDialogue();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->runCutscene();
}

void SquallyUploadSpace::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->mars->setPosition(Vec2(visibleSize.width / 2.0f - 128.0f, 48.0f));
	this->satellite->setPosition(Vec2(visibleSize.width / 2.0f + 64.0f, visibleSize.height / 2.0f + 128.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));

	DrawNode* beam1a = DrawNode::create(4.0f);
	beam1a->drawLine(this->mars->getPosition() + Vec2(66.0f, this->mars->getContentSize().height / 2.0f + 46.0f), this->satellite->getPosition(), Color4F::GREEN);

	DrawNode* beam1b = DrawNode::create(2.0f);
	beam1b->drawLine(this->mars->getPosition() + Vec2(66.0f, this->mars->getContentSize().height / 2.0f + 46.0f), this->satellite->getPosition(), Color4F::BLUE);

	DrawNode* beam2a = DrawNode::create(4.0f);
	beam2a->drawLine(this->satellite->getPosition(), Vec2(visibleSize.width, visibleSize.height + 256.0f), Color4F::GREEN);

	DrawNode* beam2b = DrawNode::create(2.0f);
	beam2b->drawLine(this->satellite->getPosition(), Vec2(visibleSize.width, visibleSize.height + 256.0f), Color4F::BLUE);

	this->beam->addChild(beam1a);
	this->beam->addChild(beam1b);
	this->beam->addChild(beam2a);
	this->beam->addChild(beam2b);
}

void SquallyUploadSpace::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(SquallyUploadSpace::onDialogueShown, this));
}

void SquallyUploadSpace::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void SquallyUploadSpace::runCutscene()
{
	this->beam->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(0.2f),
		DelayTime::create(0.5f),
		FadeOut::create(0.2f),
		nullptr
	));
}

void SquallyUploadSpace::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void SquallyUploadSpace::onDialogueShown()
{
	this->dialogue->runAction(Sequence::create(
		DelayTime::create(3.0f),
		CallFunc::create([=]() {
			if (!this->dialogue->showNextDialogue())
			{
				this->endCutscene();
			}
		}),
		nullptr
	));
}
