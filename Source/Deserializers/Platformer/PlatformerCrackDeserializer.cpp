#include "PlatformerCrackDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Engine/Maps/Backgrounds/Background.h"

#include "Resources/BackgroundResources.h"

using namespace cocos2d;

const std::string PlatformerCrackDeserializer::MapKey = "show-cracks";

PlatformerCrackDeserializer* PlatformerCrackDeserializer::create()
{
	PlatformerCrackDeserializer* instance = new PlatformerCrackDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerCrackDeserializer::PlatformerCrackDeserializer() : super()
{
}

PlatformerCrackDeserializer::~PlatformerCrackDeserializer()
{
}

void PlatformerCrackDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	bool showCracks = GameUtils::getKeyOrDefault(properties, PlatformerCrackDeserializer::MapKey, Value(false)).asBool();

	if (!showCracks)
	{
		return;
	}

	int crackProgress = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyCrackProgress, Value(0)).asInt();
	Sprite* sprite = nullptr;

	// For decor, simply grab the resource of the same name of the object type
	switch(crackProgress)
	{
		case 0:
		{
			sprite = Sprite::create(BackgroundResources::Cracks_CrackSmallBlack);
			sprite->setPosition(Vec2(1024.0f, 512.0f));
			//break;
		}
		case 1:
		{
			sprite = Sprite::create(BackgroundResources::Cracks_CrackMediumBlack);
			sprite->setPosition(Vec2(1024.0f - 32.0f, 512.0f));
			// break;
		}
		default:
		case 2:
		{
			sprite = Sprite::create(BackgroundResources::Cracks_CrackLargeBlack);
			sprite->setPosition(Vec2(1024.0f - 192.0f, 512.0f + 64.0f));
			break;
		}
	}

	owner->addChild(Background::create(sprite));
}
