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
#include "Engine/Utils/MathUtils.h"
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
	
	this->animatedStone = Sprite::create(ObjectResources::Puzzles_Stack_StackBlock);
	this->animatedString = ConstantString::create(std::to_string(0));
	LocalizedLabel* animatedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->animatedString);
	
	animatedLabel->enableOutline(Color4B::BLACK, 2);
	animatedLabel->setPosition(Vec2(this->animatedStone->getContentSize()) / 2.0f + Vec2(0.0f, -6.0f));

	this->animatedStone->addChild(animatedLabel);

	for (auto next : values)
	{
		if (StrUtils::isInteger(next))
		{
			int value = std::stoi(next);

			this->push(value, false);
		}
	}

	for (auto next : this->valueStones)
	{
		this->addChild(next);
	}

	this->addChild(this->animatedStone);
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

	for (int index = 0; index < int(this->valueStones.size()); index++)
	{
		this->valueStones[index]->setPosition(this->getPositionForStone(index));
	}

	this->animatedStone->setPositionY(1536.0f);
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

		this->pop([=](int value)
		{
			std::string regStr = GameUtils::getKeyOrDefault(args, MayanDoor::PropertyRegister, Value("")).asString();
			ValueMap retArgs = ValueMap();

			retArgs[MayanDoor::PropertyRegister] = Value(regStr);
			retArgs[MayanDoor::PropertyValue] = Value(value);

			this->broadcastMapEvent(MayanDoor::MapEventPopRet + regStr, retArgs);
		});
	});

	this->listenForMapEvent(MayanDoor::MapEventPush, [=](ValueMap args)
	{
		int value = GameUtils::getKeyOrDefault(args, MayanDoor::PropertyValue, Value(0)).asInt();
		
		this->push(value);
	});
}

void StoneStack::push(int value, bool animate)
{
	const float Speed = 0.5f;
	const Vec2 Offset = Vec2(0.0f, 1536.0f);

	bool overFlow = int(this->values.size()) >= StoneStack::MaxStackSize - 1;
	int stoneIndex = int(this->values.size());
	Vec2 stonePosition = this->getPositionForStone(stoneIndex);
	this->animatedString->setString(std::to_string(value));

	if (animate)
	{
		this->animatedStone->setVisible(true);
		this->animatedStone->setPosition(stonePosition + Offset);
		this->animatedStone->runAction(Sequence::create(
			MoveTo::create(0.5f, stonePosition),
			CallFunc::create([=]()
			{
				if (overFlow)
				{
					this->animatedStone->setPosition(stonePosition + Offset);
					return;
				}

				this->values.push_back(value);
				this->valueStrings[stoneIndex]->setString(std::to_string(value));
				this->updateStackVisibility();
			}),
			nullptr
		));
	}
	else
	{
		if (overFlow)
		{
			return;
		}

		this->values.push_back(value);
		this->valueStrings[stoneIndex]->setString(std::to_string(value));
		this->updateStackVisibility();
	}
}

void StoneStack::pop(std::function<void(int)> callback)
{
	const float Speed = 0.5f;
	const Vec2 Offset = Vec2(0.0f, 1536.0f);

	if (this->values.empty())
	{
		return;
	}
	
	int stoneIndex = int(this->values.size() - 1);
	Vec2 stonePosition = this->getPositionForStone(stoneIndex);
	int value = this->values.back();
	this->values.pop_back();
	this->updateStackVisibility();

	this->broadcastMapEvent(MayanDoor::MapEventLockInteraction, ValueMap());

	this->animatedStone->setVisible(true);
	this->animatedStone->setPosition(stonePosition);
	this->animatedStone->runAction(Sequence::create(
		MoveTo::create(0.5f, stonePosition + Offset),
		CallFunc::create([=]()
		{
			this->animatedStone->setVisible(false);

			if (callback != nullptr)
			{
				callback(value);
			}

			this->broadcastMapEvent(MayanDoor::MapEventUnlockInteraction, ValueMap());
		}),
		nullptr
	));
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

Vec2 StoneStack::getPositionForStone(int index)
{
	index = MathUtils::clamp(index, 0, int(this->valueStones.size()) - 1);

	static const float ObjectHeight = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat();
	auto next = this->valueStones[index];
	const float StoneHeight = next->getContentSize().height;
	const float Spacing = 44.0f;

	return Vec2(0.0f, float(index) * Spacing + StoneHeight / 2.0f - ObjectHeight / 2.0f);
}
