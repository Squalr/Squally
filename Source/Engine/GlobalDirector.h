#pragma once
#include "cocos2d.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/GlobalScene.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	static void loadScene(Scene* scene);
	static void registerGlobalNode(GlobalNode* node);
	static void registerGlobalScene(GlobalScene* node);

protected:
	GlobalDirector();
	~GlobalDirector();

	Scene* activeScene;
	std::vector<GlobalNode*> globalNodes;
	std::vector<GlobalScene*> globalScenes;

	static GlobalDirector* instance;
};
