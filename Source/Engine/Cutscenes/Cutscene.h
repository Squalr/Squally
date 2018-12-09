#pragma once
#include <deque>
#include <functional>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/UI/FadeScene.h"

class CutsceneClip;

class Cutscene : public FadeScene
{
public:
	static Cutscene* create(std::function<void()> cutsceneCompleteCallback);

	void playCutscenes();

protected:
	Cutscene(std::function<void()> cutsceneCompleteCallback);
	virtual ~Cutscene();

	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void enqueueCutsceneClip(CutsceneClip* cutscene);
	void cutsceneClipCompleteCallback();
	void endCutscene();

private:
	void playNextCutsceneClip();

	CutsceneClip* activeClip;
	std::deque<CutsceneClip*> cutsceneClips;
	std::function<void()> onCutsceneCompleteCallback;
};
