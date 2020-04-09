#pragma once

#include "Engine/Maps/GameObject.h"

class SoundBase : public GameObject
{
public:
	virtual void play(bool repeat = false, float startDelay = 0.0f);
	virtual void unpause();
	bool isPlaying();
	virtual void freeze();
	virtual void stop();
	virtual void stopAndFadeOut(std::function<void()> onFadeOutCallback = nullptr, bool hasPriority = false);

	void setCustomMultiplier(float customMultiplier);
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

	std::string soundResource;
	float fadeMultiplier;
	float distanceMultiplier;
	float customMultiplier;
	bool enableCameraDistanceFade;
	bool hasVolumeOverride;
	bool isFading;
	bool destroyOnFadeOut;
	std::function<void()> onFadeOutCallback;
	
	static const int INVALID_ID;

private:
	typedef GameObject super;

	static const std::string KeyScheduleFadeOutAudio;
};
