#include "CutsceneSequence.h"

CutsceneSequence* CutsceneSequence::create()
{
	CutsceneSequence* instance = new CutsceneSequence();

	instance->autorelease();

	return instance;
}

CutsceneSequence::CutsceneSequence()
{
	this->cutscenes = new std::deque<Cutscene*>();
}

CutsceneSequence::~CutsceneSequence()
{
	for (auto it = this->cutscenes->begin(); it != this->cutscenes->end(); it++)
	{
		(*it)->release();
	}

	delete(this->cutscenes);
}

void CutsceneSequence::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->onCutsceneEndCallback();
	}
}

void CutsceneSequence::setCutsceneEndCallback(std::function<void()> cutsceneCompleteCallback)
{
	this->onCutsceneCompleteCallback = cutsceneCompleteCallback;
}

void CutsceneSequence::cutsceneCompleteCallback()
{

}

void CutsceneSequence::playCutscenes()
{
}

void CutsceneSequence::playNextCutscene()
{
	if (this->cutscenes->size() <= 0)
	{
		if (this->onCutsceneCompleteCallback != nullptr)
		{
			this->onCutsceneCompleteCallback();
		}
		
		return;
	}

	Cutscene* next = this->cutscenes->front();

	this->cutscenes->pop_front();

	this->removeAllChildren();
	this->addChild(next);
}

void CutsceneSequence::enqueueCutscene(Cutscene* cutscene)
{
	cutscene->setCutsceneCompleteCallback(CC_CALLBACK_0(CutsceneSequence::cutsceneCompleteCallback, this));
	this->cutscenes->push_back(cutscene);
}

void CutsceneSequence::onCutsceneEndCallback()
{
	if (this->onCutsceneCompleteCallback != nullptr)
	{
		this->onCutsceneCompleteCallback();
	}
}
