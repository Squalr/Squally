#include "DartLauncher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/DartTraps/DartLauncher/DartNopClippy.h"
#include "Objects/Platformer/Traps/DartTraps/DartPool.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Hacking/Objects/DartLauncher/UpdateLaunchTimer/RegisterEax.h"
#include "Strings/Menus/Hacking/Objects/DartLauncher/UpdateLaunchTimer/RegisterXmm0.h"
#include "Strings/Menus/Hacking/Objects/DartLauncher/UpdateLaunchTimer/RegisterXmm1.h"
#include "Strings/Menus/Hacking/Objects/DartLauncher/UpdateLaunchTimer/UpdateLaunchTimer.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SHOOT 1

const std::string DartLauncher::MapKeyDartLauncher = "dart-launcher";
const std::string DartLauncher::PropertyLaunchSpeed = "speed";
const float DartLauncher::DefaultLaunchSpeed = 320.0f;
const float DartLauncher::LaunchCooldownMin = 2.0f;
const float DartLauncher::LaunchCooldownMax = 4.0f;

DartLauncher* DartLauncher::create(ValueMap& properties)
{
	DartLauncher* instance = new DartLauncher(properties);

	instance->autorelease();

	return instance;
}

DartLauncher::DartLauncher(ValueMap& properties) : super(properties)
{
	this->launcherContainer = Node::create();
	this->launcherSprite = Sprite::create(ObjectResources::Traps_DartLauncher_DartLauncher);
	this->rotation = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyRotation, Value(0.0f)).asFloat();
	this->launchSpeed = GameUtils::getKeyOrDefault(this->properties, DartLauncher::PropertyLaunchSpeed, Value(DartLauncher::DefaultLaunchSpeed)).asFloat();
	this->launchTimer = 0.0f;
	this->dartPool = DartPool::create(2, this->rotation + 90.0f, this->launchSpeed, 90.0f);

	this->launcherSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->dartPool->setPositionY(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);
	this->launcherContainer->setPositionY(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);

	this->launcherContainer->setRotation(this->rotation);
	
	this->launcherContainer->addChild(this->dartPool);
	this->launcherContainer->addChild(this->launcherSprite);
	this->addChild(this->launcherContainer);
}

DartLauncher::~DartLauncher()
{
}

void DartLauncher::onEnter()
{
	super::onEnter();

	this->rebindUIElementsTo(this->dartPool);

	this->scheduleUpdate();
}

void DartLauncher::initializePositions()
{
	super::initializePositions();

	this->dartPool->setPosition(Vec2(42.0f, -24.0f));
}

void DartLauncher::update(float dt)
{
	super::update(dt);

	this->shoot(dt);
}

Vec2 DartLauncher::getButtonOffset()
{
	float width = 24.0f;
	float height = -124.0f;
	float angle = float(M_PI) * this->rotation / 180.0f;

	return Vec2(std::sin(angle) * width, std::cos(angle) * height);
}

void DartLauncher::registerHackables()
{
	super::registerHackables();

	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_SHOOT,
			HackableCode::LateBindData(
				DartLauncher::MapKeyDartLauncher,
				Strings::Menus_Hacking_Objects_DartLauncher_UpdateLaunchTimer_UpdateLaunchTimer::create(),
				UIResources::Menus_Icons_CrossHair,
				nullptr,
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_DartLauncher_UpdateLaunchTimer_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_DartLauncher_UpdateLaunchTimer_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_DartLauncher_UpdateLaunchTimer_RegisterXmm1::create() },
				},
				int(HackFlags::None),
				15.0f,
				this->showClippy ? DartNopClippy::create() : nullptr
			)
		},
	};

	auto swingFunc = &DartLauncher::shoot;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

NO_OPTIMIZE void DartLauncher::shoot(float dt)
{
	if (this->launchTimer <= 0.0f)
	{
		this->launchTimer = RandomHelper::random_real(DartLauncher::LaunchCooldownMin, DartLauncher::LaunchCooldownMax);

		this->dartPool->getNextDart();
	}

	float* timePtr = &this->launchTimer;
	float* dtPtr = &dt;

	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, timePtr);
	ASM_MOV_REG_VAR(ZBX, dtPtr);
	ASM(movss xmm0, [ZAX])
	ASM(movss xmm1, [ZBX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SHOOT);
	ASM(subps xmm0, xmm1);
	ASM(movss [ZAX], xmm0);
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);

	HACKABLES_STOP_SEARCH();
}
