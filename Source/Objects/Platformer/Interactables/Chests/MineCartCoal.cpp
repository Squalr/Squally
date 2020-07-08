#include "MineCartCoal.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MineCartCoal::MapKey = "mine-cart-coal";
const std::string MineCartCoal::PropertyColor = "color";

MineCartCoal* MineCartCoal::create(cocos2d::ValueMap& properties)
{
	MineCartCoal* instance = new MineCartCoal(properties);

	instance->autorelease();

	return instance;
}

MineCartCoal::MineCartCoal(cocos2d::ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	if (GameUtils::getKeyOrDefault(this->properties, MineCartCoal::PropertyColor, Value(false)).asBool())
	{
		this->cartColor = CartColor::Blue;
	}
	else
	{
		this->cartColor = CartColor::Brown;
	}

	Node* chestOpenFrontSprite = this->buildCart(false);
	Node* chestClosedSprite = this->buildCart(true);
	
	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

MineCartCoal::~MineCartCoal()
{
}

Node* MineCartCoal::buildCart(bool withFill)
{
	Node* container = Node::create();
	Sprite* fill = withFill ? Sprite::create(ObjectResources::Interactive_MineCarts_FillCoal) : nullptr;
	Sprite* body =  Sprite::create(ObjectResources::Interactive_MineCarts_Body1);
	Sprite* wheelFront = Sprite::create(ObjectResources::Interactive_MineCarts_WheelFront);
	Sprite* wheelBack = Sprite::create(ObjectResources::Interactive_MineCarts_WheelBack);

	wheelBack->setPosition(Vec2(-32.0f, -64.0f));
	wheelFront->setPosition(Vec2(32.0f, -69.0f));

	if (fill != nullptr)
	{
		fill->setPosition(Vec2(0.0f, 96.0f));
		container->addChild(fill);
	}

	container->addChild(body);
	container->addChild(wheelFront);
	container->addChild(wheelBack);

	return container;
}
