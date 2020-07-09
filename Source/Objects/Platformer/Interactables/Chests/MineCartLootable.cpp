#include "MineCartLootable.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MineCartLootable::MapKey = "mine-cart-lootable";
const std::string MineCartLootable::PropertyFill = "fill";
const std::string MineCartLootable::PropertyColor = "color";

MineCartLootable* MineCartLootable::create(cocos2d::ValueMap& properties)
{
	MineCartLootable* instance = new MineCartLootable(properties);

	instance->autorelease();

	return instance;
}

MineCartLootable::MineCartLootable(cocos2d::ValueMap& properties) : super(properties, Size(240.0f, 184.0f))
{
	this->parseFill();
	this->parseColor();

	Node* chestOpenFrontSprite = this->buildCart(false);
	Node* chestClosedSprite = this->buildCart(true);
	
	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

MineCartLootable::~MineCartLootable()
{
}

void MineCartLootable::parseColor()
{
	std::string color = GameUtils::getKeyOrDefault(this->properties, MineCartLootable::PropertyColor, Value("")).asString();

	if (color == "blue")
	{
		this->cartColor = CartColor::Blue;
	}
	else // if (color == "brown")
	{
		this->cartColor = CartColor::Brown;
	}
}

void MineCartLootable::parseFill()
{
	std::string fill = GameUtils::getKeyOrDefault(this->properties, MineCartLootable::PropertyFill, Value("")).asString();

	if (fill == "diamond")
	{
		this->cartFill = Fill::Diamond;
	}
	else if (fill == "gold")
	{
		this->cartFill = Fill::Gold;
	}
	else // if (fill == "coal")
	{
		this->cartFill = Fill::Coal;
	}
}

Node* MineCartLootable::buildCart(bool withFill)
{
	Node* container = Node::create();
	Sprite* fill = nullptr;
	Sprite* body = Sprite::create(this->cartColor == CartColor::Brown ? ObjectResources::Interactive_MineCarts_Body1 : ObjectResources::Interactive_MineCarts_Body2);
	Sprite* wheelFront = Sprite::create(ObjectResources::Interactive_MineCarts_WheelFront);
	Sprite* wheelBack = Sprite::create(ObjectResources::Interactive_MineCarts_WheelBack);

	if (withFill)
	{
		switch(this->cartFill)
		{
			case Fill::Coal:
			{
				fill = Sprite::create(ObjectResources::Interactive_MineCarts_FillCoal);
				fill->setPosition(Vec2(0.0f, 96.0f));
				break;
			}
			case Fill::Gold:
			{
				fill = Sprite::create(ObjectResources::Interactive_MineCarts_FillGold);
				fill->setPosition(Vec2(0.0f, 96.0f));
				break;
			}
			case Fill::Diamond:
			{
				fill = Sprite::create(ObjectResources::Interactive_MineCarts_FillDiamond);
				fill->setPosition(Vec2(8.0f, 96.0f));
				break;
			}
		}
	}

	wheelBack->setPosition(Vec2(-32.0f, -64.0f));
	wheelFront->setPosition(Vec2(32.0f, -69.0f));

	if (fill != nullptr)
	{
		container->addChild(fill);
	}

	container->addChild(body);
	container->addChild(wheelFront);
	container->addChild(wheelBack);

	return container;
}
