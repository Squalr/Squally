#include "BackgroundDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

#include "Engine/Maps/Backgrounds/Background.h"

using namespace cocos2d;

const std::string BackgroundDeserializer::MapKeyBackground = "background";

BackgroundDeserializer* BackgroundDeserializer::create()
{
	BackgroundDeserializer* instance = new BackgroundDeserializer();

	instance->autorelease();

	return instance;
}

BackgroundDeserializer::BackgroundDeserializer() : super()
{
}

BackgroundDeserializer::~BackgroundDeserializer()
{
}

void BackgroundDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string background = GameUtils::getKeyOrDefault(properties, BackgroundDeserializer::MapKeyBackground, Value("")).asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* sprite = Sprite::create("Private/Platformer/Backgrounds/" + background + ".png");

	owner->addChild(Background::create(sprite));
}
