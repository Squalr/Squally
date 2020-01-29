#include "PlatformerRubberbandingDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string PlatformerRubberbandingDeserializer::MapPropertyRubberBand = "rubber-band";

PlatformerRubberbandingDeserializer* PlatformerRubberbandingDeserializer::create()
{
	PlatformerRubberbandingDeserializer* instance = new PlatformerRubberbandingDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerRubberbandingDeserializer::PlatformerRubberbandingDeserializer() : super()
{
}

PlatformerRubberbandingDeserializer::~PlatformerRubberbandingDeserializer()
{
}

void PlatformerRubberbandingDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	int rubberBand = GameUtils::getKeyOrDefault(properties, PlatformerRubberbandingDeserializer::MapPropertyRubberBand, Value(1)).asInt();
}
