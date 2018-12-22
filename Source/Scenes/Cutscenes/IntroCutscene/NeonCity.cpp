#include "NeonCity.h"

#include "Engine/Dialogue/DialogueLabel.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Scenes/Cutscenes/Objects/FlyingCar.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"

using namespace cocos2d;

const float NeonCity::vaporCorpOffset = 1280;

NeonCity* NeonCity::create(NeonCityScene neonCityScene)
{
	NeonCity* instance = new NeonCity(neonCityScene);

	instance->autorelease();

	return instance;
}

NeonCity::NeonCity(NeonCityScene neonCityScene)
{
	this->activeScene = neonCityScene;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->sky = LayerGradient::create(Color4B::ORANGE, Color4B(70, 0, 131, 255), Vec2(0.0f, 1.0f));
	this->darkFilter = LayerColor::create(Color4B::BLACK);
	this->starLayer = StarLayer::create(visibleSize);
	this->cityBackground = InfiniteParallaxNode::create(CutsceneResources::NeonCity_CityBackground);
	this->cityMidground = InfiniteParallaxNode::create(CutsceneResources::NeonCity_CityMidground);
	this->vaporCorp = Sprite::create(CutsceneResources::NeonCity_VaporCorp);
	this->dialoguePlate = LayerColor::create(Color4B(16, 0, 16, 255), visibleSize.width, 256.0f);
	this->junker1 = FlyingCar::create(FlyingCar::CarType::Junker, Vec2(196.0f, 0.0f), this->dialoguePlate->getContentSize().height);
	this->viper1 = FlyingCar::create(FlyingCar::CarType::Viper, Vec2(-256.0f, 0.0f), this->dialoguePlate->getContentSize().height);
	this->viper2 = FlyingCar::create(FlyingCar::CarType::Viper, Vec2(-256.0f, 0.0f), this->dialoguePlate->getContentSize().height);
	this->propeller1 = FlyingCar::create(FlyingCar::CarType::Propeller, Vec2(172.0f, 0.0f), this->dialoguePlate->getContentSize().height);
	this->cityForeground = InfiniteParallaxNode::create(CutsceneResources::NeonCity_CityForeground);

	// Make this larger than the screen to maximize the initial orange light initially
	this->sky->setContentSize(Size(visibleSize.width, visibleSize.height * 2.0f));
	this->darkFilter->setOpacity(0);
	this->starLayer->setCascadeOpacityEnabled(true);
	this->starLayer->setOpacity(0);

	this->sky->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->cityBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cityMidground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->vaporCorp->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->cityForeground->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->cityBackground->setScale(1.0f);
	this->cityMidground->setScale(1.0f);
	this->vaporCorp->setScale(1.0f);
	this->cityForeground->setScale(0.35f);

	this->escapeLabel = Label::createWithTTF("Press esc to skip", Localization::getPixelFont(), 20.0f, Size::ZERO, TextHAlignment::LEFT);

	this->escapeLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	switch (this->activeScene)
	{
		case NeonCityScene::Intro:
		{
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneNeonCity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			break;
		}
		case NeonCityScene::Return:
		{
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneNeonCityReturn, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			break;
		}
		case NeonCityScene::Singularity:
		{
			this->dialogue = DialogueLabel::create(StringResources::Dialogue_CutsceneNeonCitySingularity, Localization::getPixelFont(), Size(visibleSize.width - 48.0f, 256.0f - 48.0f));
			break;
		}
	}

	this->addChild(this->sky);
	this->addChild(this->darkFilter);
	this->addChild(this->starLayer);
	this->addChild(this->cityBackground);
	this->addChild(this->cityMidground);
	this->addChild(this->propeller1);
	this->addChild(this->vaporCorp);
	this->addChild(this->viper1);
	this->addChild(this->viper2);
	this->addChild(this->cityForeground);
	this->addChild(this->junker1);
	this->addChild(this->dialoguePlate);
	this->addChild(this->dialogue);
	this->addChild(this->escapeLabel);
}

NeonCity::~NeonCity()
{
}

void NeonCity::onEnter()
{
	CutsceneClip::onEnter();

	this->dialogue->showNextDialogue();

	switch (this->activeScene)
	{
		case NeonCityScene::Intro:
		{
			break;
		}
		case NeonCityScene::Return:
		{
			break;
		}
		case NeonCityScene::Singularity:
		{
			this->viper1->crash();

			this->propeller1->runAction(Sequence::create(
				DelayTime::create(2.5f),
				CallFunc::create([=]() {
					this->propeller1->crash();
				}),
				nullptr
			));

			this->junker1->runAction(Sequence::create(
				DelayTime::create(4.5f),
				CallFunc::create([=]() {
					this->junker1->crash();
				}),
				nullptr
			));

			this->viper2->runAction(Sequence::create(
				DelayTime::create(5.5f),
				CallFunc::create([=]() {
					this->viper2->crash();
				}),
				nullptr
			));

			break;
		}
	}

	this->cutscenePan();
}

void NeonCity::initializePositions()
{
	CutsceneClip::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->sky->setPosition(Vec2(0.0f, this->dialoguePlate->getContentSize().height));
	this->cityBackground->setPosition(Vec2(0.0f, this->dialoguePlate->getContentSize().height + 96.0f));
	this->cityMidground->setPosition(Vec2(212.0f, this->dialoguePlate->getContentSize().height));
	this->vaporCorp->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset, this->dialoguePlate->getContentSize().height));
	this->junker1->setPosition(Vec2(320.0f, visibleSize.height / 2.0f + 24.0f));
	this->viper1->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset + 640.0f, visibleSize.height / 2.0f + 172.0f));
	this->viper2->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset + 3072.0f, visibleSize.height / 2.0f + 480.0f));
	this->propeller1->setPosition(Vec2(visibleSize.width / 2.0f + NeonCity::vaporCorpOffset - 512.0f, visibleSize.height / 2.0f + 256.0f));
	this->cityForeground->setPosition(Vec2(0.0f, this->dialoguePlate->getContentSize().height));

	this->dialoguePlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialoguePlate->getContentSize().width / 2.0f, 0.0f));
	this->dialogue->setPosition(Vec2(24.0f, this->dialoguePlate->getContentSize().height - 24.0f));
	this->escapeLabel->setPosition(Vec2(visibleSize.width - 24.0f, 24.0f));
}

void NeonCity::initializeListeners()
{
	CutsceneClip::initializeListeners();

	this->dialogue->setDialogueShownCallback(CC_CALLBACK_0(NeonCity::onDialogueShown, this));
}

void NeonCity::onDialogueShown()
{
	switch (this->activeScene)
	{
		case NeonCityScene::Intro:
		{
			this->dialogue->runAction(Sequence::create(
				DelayTime::create(2.0f),
				CallFunc::create([=]() {
					if (!this->dialogue->showNextDialogue())
					{
						this->endCutsceneClip();
					}
				}),
				nullptr
			));

			break;
		}
		case NeonCityScene::Return:
		{
			this->dialogue->runAction(Sequence::create(
				DelayTime::create(3.0f),
				CallFunc::create([=]() {
					if (!this->dialogue->showNextDialogue())
					{
						this->endCutsceneClip();
					}
				}),
				nullptr
			));

			break;
		}
		case NeonCityScene::Singularity:
		{
			this->dialogue->runAction(Sequence::create(
				DelayTime::create(8.0f),
				CallFunc::create([=]() {
					if (!this->dialogue->showNextDialogue())
					{
						this->endCutsceneClip();
					}
				}),
				nullptr
			));

			break;
		}
	}
}

void NeonCity::cutscenePan()
{
	float moveDuration = 5.0f;

	switch (this->activeScene)
	{
		case NeonCityScene::Intro:
		{
			break;
		}
		case NeonCityScene::Return:
		case NeonCityScene::Singularity:
		{
			moveDuration = 0.0f;
			break;
		}
	}

	CallFunc* panCamera = CallFunc::create([=]()
	{
		const float deltaX = NeonCity::vaporCorpOffset;

		this->sky->runAction(EaseSineInOut::create(ScaleTo::create(moveDuration, 4.0f)));
		this->darkFilter->runAction(EaseSineInOut::create(FadeTo::create(moveDuration, 128)));
		this->starLayer->runAction(Sequence::create(
			DelayTime::create(2.0f),
			EaseSineIn::create(FadeTo::create(moveDuration - 2.0f, 255)),
			nullptr
		));
		this->cityBackground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityBackground->getPositionX() - deltaX + 256.0f, this->cityBackground->getPositionY()))));
		this->cityMidground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityMidground->getPositionX() - deltaX + 128.0f, this->cityMidground->getPositionY()))));
		this->vaporCorp->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->vaporCorp->getPositionX() - deltaX, this->vaporCorp->getPositionY()))));
		this->junker1->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->viper1->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->viper2->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->propeller1->runAction(EaseSineInOut::create(MoveBy::create(moveDuration, Vec2(-deltaX, 0.0f))));
		this->cityForeground->runAction(EaseSineInOut::create(MoveTo::create(moveDuration, Vec2(this->cityForeground->getPositionX() - deltaX - 64.0f, this->cityForeground->getPositionY()))));
	});

	this->runAction(Sequence::create(
		panCamera,
		nullptr
	));
}
