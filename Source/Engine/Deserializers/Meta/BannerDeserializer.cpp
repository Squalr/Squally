#include "BannerDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/MapTitleBanner.h"
#include "Engine/Utils/GameUtils.h"

#include "Engine/Maps/Backgrounds/Background.h"

using namespace cocos2d;

const std::string BannerDeserializer::MapKeyBanner = "map-banner";

BannerDeserializer* BannerDeserializer::create()
{
	BannerDeserializer* instance = new BannerDeserializer();

	instance->autorelease();

	return instance;
}

BannerDeserializer::BannerDeserializer() : super()
{
}

BannerDeserializer::~BannerDeserializer()
{
}

void BannerDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string bannerName = GameUtils::getKeyOrDefault(properties, BannerDeserializer::MapKeyBanner, Value("")).asString();

	if (this->deserializers.find(bannerName) != deserializers.end())
	{
		owner->addChild(MapTitleBanner::create(deserializers[bannerName]()));
	}
}
