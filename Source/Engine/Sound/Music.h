#pragma once

#include "Engine/Sound/SoundBase.h"

class SmartNode;
class SmartScene;

class Music : public SoundBase
{
public:
	void unpause() override;

protected:
	friend class MusicPlayer;
	friend class Track;

	static Music* createAndAddGlobally(std::string musicResource, SmartNode* owner);
	static Music* createAndAddGlobally(std::string musicResource, SmartScene* owner);

	Music(std::string musicResource, SmartNode* owner);
	Music(std::string musicResource, SmartScene* owner);
	virtual ~Music();

	void initializeListeners() override;
	void play(bool repeat = true, float startDelay = 0.0f) override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	SmartNode* owner;
};
