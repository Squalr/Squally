////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Goblin.h"

#include "Resources/EntityResources.h"

const std::string Goblin::MapKeyGoblin = "goblin";

using namespace cocos2d;

Goblin* Goblin::deserialize(cocos2d::ValueMap* initProperties)
{
	Goblin* instance = new Goblin(initProperties);

	instance->autorelease();

	return instance;
}

Goblin::Goblin(cocos2d::ValueMap* initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_Goblin_Animations,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, -220.0f),
	10,
	10)
{
}

Goblin::~Goblin()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Dialogue/SpeechBubble.h"

#include "Strings/Dialogue/Helpers/Goblin/PendulumTutorial1.h"
#include "Strings/Dialogue/Helpers/Goblin/PendulumTutorial2.h"

void Goblin::onEnter()
{
	PlatformerEntity::onEnter();

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Helpers_Goblin_PendulumTutorial1::create(), SpeechBubble::Direction::Auto);
		}),
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Helpers_Goblin_PendulumTutorial2::create(), SpeechBubble::Direction::Auto);
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
