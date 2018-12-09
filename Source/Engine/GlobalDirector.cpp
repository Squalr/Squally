#include "GlobalDirector.h"

#include "cocos/2d/CCScene.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

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
	this->globalScenes = std::vector<GlobalScene*>();
	this->activeScene = nullptr;
}

GlobalDirector::~GlobalDirector()
{
}

void GlobalDirector::loadScene(Scene* scene, bool saveToHistory)
{
	SceneEvents::TriggerBeforeSceneChange();

	// Although this is counter-intuitive, add the Global Director as a child to whichever scene is active.
	// This will allows for the Global Director's nodes to listen for events
	if (GlobalDirector::getInstance()->activeScene != nullptr)
	{
		if (saveToHistory)
		{
			GlobalDirector::getInstance()->sceneHistory.push(GlobalDirector::getInstance()->activeScene);
		}
		
		GlobalDirector::getInstance()->getParent()->removeChild(GlobalDirector::getInstance());
	}

	scene->addChild(GlobalDirector::getInstance());

	if (GlobalDirector::getInstance()->activeScene == nullptr)
	{
		Director::getInstance()->runWithScene(scene);
	}
	else
	{
		GameUtils::pause(GlobalDirector::getInstance()->activeScene);
		Director::getInstance()->replaceScene(scene);
	}

	GlobalDirector::getInstance()->activeScene = scene;
	GameUtils::resume(scene);
}

void GlobalDirector::navigateBack(int backCount)
{
	Scene* scene = GlobalDirector::getInstance()->activeScene;

	for (int index = 0; index < backCount; index++)
	{
		if (GlobalDirector::getInstance()->sceneHistory.size() <= 0)
		{
			break;
		}

		scene = GlobalDirector::getInstance()->sceneHistory.top();
		GlobalDirector::getInstance()->sceneHistory.pop();
	}

	GlobalDirector::getInstance()->loadScene(scene, false);
}

void GlobalDirector::registerGlobalNode(GlobalNode* node)
{
	if (node != nullptr)
	{
		GlobalDirector::getInstance()->addChild(node);
		GlobalDirector::getInstance()->globalNodes.push_back(node);
	}
}

void GlobalDirector::registerGlobalScene(GlobalScene* scene)
{
	if (scene != nullptr)
	{
		scene->retain();

		GlobalDirector::getInstance()->globalScenes.push_back(scene);
	}
}
