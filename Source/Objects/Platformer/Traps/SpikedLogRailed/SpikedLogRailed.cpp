#include "SpikedLogRailed.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/SpikedLogRailed/SpikedLogRailedGenericPreview.h"
#include "Objects/Platformer/Traps/SpikedLogRailed/SpikedLogRailedSetRotationPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_MOVE 1

const std::string SpikedLogRailed::MapKey = "spiked-log-railed";

SpikedLogRailed* SpikedLogRailed::create(ValueMap& properties)
{
	SpikedLogRailed* instance = new SpikedLogRailed(properties);

	instance->autorelease();

	return instance;
}

SpikedLogRailed::SpikedLogRailed(ValueMap& properties) : super(properties)
{
	this->beam = Sprite::create(ObjectResources::Traps_SpikedLogRailed_Beam);
	this->spikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(CSize(32.0f, 480.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->logCollision = CollisionObject::create(CollisionObject::createBox(CSize(128.0f, 512.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->animationLength = SmartAnimationSequenceNode::GetAnimationLength(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);

	this->spikedLog->addChild(this->spikeCollision);
	this->spikedLog->addChild(this->logCollision);
	this->addChild(this->beam);
	this->addChild(this->spikedLog);
}

SpikedLogRailed::~SpikedLogRailed()
{
}

void SpikedLogRailed::onEnter()
{
	super::onEnter();

	this->onFrameComplete();
}

void SpikedLogRailed::initializePositions()
{
	super::initializePositions();

	// this->spikedLog->setPositionY(this->properties->at(GameObject::MapKeyHeight).asFloat() / 2.0f);
	this->logCollision->setPosition(Vec2(this->spikedLog->getContentSize().width / 2.0f, 0.0f));
	this->spikeCollision->setPosition(Vec2(this->spikedLog->getContentSize().width / 2.0f, 0.0f));
}

Vec2 SpikedLogRailed::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void SpikedLogRailed::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_MOVE,
			HackableCode::HackableCodeInfo(
				SpikedLogRailed::MapKey,
				Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_IncrementAnimationFrame::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Banner,
				LazyNode<HackablePreview>::create([=](){ return SpikedLogRailedSetRotationPreview::create(); }),
				{
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_RegisterEcx::create() },
				},
				int(HackFlags::None),
				16.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_CommentOptions::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create())) + 
						"inc ecx\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_CommentOptions::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create())) + 
						"inc rcx\n"
					)
				},
				true
			)
		},
	};

	auto incrementAnimationFunc = &SpikedLogRailed::incrementSpikedLogRailedAnimation;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)incrementAnimationFunc, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* SpikedLogRailed::createDefaultPreview()
{
	return SpikedLogRailedGenericPreview::create();
}

void SpikedLogRailed::onFrameComplete()
{
	this->currentAnimationIndex = MathUtils::wrappingNormalize(incrementSpikedLogRailedAnimation(this->currentAnimationIndex, this->animationLength), 0, this->animationLength - 1);

	this->spikedLog->playSingleFrame(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00, this->currentAnimationIndex, 0.05f, [=]()
	{
		this->onFrameComplete();
	});
}

NO_OPTIMIZE int SpikedLogRailed::incrementSpikedLogRailedAnimation(int count, int max)
{
	this->spikeCollision->setPhysicsFlagEnabled(true);
	float offsetX = 0;

	switch(count)
	{
		case 1:
		{
			offsetX = 32.0f;
			break;
		}
		case 2:
		{
			offsetX = 96.0f;
			break;
		}
		case 3:
		{
			offsetX = 72.0f;
			break;
		}
		case 7:
		{
			offsetX = -72.0f;
			break;
		}
		case 8:
		{
			offsetX = -96.0f;
			break;
		}
		case 9:
		{
			offsetX = -32.0f;
			break;
		}
		default:
		{
			this->spikeCollision->setPhysicsFlagEnabled(false);
		}
	}

	this->spikeCollision->setPositionX(offsetX);

	static volatile int countLocal;

	countLocal = count;

	ASM(push ZCX)
	ASM_MOV_REG_VAR(ecx, countLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MOVE);
	ASM(inc ZCX)
	ASM_NOP6();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(countLocal, ecx);
	ASM(pop ZCX);

	HACKABLES_STOP_SEARCH();

	return countLocal;
}
END_NO_OPTIMIZE
