#include "MiniMapObject.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string MiniMapObject::MapKey = "mini-map-object";
const std::string MiniMapObject::PropertyMiniMapHidden = "mini-map-hidden";
const std::string MiniMapObject::PropertyColor = "mini-map-color";
const std::string MiniMapObject::PropertyShape = "shape";
const std::string MiniMapObject::TagMiniMapObject = "mini-map-object";

MiniMapObject* MiniMapObject::create(ValueMap& properties, Color4B defaultColor)
{
	MiniMapObject* instance = new MiniMapObject(properties, defaultColor);

	instance->autorelease();

	return instance;
}

MiniMapObject::MiniMapObject(ValueMap& properties, Color4B defaultColor) : super(properties)
{
	this->drawColor = defaultColor;
	this->miniMapObject = DrawNode::create();
	this->isMiniMapHidden = GameUtils::getKeyOrDefault(this->properties, MiniMapObject::PropertyMiniMapHidden, Value(false)).asBool();

	this->addTag(MiniMapObject::TagMiniMapObject);
	
	Size size = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(16.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(16.0f)).asFloat()
	);

	std::string color = GameUtils::getKeyOrDefault(this->properties, MiniMapObject::PropertyColor, Value("")).asString();
	std::string shape = GameUtils::getKeyOrDefault(this->properties, MiniMapObject::PropertyShape, Value("")).asString();

	if (color == "red")
	{
		this->drawColor = Color4B::RED;
	}
	else if (color == "blue")
	{
		this->drawColor = Color4B::BLUE;
	}
	else if (color == "green")
	{
		this->drawColor = Color4B::GREEN;
	}
	else if (color == "yellow")
	{
		this->drawColor = Color4B::YELLOW;
	}
	else if (color == "purple")
	{
		this->drawColor = Color4B::PURPLE;
	}
	else if (color == "orange")
	{
		this->drawColor = Color4B::ORANGE;
	}
	else if (color == "magenta")
	{
		this->drawColor = Color4B::MAGENTA;
	}

	if (!this->isMiniMapHidden)
	{
		if (shape == "circle")
		{
			this->miniMapObject->drawSolidCircle(Vec2::ZERO, std::max(size.width, size.height), 0.0f, 16, Color4F(this->drawColor));
		}
		else
		{
			this->miniMapObject->drawSolidRect(-Vec2(size) / 2.0f, Vec2(size) / 2.0f, Color4F(this->drawColor));
		}
	}

	this->addChild(this->miniMapObject);
}

MiniMapObject::~MiniMapObject()
{
}
