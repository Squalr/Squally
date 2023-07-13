#pragma once

#include "Engine/Maps/GameObject.h"

namespace sf
{
	class Sound;
}

enum class SoundChannel;

class SoundBase : public GameObject
{
public:
	virtual void allocSound();
	virtual void play(bool repeat = false, float startDelay = 0.0f);
	virtual void unfreeze(); // careful, unpause is a cocos function
	bool isPlaying();
	virtual void freeze(); // careful, pause is a cocos function
	virtual void stop();
	virtual void stopAndFadeOut(std::function<void()> onFadeOutCallback = nullptr, bool hasPriority = false);
	void toggleIgnorePause(bool ignorePause);

	void setCustomMultiplier(float customMultiplier);
	virtual void setSoundResource(std::string soundResource);
	std::string getSoundResource() const;
	
	static const int InvalidSoundId;

protected:
	SoundBase(cocos2d::ValueMap& properties, std::string soundResource);
	virtual ~SoundBase();

	void onEnter() override;
	void pause() override;
	void update(float dt) override;
	virtual SoundChannel getSoundChannel();
	virtual float getConfigVolume() = 0;
	void updateVolume();
	void setVolumeOverride(float volume);
	void clearVolumeOverride();
	float getVolume();

	std::string soundResource;
	float fadeMultiplier = 1.0f;
	float distanceMultiplier = 1.0f;
	float customMultiplier = 1.0f;
	bool enableCameraDistanceFade = false;
	bool hasVolumeOverride = false;
	bool isFading = false;
	std::function<void()> onFadeOutCallback = nullptr;
	sf::Sound* soundRef = nullptr;
	int soundId = -1;
	
private:
	typedef GameObject super;

	bool ignorePause = false;

	static const std::string KeyScheduleFadeOutAudio;
};
