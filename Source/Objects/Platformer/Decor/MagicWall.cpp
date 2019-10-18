#include "MagicWall.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_WIND_SPEED 1

const std::string MagicWall::MapKeyMagicWall = "magic-wall";

MagicWall* MagicWall::create(ValueMap& properties)
{
	MagicWall* instance = new MagicWall(properties);

	instance->autorelease();

	return instance;
}

MagicWall::MagicWall(ValueMap& properties) : super(properties)
{
	this->wallParticles = ParticleSystemQuad::create(ParticleResources::Objects_MagicWall);

	this->wallSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());

	this->addChild(this->wallParticles);
}

MagicWall::~MagicWall()
{
}

void MagicWall::onEnter()
{
	super::onEnter();

	this->wallParticles->setTotalParticles(int(this->wallSize.width * this->wallSize.height / 256.0f));
	this->wallParticles->setPosVar(Vec2(this->wallSize.width / 2.0f, this->wallSize.height / 2.0f));

	this->scheduleUpdate();
}
