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
	this->globalNodes = new std::vector<GlobalNode*>();
	this->activeScene = nullptr;
}

GlobalDirector::~GlobalDirector()
{
	delete(this->globalNodes);
}

void GlobalDirector::loadScene(Scene* scene)
{
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
		Director::getInstance()->replaceScene(scene);
	}

	this->activeScene = scene;

	// Reinitialize the listeners -- they will have been disposed from the scene change
	for (auto it = this->globalNodes->begin(); it != this->globalNodes->end(); it++)
	{
		(*it)->initializeEventListeners();
	}
}

void GlobalDirector::registerGlobalNode(GlobalNode* node)
{
	if (node != nullptr)
	{
		this->addChild(node);
		this->globalNodes->push_back(node);
		node->initializeEventListeners();
	}
}
