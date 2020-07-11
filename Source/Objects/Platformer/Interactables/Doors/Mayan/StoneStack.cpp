#include "StoneStack.h"

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

using namespace cocos2d;

const std::string StoneStack::MapKey = "stone-stack";
const std::string StoneStack::PropertyValues = "values";
const int StoneStack::MaxStackSize = 6;

StoneStack* StoneStack::create(ValueMap& properties)
{
	StoneStack* instance = new StoneStack(properties);

	instance->autorelease();

	return instance;
}

StoneStack::StoneStack(ValueMap& properties) : super(properties)
{
	this->valueStones = std::vector<cocos2d::Sprite*>();
	this->values = std::vector<int>();
	this->valueStrings = std::vector<ConstantString*>();
	std::vector<std::string> values = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, StoneStack::PropertyValues, Value("")).asString(), ", ", false);

	for (int index = 0; index < StoneStack::MaxStackSize; index++)
	{
		Sprite* stone = Sprite::create(ObjectResources::Puzzles_Stack_StackBlock);
		ConstantString* str = ConstantString::create(std::to_string(0));
		LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, str);

		label->enableOutline(Color4B::BLACK, 2);
		label->setPosition(Vec2(stone->getContentSize()) / 2.0f + Vec2(0.0f, -6.0f));

		stone->addChild(label);
		this->valueStones.push_back(stone);
		this->valueStrings.push_back(str);
	}

	for (auto next : values)
	{
		if (StrUtils::isInteger(next))
		{
			int value = std::stoi(next);

			this->push(value);
		}
	}

	for (auto next : this->valueStones)
	{
		this->addChild(next);
	}
}

StoneStack::~StoneStack()
{
}

void StoneStack::onEnter()
{
	super::onEnter();
}

void StoneStack::initializePositions()
{
	super::initializePositions();

	const float ObjectHeight = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat();

	for (int index = 0; index < int(this->valueStones.size()); index++)
	{
		auto next = this->valueStones[index];
		const float StoneHeight = next->getContentSize().height;
		const float Spacing = 44.0f;

		next->setPosition(Vec2(
			0.0f,
			float(index) * Spacing + StoneHeight / 2.0f - ObjectHeight / 2.0f
		));
	}
}

void StoneStack::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(MayanDoor::MapEventPop, [=](ValueMap args)
	{
		if (this->values.empty())
		{
			return;
		}

		std::string regStr = GameUtils::getKeyOrDefault(args, MayanDoor::PropertyRegister, Value("")).asString();
		ValueMap retArgs = ValueMap();

		retArgs[MayanDoor::PropertyRegister] = Value(regStr);
		retArgs[MayanDoor::PropertyValue] = Value(this->pop());

		this->broadcastMapEvent(MayanDoor::MapEventPopRet + regStr, retArgs);
	});

	this->listenForMapEvent(MayanDoor::MapEventPush, [=](ValueMap args)
	{
		int value = GameUtils::getKeyOrDefault(args, MayanDoor::PropertyValue, Value(0)).asInt();
		
		this->push(value);
	});
}

void StoneStack::push(int value)
{
	if (int(this->values.size()) >= StoneStack::MaxStackSize - 1)
	{
		return;
	}

	this->values.push_back(value);
	this->valueStrings[int(this->values.size() - 1)]->setString(std::to_string(value));
	this->updateStackVisibility();
}

int StoneStack::pop()
{
	if (this->values.empty())
	{
		return 0;
	}

	int value = this->values.back();
	this->values.pop_back();
	this->updateStackVisibility();

	return value;
}

void StoneStack::updateStackVisibility()
{
	for (auto next : this->valueStones)
	{
		next->setVisible(false);
	}

	for (int index = 0; index < int(this->values.size()); index++)
	{
		this->valueStones[index]->setVisible(true);
	}
}
