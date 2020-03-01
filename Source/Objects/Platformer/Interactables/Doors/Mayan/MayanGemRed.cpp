#include "MayanGemRed.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string MayanGemRed::MapKeyMayanGemRed = "mayan-gem-red";

MayanGemRed* MayanGemRed::create()
{
	MayanGemRed* instance = new MayanGemRed();

	instance->autorelease();

	return instance;
}

MayanGemRed::MayanGemRed() : super(ObjectResources::Doors_Mayan_RedGem, ObjectResources::Doors_Mayan_RedGemDisabled)
{
}

MayanGemRed::~MayanGemRed()
{
}
