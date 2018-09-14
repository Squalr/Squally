#include "CutsceneManager.h"

CutsceneManager* CutsceneManager::create(std::function<void()> cutsceneCompleteCallback)
{
	CutsceneManager* instance = new CutsceneManager(cutsceneCompleteCallback);

	instance->autorelease();

	return instance;
}

CutsceneManager::CutsceneManager(std::function<void()> cutsceneCompleteCallback)
{
	this->onCutsceneCompleteCallback = cutsceneCompleteCallback;

	this->cutscenes = new std::deque<Cutscene*>();
}

CutsceneManager::~CutsceneManager()
{
	for (auto it = this->cutscenes->begin(); it != this->cutscenes->end(); it++)
	{
		(*it)->release();
	}

	delete(this->cutscenes);
}

void CutsceneManager::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->onCutsceneEndCallback();
	}
}

void CutsceneManager::enqueueCutscene(Cutscene* cutscene)
{
	this->cutscenes->push_back(cutscene);
}

void CutsceneManager::playCutscenes()
{
	Cutscene* next = this->cutscenes->front();

	this->cutscenes->pop_front();

	this->removeAllChildren();
	this->addChild(next);
}

void CutsceneManager::onCutsceneEndCallback()
{
	if (this->onCutsceneCompleteCallback != nullptr)
	{
		this->onCutsceneCompleteCallback();
	}
}
