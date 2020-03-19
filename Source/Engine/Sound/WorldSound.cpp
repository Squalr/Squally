#include "WorldSound.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

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

void WorldSound::updateDistanceFade()
{
	if (this->soundResource.empty())
	{
		return;
	}

	AudioEngine::AudioState state = AudioEngine::getState(this->activeTrackId);

	switch (state)
	{
		default:
		case AudioEngine::AudioState::ERROR:
		case AudioEngine::AudioState::INITIALIZING:
		case AudioEngine::AudioState::PAUSED:
		{
			// Not playing, do nothing
			break;
		}
		case AudioEngine::AudioState::PLAYING:
		{
			Vec3 thisCoords = GameUtils::getWorldCoords3D(this);
			Vec3 cameraPosition = GameCamera::getInstance()->getCameraPosition3();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			float distance = thisCoords.distance(cameraPosition);
			float dropOffDistance = 1080.0f;
			float adjustedDistance = distance - dropOffDistance;

			this->distanceMultiplier = distance <= dropOffDistance ? 1.0f : MathUtils::clamp(1.0f / (1.0f + 0.0025f * std::pow(adjustedDistance, 1.25f)), 0.0f, 1.0f);
			this->updateVolume();

			break;
		}
	}
}
