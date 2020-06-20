#include "Sarcophagus.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Sarcophagus::MapKey = "sarcophagus";

Sarcophagus* Sarcophagus::create(ValueMap& properties)
{
	Sarcophagus* instance = new Sarcophagus(properties);

	instance->autorelease();

	return instance;
}

Sarcophagus::Sarcophagus(ValueMap& properties) : super(properties)
{
	this->sarcophagusBase = Sprite::create(ObjectResources::Cinematic_Sarcophagus_SarcophagusBase);
	this->sarcophagusLid = Sprite::create(ObjectResources::Cinematic_Sarcophagus_SarcophagusLid);

	this->addChild(sarcophagusBase);
	this->addChild(sarcophagusLid);
}

Sarcophagus::~Sarcophagus()
{
}

void Sarcophagus::initializePositions()
{
	super::initializePositions();

	this->sarcophagusLid->setPosition(Vec2(0.0f, 128.0f));
}

void Sarcophagus::initializeListeners()
{
	super::initializeListeners();
}

Sprite* Sarcophagus::getBase()
{
	return this->sarcophagusBase;
}

Sprite* Sarcophagus::getLid()
{
	return this->sarcophagusLid;
}
