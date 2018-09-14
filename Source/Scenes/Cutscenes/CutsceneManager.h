#pragma once
#include "cocos2d.h"

#include "Cutscene.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class CutsceneManager : public FadeScene
{
public:
	static CutsceneManager* create(std::function<void()> cutsceneCompleteCallback);


private:
	CutsceneManager(std::function<void()> cutsceneCompleteCallback);
	~CutsceneManager();

	void update(float dt) override;
	void enqueueCutscene(Cutscene* cutscene);
	void playCutscenes();
	void onCutsceneEndCallback();

	std::deque<Cutscene*>* cutscenes;
	std::function<void()> onCutsceneCompleteCallback;
};
