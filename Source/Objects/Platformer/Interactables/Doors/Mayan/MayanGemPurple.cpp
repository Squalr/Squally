#include "MayanGemPurple.h"

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

const std::string MayanGemPurple::MapKeyMayanGemPurple = "mayan-gem-purple";

MayanGemPurple* MayanGemPurple::create()
{
	MayanGemPurple* instance = new MayanGemPurple();

	instance->autorelease();

	return instance;
}

MayanGemPurple::MayanGemPurple() : super(ObjectResources::Doors_Mayan_PurpleGem, ObjectResources::Doors_Mayan_PurpleGemDisabled)
{
}

MayanGemPurple::~MayanGemPurple()
{
}
