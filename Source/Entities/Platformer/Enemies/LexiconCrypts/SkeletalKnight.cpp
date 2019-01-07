////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalKnight.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SkeletalKnight::MapKeySkeletalKnight = "skeletal-knight";

SkeletalKnight* SkeletalKnight::deserialize(cocos2d::ValueMap* initProperties)
{
	SkeletalKnight* instance = new SkeletalKnight(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalKnight::SkeletalKnight(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LexiconCrypts_SkeletalKnight_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(212.0f, 280.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

SkeletalKnight::~SkeletalKnight()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Dialogue/SpeechBubble.h"

#include "Strings/Dialogue/Enemies/BattleCries/DieMortal.h"

void SkeletalKnight::onEnter()
{
	PlatformerEntity::onEnter();

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Enemies_BattleCries_DieMortal::create(), SpeechBubble::Direction::Auto);
		}),
		DelayTime::create(2.5f),
		CallFunc::create([=]()
		{
			this->speechBubble->hideDialogue();
		}),
		nullptr
	));
}

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
