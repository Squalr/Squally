#pragma once

#include "Engine/Sound/SoundBase.h"

class SmartNode;
class SmartScene;

class Music : public SoundBase
{
public:
	static Music* createAndAddGlobally(std::string musicResource, SmartNode* owner);
	static Music* createAndAddGlobally(std::string musicResource, SmartScene* owner);

	void unpause() override;

protected:
	friend class MusicPlayer;

	void initializeListeners() override;
	void play(bool repeat = true, float startDelay = 0.0f) override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	Music(std::string musicResource, SmartNode* owner);
	Music(std::string musicResource, SmartScene* owner);
	virtual ~Music();

	SmartNode* owner;
};
