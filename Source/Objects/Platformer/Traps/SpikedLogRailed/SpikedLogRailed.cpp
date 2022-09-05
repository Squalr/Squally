#include "SpikedLogRailed.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Traps/SpikedLogRailed/SpikedLogRailedGenericPreview.h"
#include "Objects/Platformer/Traps/SpikedLogRailed/SpikedLogRailedSetRotationPreview.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_MOVE 1

const std::string SpikedLogRailed::MapKey = "spiked-log-railed";
const std::string SpikedLogRailed::PropertyInverse = "inverse";

SpikedLogRailed* SpikedLogRailed::create(ValueMap& properties)
{
	SpikedLogRailed* instance = new SpikedLogRailed(properties);

	instance->autorelease();

	return instance;
}

SpikedLogRailed::SpikedLogRailed(ValueMap& properties) : super(properties)
{
	this->root = Node::create();
	this->beam = Sprite::create(ObjectResources::Traps_SpikedLogRailed_Beam);
	this->spikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(CSize(192.0f, 480.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->logCollision = CollisionObject::create(CollisionObject::createBox(CSize(128.0f, 512.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->squally = nullptr;
	this->railSize = CSize(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat());
	this->inverse = GameUtils::getKeyOrDefault(this->properties, SpikedLogRailed::PropertyInverse, Value(false)).asBool();
	this->spikedLog->addChild(this->spikeCollision);
	this->spikedLog->addChild(this->logCollision);
	this->root->addChild(this->beam);
	this->root->addChild(this->spikedLog);
	this->addChild(this->root);
}

SpikedLogRailed::~SpikedLogRailed()
{
}

void SpikedLogRailed::onEnter()
{
	super::onEnter();

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	this->spikedLog->playAnimationRepeat(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00, 0.05f);
	this->rootPosition = this->root->getPosition();
}

void SpikedLogRailed::update(float dt)
{
	this->moveRailedSpikes(dt);
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
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_RegisterEcx::create() },
					{ HackableCode::Register::zdx, Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_RegisterEcx::create() },
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
						"cmp ebx, 0\n" +
						"cmovg eax, esi\n" +
						"cmovl eax, edi\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Objects_SpikedLog_IncrementAnimationFrame_CommentOptions::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create())) + 
						"cmp rbx, 0\n" +
						"cmovg rax, rsi\n" +
						"cmovl rax, rdi\n"
					)
				},
				true
			)
		},
	};

	auto moveRailedSpikesFunc = &SpikedLogRailed::moveRailedSpikes;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)moveRailedSpikesFunc, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* SpikedLogRailed::createDefaultPreview()
{
	return SpikedLogRailedGenericPreview::create();
}

NO_OPTIMIZE void SpikedLogRailed::moveRailedSpikes(float dt)
{
	static volatile int spikeDirectionLocal;
	static volatile int squallyVelocityXLocal;

	spikeDirectionLocal = 0;
	squallyVelocityXLocal = 0;

	if (this->squally != nullptr)
	{
		// Compute a fake velocity given movement direction. This was easier than trying to get the true velocity.
		// For this script velocity is read-only anyways, and we just care about whether it's < or > 0.0f
		squallyVelocityXLocal = int(this->squally->getRuntimeStateOrDefaultFloat(StateKeys::MovementX, 0.0f) * EntityMovementBehavior::DefaultRunAcceleration);
	}

	ASM(push ZBX)
	ASM(push ZAX)
	ASM(push ZSI)
	ASM(push ZDI)
	ASM(mov ZAX, 0)
	ASM(mov ZSI, 1)
	ASM(mov ZDI, -1)
	ASM_MOV_REG_VAR(ebx, squallyVelocityXLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MOVE);
	ASM(cmp ZBX, 0)
	ASM(cmovg ZAX, ZSI)
	ASM(cmovl ZAX, ZDI)
	ASM_NOP9();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(spikeDirectionLocal, eax);
	ASM(pop ZDI);
	ASM(pop ZSI);
	ASM(pop ZAX);
	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	static const float MoveSpeed = 512.0f;

	float newX = this->root->getPositionX();
	const float minX = this->rootPosition.x - this->railSize.width / 2.0f;
	const float maxX = this->rootPosition.x + this->railSize.width / 2.0f;

	if (spikeDirectionLocal != 0 && ((spikeDirectionLocal < 0) ^ this->inverse))
	{
		newX += MoveSpeed * dt;
		this->root->setPositionX(MathUtils::clamp(newX, minX, maxX));
	}
	else if (spikeDirectionLocal != 0 && ((spikeDirectionLocal > 0) ^ this->inverse))
	{
		newX -= MoveSpeed * dt;
		this->root->setPositionX(MathUtils::clamp(newX, minX, maxX));
	}
}
END_NO_OPTIMIZE
