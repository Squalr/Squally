#include "MagicWall.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/2d/CCParticleSystem.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string MagicWall::MapKey = "magic-wall";

MagicWall* MagicWall::create(ValueMap& properties)
{
	MagicWall* instance = new MagicWall(properties);

	instance->autorelease();

	return instance;
}

MagicWall::MagicWall(ValueMap& properties) : super(properties)
{
	this->wallSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->wallParticles = SmartParticles::create(ParticleResources::Objects_MagicWall, SmartParticles::CullInfo(this->wallSize));

	this->addChild(this->wallParticles);
}

MagicWall::~MagicWall()
{
}

void MagicWall::onEnter()
{
	super::onEnter();

	this->wallParticles->start();
	this->wallParticles->getParticles()->setTotalParticles(int(this->wallSize.width * this->wallSize.height / 256.0f));
	this->wallParticles->getParticles()->setPosVar(Vec2(this->wallSize.width / 2.0f, this->wallSize.height / 2.0f));
}
