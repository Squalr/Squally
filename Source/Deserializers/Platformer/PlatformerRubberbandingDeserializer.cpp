#include "PlatformerRubberbandingDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

const std::string PlatformerRubberbandingDeserializer::PropertyRubberBand = "rubber-band";

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
	if (GameUtils::keyExists(properties, PlatformerRubberbandingDeserializer::PropertyRubberBand))
	{
		const int rubberBand = GameUtils::getKeyOrDefault(properties, PlatformerRubberbandingDeserializer::PropertyRubberBand, Value(1)).asInt();
		
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyLevelRubberband, Value(rubberBand));
	}
}
