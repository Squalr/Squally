#include "SquallyUploadMars.h"

const Vec2 SquallyUploadMars::panOffset = Vec2(-608.0f, 256.0f);

SquallyUploadMars* SquallyUploadMars::create()
{
	SquallyUploadMars* instance = new SquallyUploadMars();

	instance->autorelease();

	return instance;
}

SquallyUploadMars::SquallyUploadMars()
{
	this->dialogueCount = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::create(Resources::Cutscenes_SquallyUploadMars_Scene);
	this->squally = Sprite::create(Resources::Cutscenes_SquallyUploadMars_SquallyPixel);

	this->squally->setOpacity(0);
	this->background->setOpacity(0);

	this->dialogue = Dialogue::create(Resources::Strings_Dialogue_CutsceneSquallyUploadMars, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
	
	this->dialoguePlate = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(InputManager::claimInstance());

	this->addChild(this->background);
	this->addChild(this->squally);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

SquallyUploadMars::~SquallyUploadMars()
{
}

void SquallyUploadMars::onEnter()
{
	Cutscene::onEnter();

	this->dialogue->showNextDialogue();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->runCutscene();
}

void SquallyUploadMars::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->squally->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void SquallyUploadMars::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(SquallyUploadMars::onDialogueShown, this));
}

void SquallyUploadMars::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void SquallyUploadMars::runCutscene()
{
	const float duration = 1.5f;
	Vec2 start = this->squally->getPosition();
	Vec2 end = start + Vec2(0.0f, 64.0f);

	this->squally->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(duration, end)),
		EaseSineInOut::create(MoveTo::create(duration, start)),
		nullptr,
		nullptr
	)));
}

void SquallyUploadMars::runCutscenePt2()
{
	this->squally->runAction(FadeIn::create(1.0f));
}

void SquallyUploadMars::runCutscenePt3()
{
	this->squally->runAction(FadeOut::create(1.0f));

	this->background->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(1.0f),
		nullptr
	));
}

void SquallyUploadMars::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

void SquallyUploadMars::onDialogueShown()
{
	this->dialogueCount++;

	this->dialogue->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			if (this->dialogueCount == 1)
			{
				this->runCutscenePt2();
			}

			if (this->dialogueCount == 2)
			{
				this->runCutscenePt3();
			}

			if (!this->dialogue->showNextDialogue())
			{
				this->dialogue->runAction(Sequence::create(
					DelayTime::create(5.0f),
					CallFunc::create([=]() {
					NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneSquallyUploadSpace);
				}),
				nullptr));
			}
		}),
		nullptr
	));
}
