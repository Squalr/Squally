#include "AnswerStone.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanDoor.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AnswerStone::MapKey = "answer-stone";
const std::string AnswerStone::PropertyRegister = "register";
const std::string AnswerStone::PropertyCorrectValue = "correct-value";

AnswerStone* AnswerStone::create(ValueMap& properties)
{
	AnswerStone* instance = new AnswerStone(properties);

	instance->autorelease();

	return instance;
}

AnswerStone::AnswerStone(ValueMap& properties) : super(properties)
{
	std::string correctValueStr = GameUtils::getKeyOrDefault(this->properties, AnswerStone::PropertyCorrectValue, Value("0")).asString();

	this->correctValue = StrUtils::isInteger(correctValueStr) ? std::stoi(correctValueStr) : 0;
	this->answerStone = Sprite::create(ObjectResources::Puzzles_Stack_AnswerBlock);
	this->correctValueString = ConstantString::create(correctValueStr);
	this->correctValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->correctValueString);

	this->correctValueLabel->enableOutline(Color4B::BLACK, 4);

	this->addChild(this->answerStone);
	this->addChild(this->correctValueLabel);
}

AnswerStone::~AnswerStone()
{
}

void AnswerStone::initializePositions()
{
	super::initializePositions();

	this->answerStone->setPosition(Vec2(0.0f, 0.0f));
	this->correctValueLabel->setPosition(Vec2(0.0f, -2.0f));
}

int AnswerStone::getCorrectValue()
{
	return this->correctValue;
}
