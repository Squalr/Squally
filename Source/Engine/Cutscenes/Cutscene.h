#pragma once
#include <deque>
#include <functional>

#include "Engine/SmartScene.h"

class CutsceneClip;

class Cutscene : public SmartScene
{
public:
	static Cutscene* create(std::function<void()> cutsceneCompleteCallback);

	void playCutscenes();

protected:
	Cutscene(std::function<void()> cutsceneCompleteCallback);
	virtual ~Cutscene();

	void initializeListeners() override;
	void enqueueCutsceneClip(CutsceneClip* cutscene);
	void cutsceneClipCompleteCallback();
	void endCutscene();

private:
	typedef SmartScene super;
	void playNextCutsceneClip();

	CutsceneClip* activeClip;
	std::deque<CutsceneClip*> cutsceneClips;
	std::function<void()> onCutsceneCompleteCallback;
};
