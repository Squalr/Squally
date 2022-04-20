#include "WorldSound.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include <SFML/Audio.hpp>

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos_experimental;

const std::string WorldSound::MapKey = "world-sound";

WorldSound* WorldSound::create(std::string soundResource)
{
	ValueMap valueMap = ValueMap();

	return WorldSound::create(valueMap, soundResource);
}

WorldSound* WorldSound::create(ValueMap& properties, std::string soundResource)
{
	WorldSound* instance = new WorldSound(properties, soundResource);

	instance->autorelease();

	return instance;
}

WorldSound::WorldSound(ValueMap& properties, std::string soundResource) : super(properties, soundResource)
{
}

WorldSound::~WorldSound()
{
}

void WorldSound::onEnterTransitionDidFinish()
{
	this->updateDistanceFade();
}

void WorldSound::update(float dt)
{
	super::update(dt);

	this->updateDistanceFade();
}

void WorldSound::disableZDepth()
{
	this->zDepthEnabled = false;
}

void WorldSound::enableZDepth()
{
	this->zDepthEnabled = true;
}

void WorldSound::updateDistanceFade()
{
	if (this->soundResource.empty() || this->soundRef == nullptr)
	{
		return;
	}

	sf::SoundSource::Status status = this->soundRef->getStatus();

	switch (status)
	{
		default:
		case sf::SoundSource::Status::Paused:
		case sf::SoundSource::Status::Stopped:
		{
			// Not playing, do nothing
			if (this->onFadeOutCallback != nullptr)
			{
				this->onFadeOutCallback();
			}
			break;
		}
		case sf::SoundSource::Status::Playing:
		{
			Vec3 thisCoords = GameUtils::getWorldCoords3D(this);
			Vec3 cameraPosition = GameCamera::getInstance()->getCameraPosition3();
			CSize visibleSize = Director::getInstance()->getVisibleSize();
			float distance = this->zDepthEnabled ? thisCoords.distance(cameraPosition) : Vec2(thisCoords.x, thisCoords.y).distance(Vec2(cameraPosition.x, cameraPosition.y));
			float dropOffDistance = 1080.0f * GameCamera::getInstance()->getCameraZoom();
			float adjustedDistance = distance - dropOffDistance;

			this->distanceMultiplier = distance <= dropOffDistance ? 1.0f : MathUtils::clamp(1.0f / (1.0f + 0.0025f * std::pow(adjustedDistance, 1.25f)), 0.0f, 1.0f);
			this->updateVolume();
			break;
		}
	}
}
