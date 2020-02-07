#pragma once

#include "Engine/Maps/GameObject.h"

class SoundBase : public GameObject
{
public:
	virtual void play(bool repeat = false, float startDelay = 0.0f);
	virtual void unpause();
	virtual void stop();
	virtual void stopAndFadeOut(std::function<void()> onFadeOutCallback = nullptr);

	void setCustomMultiplier(float customMultiplier);
	void toggleCameraDistanceFade(bool enableCameraDistanceFade);
	void setSoundResource(std::string soundResource);
	std::string getSoundResource();

protected:
	SoundBase(cocos2d::ValueMap& properties, std::string soundResource);
	virtual ~SoundBase();

	void onEnter() override;
	void update(float dt) override;
	virtual float getConfigVolume() = 0;
	void updateVolume();
	void setVolumeOverride(float volume);
	void clearVolumeOverride();
	float getVolume();

	int activeTrackId;

private:
	typedef GameObject super;

	void updateDistanceFade();

	std::string soundResource;
	float fadeMultiplier;
	float distanceMultiplier;
	float customMultiplier;
	int fadeOutTick;
	bool enableCameraDistanceFade;
	bool hasVolumeOverride;
	bool isFading;
	std::function<void()> onFadeOutCallback;
	cocos2d::Vec2 cachedCoords;

	static const std::string KeyScheduleFadeOutAudio;
	static const int INVALID_ID;
};
