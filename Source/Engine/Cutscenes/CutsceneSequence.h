#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class CutsceneSequence : public FadeScene
{
public:
	static CutsceneSequence* create();

	void setCutsceneEndCallback(std::function<void()> cutsceneCompleteCallback);
	void playCutscenes();

protected:
	CutsceneSequence();
	~CutsceneSequence();

	void update(float dt) override;
	void enqueueCutscene(Cutscene* cutscene);
	void onCutsceneEndCallback();
	void cutsceneCompleteCallback();

private:
	void playNextCutscene();

	std::deque<Cutscene*>* cutscenes;
	std::function<void()> onCutsceneCompleteCallback;
};
