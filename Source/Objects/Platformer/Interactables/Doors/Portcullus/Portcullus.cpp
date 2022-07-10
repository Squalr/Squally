#include "Portcullus.h"

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

const std::string Portcullus::MapKey = "portcullus";
const float Portcullus::DoorOpenDelta = 320.0f;
const std::string Portcullus::UnlockedSaveKey = "PORTCULLUSR_UNLOCKED";

Portcullus* Portcullus::create(ValueMap& properties)
{
	Portcullus* instance = new Portcullus(properties);

	instance->autorelease();

	return instance;
}

Portcullus::Portcullus(ValueMap& properties) : super(properties, CSize(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()), Vec2(0.0f, 0.0f))
{
	CSize doorSize = CSize(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());

	this->doorOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_Ancient_Stone_Mechanism_Movement_01);
	this->top = Sprite::create(ObjectResources::Doors_Portcullus_PortcullusTop);
	this->bars = Sprite::create(ObjectResources::Doors_Portcullus_PortcullusMid);
	this->spikes = Sprite::create(ObjectResources::Doors_Portcullus_PortcullusSpikes);

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;

	this->bars->getTexture()->setTexParameters(params);
	this->bars->setTextureRect(CRect(
		0.0f,
		0.0f,
		this->bars->getContentSize().width,
		doorSize.height - this->top->getContentSize().height - this->spikes->getContentSize().height
	));

	this->contentNode->addChild(this->spikes);
	this->contentNode->addChild(this->top);
	this->contentNode->addChild(this->bars);
}

Portcullus::~Portcullus()
{
}

void Portcullus::onEnter()
{
	super::onEnter();
	
	if (this->loadObjectStateOrDefault(Portcullus::UnlockedSaveKey, Value(true)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
}

void Portcullus::initializePositions()
{
	super::initializePositions();

	CSize doorSize = CSize(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());

	float topSize = this->top->getContentSize().height;
	float spikeSize = this->spikes->getContentSize().height;
	float barOffsetY = spikeSize - topSize;
	float offsetY = doorSize.height / 2.0f - 24.0f; // This shouldn't be a constant, but I don't really care enough to work this out as a proper equation

	this->top->setPosition(Vec2(0.0f, -this->top->getContentSize().height + offsetY));
	this->bars->setPosition(Vec2(0.0f, -doorSize.height / 2.0f + barOffsetY + offsetY));
	this->spikes->setPosition(Vec2(0.0f, -doorSize.height + spikeSize + offsetY));
}

void Portcullus::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(Portcullus::UnlockedSaveKey, Value(false));
	
	float currentProgress = this->contentNode->getPositionY() / Portcullus::DoorOpenDelta;

	if (animate)
	{
		this->contentNode->stopAllActions();
		this->contentNode->runAction(MoveTo::create(5.0f * currentProgress, Vec2::ZERO));

		this->doorOpenSound->play();
	}
	else
	{
		this->contentNode->setPosition(Vec2::ZERO);
	}
}

void Portcullus::unlock(bool animate)
{
	super::unlock(animate);

	this->saveObjectState(Portcullus::UnlockedSaveKey, Value(true));

	float currentProgress = 1.0f - this->contentNode->getPositionY() / Portcullus::DoorOpenDelta;

	if (animate)
	{
		this->contentNode->stopAllActions();
		this->contentNode->runAction(MoveTo::create(5.0f * currentProgress, Vec2(0.0f, Portcullus::DoorOpenDelta)));
		this->doorOpenSound->play();
	}
	else
	{
		this->contentNode->setPosition(Vec2(0.0f, Portcullus::DoorOpenDelta));
	}
}
