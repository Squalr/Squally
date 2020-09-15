#include "MiniMapObject.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"
#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinderDeserializer.h"

using namespace cocos2d;

const std::string MiniMapObject::MapKey = "mini-map-object";
const std::string MiniMapObject::PropertyOriginalId = "original-uuid";
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

MiniMapObject::MiniMapObject(ValueMap& properties, Color4B defaultColor) : super(MiniMapObject::transformUUID(properties))
{
	this->drawColor = defaultColor;
	this->depthVisibilityNode = Node::create();
	this->rotatorNode = Node::create();
	this->drawNode = DrawNode::create();
	this->isMiniMapHidden = GameUtils::getKeyOrDefault(this->properties, MiniMapObject::PropertyMiniMapHidden, Value(false)).asBool();

	this->addTag(MiniMapObject::TagMiniMapObject);
	this->properties[GameObject::MapKeyQueryable] = Value(false);
	
	Size size = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(16.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(16.0f)).asFloat()
	);

	this->drawNode->setContentSize(size);
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
			this->drawNode->drawSolidCircle(Vec2::ZERO, std::max(size.width, size.height), 0.0f, 16, Color4F(this->drawColor));
		}
		else
		{
			this->drawNode->drawSolidRect(-Vec2(size) / 2.0f, Vec2(size) / 2.0f, Color4F(this->drawColor));
		}
	}
	
	this->depthVisibilityNode->addChild(this->rotatorNode);
	this->rotatorNode->addChild(this->drawNode);
	this->addChild(this->depthVisibilityNode);
}

MiniMapObject::~MiniMapObject()
{
}

void MiniMapObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	std::string identifier = GameObject::BuildUUID(this->properties.at(GameObject::MapKeyMetaMapIdentifier).asString(), this->properties.at(MiniMapObject::PropertyOriginalId).asString());

	ObjectEvents::WatchForObject<GameObject>(this, [=](GameObject* object)
	{
		MiniMapObjectBinder* binder = MiniMapObjectBinderDeserializer::Deserialize(GameUtils::getKeyOrDefault(object->properties, GameObject::MapKeyName, Value("")).asString());

		binder->bindTo(this, object);

		this->addChild(binder);

	}, identifier);
}

cocos2d::ValueMap& MiniMapObject::transformUUID(cocos2d::ValueMap& properties)
{
	properties[MiniMapObject::PropertyOriginalId] = properties[GameObject::MapKeyId];
	properties[GameObject::MapKeyId] = Value(properties[GameObject::MapKeyId].asString() + "_MINI_MAP");
	properties[GameObject::MapKeyTags] = Value("");

	return properties;
}
