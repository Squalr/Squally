#include "SmartParticles.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SmartParticles* SmartParticles::create(std::string particleResource, CullInfo cullInfo)
{
	SmartParticles* instance = new SmartParticles(particleResource, cullInfo);

	instance->autorelease();

	return instance;
}

SmartParticles::SmartParticles(std::string particleResource, CullInfo cullInfo) : super()
{
	this->particleResource = particleResource;
	this->cullContainer = Node::create();
	this->particles = nullptr; // lazy init for culled particles
	this->debugDrawNode = DeveloperModeController::IsDeveloperBuild ? DrawNode::create() : nullptr;
	this->cullInfo = cullInfo;
	this->canUpdate = false;
	this->hasAnchorOverride = false;
	this->hasPosVarOverride = false;
	this->hasSourcePositionOverride = false;
	this->hasTotalParticlesOverride = false;
	this->hasAngleOverride = false;
	this->hasPositionTypeOverride = false;
	this->boundsRect = Rect(Vec2::ZERO, this->cullInfo.size);

	this->setContentSize(this->cullInfo.size);

	if (!cullInfo.cull)
	{
		tryCreateParticleInstance();
	}

	this->stop();

	if (this->debugDrawNode != nullptr && cullInfo.cull)
	{
		this->debugDrawNode->drawRect(-Vec2(this->cullInfo.size) / 2.0f, Vec2(this->cullInfo.size) / 2.0f, Color4F::GREEN);
	}

	this->addChild(this->cullContainer);

	if (this->debugDrawNode != nullptr)
	{
		this->addChild(this->debugDrawNode);
	}
}

SmartParticles::~SmartParticles()
{ 
}

void SmartParticles::onEnter()
{
	super::onEnter();
	
	if (this->cullInfo.cull)
	{
		this->optimizationHideOffscreenParticles();
		this->scheduleUpdate();
	}
}

void SmartParticles::onDeveloperModeEnable(int debugLevel)
{
	if (debugLevel >= 2 && this->debugDrawNode != nullptr)
	{
		this->debugDrawNode->setVisible(true);
	}
}

void SmartParticles::onDeveloperModeDisable()
{
	if (this->debugDrawNode != nullptr)
	{
		this->debugDrawNode->setVisible(false);
	}
}

void SmartParticles::update(float dt)
{
	super::update(dt);
	
	this->optimizationHideOffscreenParticles();
}

void SmartParticles::tryCreateParticleInstance()
{
	if (this->particles == nullptr)
	{
		this->particles = ParticleSystemQuad::create(particleResource);

		if (this->hasAnchorOverride)
		{
			this->particles->setAnchorPoint(this->particleAnchor);
		}

		if (this->hasPosVarOverride)
		{
			this->particles->setPosVar(this->particlePosVar);
		}

		if (this->hasSourcePositionOverride)
		{
			this->particles->setSourcePosition(this->particleSourcePosition);
		}

		if (this->hasTotalParticlesOverride)
		{
			this->particles->setTotalParticles(this->particleTotalParticles);
		}

		if (this->hasAngleOverride)
		{
			this->particles->setAngle(this->particleAngle);
		}

		if (this->hasPositionTypeOverride)
		{
			this->particles->setPositionType(ParticleSystem::PositionType(this->particlePositionType));
		}

		this->cullContainer->addChild(this->particles);
	}
}

void SmartParticles::start()
{
	this->canUpdate = true;

	if (this->particles == nullptr)
	{
		return;
	}
	
	this->stopAllActions();
	this->particles->start();
	this->particles->toggleCanUpdate(this->canUpdate);
	this->particles->resumeEmissions();
	this->particles->setVisible(true);
}

void SmartParticles::restart()
{
	if (this->particles == nullptr)
	{
		return;
	}
	
	this->particles->resetSystem();
}

void SmartParticles::stop(float disableUpdateAfter)
{
	if (this->particles == nullptr)
	{
		this->canUpdate = false;
		return;
	}

	this->particles->stopSystem();
	this->particles->pauseEmissions();

	if (disableUpdateAfter <= 0.0f)
	{
		this->canUpdate = false;
		this->particles->toggleCanUpdate(this->canUpdate);
		this->particles->setVisible(false);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(disableUpdateAfter),
			CallFunc::create([=]()
			{
				this->canUpdate = false;
				this->particles->toggleCanUpdate(this->canUpdate);
				this->particles->setVisible(false);
			}),
			nullptr
		));
	}
}

bool SmartParticles::isActive()
{
	if (this->particles == nullptr)
	{
		return false;
	}

	return this->particles->isActive();
}

void SmartParticles::accelerate(float duration)
{
	if (this->particles == nullptr)
	{
		return;
	}

	const float step = 1.0f / 60.0f;

	this->start();

	for (float currentDuration = 0.0f; currentDuration < duration; currentDuration += step)
	{
		this->particles->update(step);
	}
}

void SmartParticles::setTotalParticles(int totalParticles)
{
	this->particleTotalParticles = totalParticles;
	this->hasTotalParticlesOverride = true;

	if (this->particles != nullptr)
	{
		this->particles->setTotalParticles(this->particleTotalParticles);
	}
}

void SmartParticles::setPosVar(cocos2d::Vec2 posVar)
{
	this->particlePosVar = posVar;
	this->hasPosVarOverride = true;

	if (this->particles != nullptr)
	{
		this->particles->setPosVar(this->particlePosVar);
	}
}

void SmartParticles::setSourcePosition(cocos2d::Vec2 sourcePosition)
{
	this->particleSourcePosition = sourcePosition;
	this->hasSourcePositionOverride = true;

	if (this->particles != nullptr)
	{
		this->particles->setSourcePosition(this->particleSourcePosition);
	}
}

void SmartParticles::setAngle(float angle)
{
	this->particleAngle = angle;
	this->hasAngleOverride = true;

	if (this->particles != nullptr)
	{
		this->particles->setAngle(this->particleAngle);
	}
}

void SmartParticles::setParticleAnchorPoint(cocos2d::Vec2 anchorPoint)
{
	this->particleAnchor = anchorPoint;
	this->hasAnchorOverride = true;

	if (this->particles != nullptr)
	{
		this->particles->setAnchorPoint(this->particleAnchor);
	}
}

void SmartParticles::setGrouped()
{
	this->particlePositionType = int(ParticleSystem::PositionType::GROUPED);
	this->hasPositionTypeOverride = true;

	if (this->particles != nullptr)
	{
		this->particles->setPositionType(ParticleSystem::PositionType(this->particlePositionType));
	}
}

void SmartParticles::setRelative()
{
	this->particlePositionType = int(ParticleSystem::PositionType::RELATIVE);

	if (this->particles != nullptr)
	{
		this->particles->setPositionType(ParticleSystem::PositionType(this->particlePositionType));
	}
}

void SmartParticles::setFree()
{
	this->particlePositionType = int(ParticleSystem::PositionType::FREE);

	if (this->particles != nullptr)
	{
		this->particles->setPositionType(ParticleSystem::PositionType(this->particlePositionType));
	}
}

void SmartParticles::optimizationHideOffscreenParticles()
{
	if (!this->cullInfo.cull)
	{
		return;
	}
	
	// A little extra padding to give particles time to start up if needed
	static const Size Padding = Size(512.0f, 512.0f);
	static const Rect CameraRect = Rect(Vec2::ZERO, Director::getInstance()->getVisibleSize());
	Rect thisRect = GameUtils::getScreenBounds(this, Padding);

	if (CameraRect.intersectsRect(thisRect))
	{
		// Lazy initialize finally!
		if (this->canUpdate && this->particles == nullptr)
		{
			this->tryCreateParticleInstance();
			this->start();
		}
		
		if (this->particles != nullptr)
		{
			this->particles->toggleCanUpdate(this->canUpdate);
		}

		this->cullContainer->setVisible(true);
	}
	else
	{
		if (this->particles != nullptr)
		{
			this->particles->toggleCanUpdate(false);
		}

		this->cullContainer->setVisible(false);
	}
}
