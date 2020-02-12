#include "GlobalDirector.h"

#include "cocos/2d/CCScene.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/GlobalNode.h"
#include "Engine/GlobalHud.h"
#include "Engine/Save/SaveManager.h"
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
	this->globalNodes = std::vector<SmartNode*>();
	this->globalScenes = std::vector<GlobalScene*>();
	this->activeScene = nullptr;
}

GlobalDirector::~GlobalDirector()
{
}

void GlobalDirector::loadScene(Scene* scene)
{
	SaveEvents::TriggerSoftSaveGameState();
	SceneEvents::TriggerBeforeSceneChange();

	if (GlobalDirector::getInstance()->activeScene == nullptr)
	{
		Director::getInstance()->runWithScene(scene);
	}
	else
	{
		GlobalDirector::getInstance()->getParent()->removeChildNoExit(GlobalDirector::getInstance());
		GameUtils::pause(GlobalDirector::getInstance()->activeScene);
		Director::getInstance()->replaceScene(scene);
	}

	// Reparent the global director onto the active scene so that all global nodes are part of the active scene graph
	scene->addChild(GlobalDirector::getInstance());

	SaveManager::save();
	GlobalDirector::getInstance()->activeScene = scene;
	GameUtils::resume(scene);

	SceneEvents::TriggerAfterSceneChange();
}

void GlobalDirector::registerGlobalNode(GlobalNode* node)
{
	if (node != nullptr)
	{
		GlobalDirector::getInstance()->addChild(node);
		GlobalDirector::getInstance()->globalNodes.push_back(node);
	}
}

void GlobalDirector::registerGlobalNode(GlobalHud* node)
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
