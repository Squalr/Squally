#pragma once

#include "Engine/SmartNode.h"

class SoundBase : public SmartNode
{
public:
	void play(bool repeat = false);
	void stop();
	void stopAndFadeOut();
	void setVolumeMultiplier(float volumeMultiplier);
	void toggleCameraDistanceFade(bool enableCameraDistanceFade);
	void setSoundResource(std::string soundResource);

protected:
	SoundBase(std::string soundResource);
	~SoundBase();

	void onExit() override;
	virtual float getConfigVolume() = 0;

private:
	typedef SmartNode super;

	float getVolume();

	std::string soundResource;
	int activeTrackId;
	float volumeMultiplier;
	bool enableCameraDistanceFade;

	static const int INVALID_ID;
};
