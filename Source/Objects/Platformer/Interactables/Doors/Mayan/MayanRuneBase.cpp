#include "MayanRuneBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

MayanRuneBase::MayanRuneBase(std::string emblemResource, std::string emblemResourceDisabled) : super()
{
	this->emblemFrameGlowing = Sprite::create(ObjectResources::Doors_Mayan_GemFrameGlowing);
	this->emblemFrame = Sprite::create(ObjectResources::Doors_Mayan_GemFrame);
	this->emblemDisabled = Sprite::create(emblemResourceDisabled);
	this->emblem = Sprite::create(emblemResource);
	this->answerString = ConstantString::create("?");
	this->answerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, this->answerString);

	this->answerLabel->enableOutline(Color4B::BLACK, 3);

	this->disableGem();
	this->emblemFrameGlowing->setOpacity(0);

	this->addChild(this->emblemFrameGlowing);
	this->addChild(this->emblemFrame);
	this->addChild(this->emblemDisabled);
	this->addChild(this->emblem);
	this->addChild(this->answerLabel);
}

MayanRuneBase::~MayanRuneBase()
{
}

void MayanRuneBase::onEnter()
{
	super::onEnter();

	this->answerLabel->setTextColor(this->getGemFontColor());

	this->answerLabel->runAction(RepeatForever::create(
		Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.0f, Vec2(0.0f, 64.0f))),
			EaseSineInOut::create(MoveTo::create(1.0f, Vec2(0.0f, 56.0f))),
			nullptr
		)
	));
}

void MayanRuneBase::initializePositions()
{
	super::initializePositions();

	this->answerLabel->setPosition(Vec2(0.0f, 56.0f));
}

void MayanRuneBase::loadAnswer(int answer)
{
	this->answerString->setString(std::to_string(answer));
}

void MayanRuneBase::runFX()
{
	this->emblemFrameGlowing->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		FadeTo::create(0.5f, 0),
		nullptr
	));
}

void MayanRuneBase::hideText()
{
	this->answerLabel->runAction(FadeTo::create(0.25f, 0));
}

void MayanRuneBase::showText()
{
	this->answerLabel->runAction(FadeTo::create(0.25f, 255));
}

void MayanRuneBase::enableGem()
{
	this->answerLabel->setVisible(true);
	this->emblemDisabled->setVisible(false);
	this->emblem->setVisible(true);
}

void MayanRuneBase::disableGem()
{
	this->answerLabel->setVisible(false);
	this->emblemDisabled->setVisible(true);
	this->emblem->setVisible(false);
}
