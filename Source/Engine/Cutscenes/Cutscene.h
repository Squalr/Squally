#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/SmartScene.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class Cutscene : public SmartScene
{
public:
	static Cutscene* create(std::function<void()> cutsceneCompleteCallback);

	void playCutscenes();

protected:
	Cutscene(std::function<void()> cutsceneCompleteCallback);
	~Cutscene();

	void initializeListeners() override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void enqueueCutsceneClip(CutsceneClip* cutscene);
	void cutsceneClipCompleteCallback();
	void endCutscene();

private:
	void playNextCutsceneClip();

	CutsceneClip* activeClip;
	std::deque<CutsceneClip*> cutsceneClips;
	std::function<void()> onCutsceneCompleteCallback;
};
