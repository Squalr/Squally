#include "LiquidNode.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/Liquid/LiquidTop.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::string LiquidNode::PropertyDisableWaves = "disable-waves";
const std::string LiquidNode::PropertyDisableEdges = "disable-edges";
const float LiquidNode::SplashSpacing = 192.0f;
const float LiquidNode::WaterGravity = 0.0f;
const float LiquidNode::WaterCollisionOffset = 128.0f;

LiquidNode* LiquidNode::create(ValueMap& properties, float surfaceDepth, CollisionType collisionType, Color4B surfaceColor, Color4B bodyColor)
{
    LiquidNode* instance = new LiquidNode(properties, surfaceDepth, collisionType, surfaceColor, bodyColor);

    instance->autorelease();

    return instance;
}

LiquidNode::LiquidNode(ValueMap& properties, float surfaceDepth, CollisionType collisionType, Color4B surfaceColor, Color4B bodyColor) : super(properties)
{
    const float kTension = 0.015f;
    const float kDampening = 0.005f;
    const float kSpread = 0.05f;
    
	this->liquidSize = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	);
	this->splashes = int(std::round(this->liquidSize.width / LiquidNode::SplashSpacing));
	this->noSplashDelay = 1.0f;

	float waterCollisionHeight = MathUtils::clamp(this->liquidSize.height - LiquidNode::WaterCollisionOffset, 0.0f, this->liquidSize.height);
	float effectiveOffset = this->liquidSize.height - waterCollisionHeight;
	Size collisionSize = Size(this->liquidSize.width, waterCollisionHeight);
    this->liquidSize = liquidSize;

	this->liquidCollision = CollisionObject::create(CollisionObject::createBox(collisionSize), collisionType, CollisionObject::Properties(false, false));

	if (GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString() == CollisionObject::MapKeyCollisionTypeNone)
	{
		this->liquidCollision->setPhysicsEnabled(false);
	}

	this->liquidCollision->setPositionY(-effectiveOffset / 2.0f);
	

    this->surfaceDepth = MathUtils::clamp(surfaceDepth, 0.0f, liquidSize.height);
    this->liquidSize.height = MathUtils::clamp(this->liquidSize.height, this->surfaceDepth, liquidSize.height);
    this->liquidBody = LayerColor::create(bodyColor, this->liquidSize.width, this->liquidSize.height - this->surfaceDepth);
    this->liquidTop = LiquidTop::create(Size(this->liquidSize.width, this->surfaceDepth), surfaceColor, bodyColor, kTension, kDampening, kSpread);
    this->edges = DrawNode::create();

    if (!GameUtils::getKeyOrDefault(this->properties, LiquidNode::PropertyDisableEdges, Value(false)).asBool())
    {
        this->edges->drawSegment(Vec2(-liquidSize.width / 2.0f, liquidSize.height / 2.0f), Vec2(-liquidSize.width / 2.0f, -liquidSize.height / 2.0f), 2.0f, Color4F(surfaceColor));
        this->edges->drawSegment(Vec2(-liquidSize.width / 2.0f, -liquidSize.height / 2.0f), Vec2(liquidSize.width / 2.0f, -liquidSize.height / 2.0f), 2.0f, Color4F(surfaceColor));
        this->edges->drawSegment(Vec2(liquidSize.width / 2.0f, -liquidSize.height / 2.0f), Vec2(liquidSize.width / 2.0f, liquidSize.height / 2.0f), 2.0f, Color4F(surfaceColor));
    }

    this->wavesDisabled = GameUtils::getKeyOrDefault(this->properties, LiquidNode::PropertyDisableWaves, Value(false)).asBool();

	this->addChild(this->liquidCollision);
    this->addChild(this->liquidBody);
    this->addChild(this->liquidTop);
    this->addChild(this->edges);
}

LiquidNode::~LiquidNode()
{
}

void LiquidNode::onEnter()
{
	super::onEnter();

	this->runSplashes();

	this->scheduleUpdate();
}

void LiquidNode::initializePositions()
{
    super::initializePositions();

    this->liquidTop->setPosition(Vec2(-this->liquidSize.width / 2.0f, this->liquidSize.height / 2.0f - this->surfaceDepth));
    this->liquidBody->setPosition(Vec2(-this->liquidSize.width / 2.0f, -this->liquidSize.height / 2.0f));
}

void LiquidNode::splash(float x, float speed, float splashRadius, float decay)
{
    this->liquidTop->splash(x, speed, splashRadius, decay);
}

void LiquidNode::update(float dt)
{
	super::update(dt);

	if (this->noSplashDelay > 0.0f)
	{
		this->noSplashDelay -= dt;
	}
}

void LiquidNode::runObjectSplash(CollisionObject* other, bool isExit)
{
	if (this->noSplashDelay > 0.0f)
	{
		return;
	}

	float objectX = GameUtils::getWorldCoords(other).x;
	float waterX = GameUtils::getWorldCoords(this).x - this->liquidSize.width / 2.0f;
	float speed = isExit ? 1.5f : 2.0f;
	float radius = isExit ? 192.0f : 128.0f;

	this->splash(objectX - waterX, speed, radius);
}

void LiquidNode::runSplashes()
{
	for (int index = 0; index < this->splashes; index++)
	{
		this->runSplash(index);
	}
}

void LiquidNode::runSplash(int index)
{
    if (this->wavesDisabled)
    {
        return;
    }

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(1.0f, 2.0f)),
		CallFunc::create([=]()
		{
			float x = RandomHelper::random_real(0.0f, LiquidNode::SplashSpacing) * float(index);
			this->splash(x, RandomHelper::random_real(0.0f, 1.0f));
			this->runSplash(index);
		}),
		nullptr
	));
}
