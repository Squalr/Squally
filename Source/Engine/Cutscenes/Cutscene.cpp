#include "Cutscene.h"

#include "cocos/base/CCInputEvents.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

Cutscene* Cutscene::create(std::function<void()> cutsceneCompleteCallback)
{
	Cutscene* instance = new Cutscene(cutsceneCompleteCallback);

	instance->autorelease();

	return instance;
}

Cutscene::Cutscene(std::function<void()> cutsceneCompleteCallback)
{
	this->activeClip = nullptr;
	this->cutsceneClips = std::deque<CutsceneClip*>();
	this->onCutsceneCompleteCallback = cutsceneCompleteCallback;
}

Cutscene::~Cutscene()
{
	for (auto next : this->cutsceneClips)
	{
		next->release();
	}
}

void Cutscene::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		this->endCutscene();
	});
}

void Cutscene::playCutscenes()
{
	this->playNextCutsceneClip();
}

void Cutscene::playNextCutsceneClip()
{
	if (this->activeClip != nullptr)
	{
		this->removeChild(this->activeClip);
	}

	if (this->cutsceneClips.size() <= 0)
	{
		this->activeClip = nullptr;
		this->endCutscene();
		return;
	}

	this->activeClip = this->cutsceneClips.front();
	this->cutsceneClips.pop_front();

	this->addChild(this->activeClip);
}

void Cutscene::endCutscene()
{
	if (this->onCutsceneCompleteCallback != nullptr)
	{
		this->onCutsceneCompleteCallback();
	}
}

void Cutscene::cutsceneClipCompleteCallback()
{
	this->playNextCutsceneClip();
}

void Cutscene::enqueueCutsceneClip(CutsceneClip* cutscene)
{
	cutscene->setCutsceneClipCompleteCallback(CC_CALLBACK_0(Cutscene::cutsceneClipCompleteCallback, this));
	cutscene->retain();
	this->cutsceneClips.push_back(cutscene);
}
