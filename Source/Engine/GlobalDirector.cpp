#include "GlobalDirector.h"

GlobalDirector* GlobalDirector::instance = nullptr;

GlobalDirector* GlobalDirector::getInstance()
{
	if (GlobalDirector::instance == nullptr)
	{
		GlobalDirector::instance = new GlobalDirector();
	}

	return GlobalDirector::instance;
}

GlobalDirector::GlobalDirector()
{
	this->globalNodes = std::vector<GlobalNode*>();
	this->activeScene = nullptr;
}

GlobalDirector::~GlobalDirector()
{
}

void GlobalDirector::loadScene(Scene* scene)
{
	SceneEvents::TriggerBeforeSceneChange();

	// Although this is counter-intuitive, add the Global Director as a child to whichever scene is active.
	// This will allows for the Global Director's nodes to listen for events
	if (activeScene != nullptr)
	{
		this->getParent()->removeChild(this);
	}

	scene->addChild(this);

	if (this->activeScene == nullptr)
	{
		Director::getInstance()->runWithScene(scene);
	}
	else
	{
		GameUtils::pause(this->activeScene);
		Director::getInstance()->replaceScene(scene);
	}

	this->activeScene = scene;
	GameUtils::resume(scene);
}

void GlobalDirector::registerGlobalNode(GlobalNode* node)
{
	if (node != nullptr)
	{
		this->addChild(node);
		this->globalNodes.push_back(node);
	}
}
