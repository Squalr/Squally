#pragma once

#include "Engine/GlobalNode.h"

class SoundBase : public GlobalNode
{
public:
	virtual void play(bool repeat = false);
	void stop();
	void stopAndFadeOut();
	void setVolumeMultiplier(float volumeMultiplier);
	void toggleCameraDistanceFade(bool enableCameraDistanceFade);
	void setSoundResource(std::string soundResource);

protected:
	SoundBase(std::string soundResource);
	~SoundBase();

	void onEnter() override;
	void update(float dt) override;
	virtual float getConfigVolume() = 0;
	void updateVolume();
	float getVolume();

	int activeTrackId;

private:
	typedef GlobalNode super;

	std::string soundResource;
	float fadeMultiplier;
	float distanceMultiplier;
	float volumeMultiplier;
	int fadeOutTick;
	bool enableCameraDistanceFade;

	static const std::string KeyScheduleFadeOutAudio;
	static const int INVALID_ID;
};
