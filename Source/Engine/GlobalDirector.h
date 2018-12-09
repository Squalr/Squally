#pragma once
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Scene;
}

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	static void loadScene(cocos2d::Scene* scene, bool saveToHistory = true);
	static void navigateBack(int backCount = 1);
	static void registerGlobalNode(GlobalNode* node);
	static void registerGlobalScene(GlobalScene* node);

protected:
	GlobalDirector();
	virtual ~GlobalDirector();

	cocos2d::Scene* activeScene;
	std::stack<cocos2d::Scene*> sceneHistory;
	std::vector<GlobalNode*> globalNodes;
	std::vector<GlobalScene*> globalScenes;

	static GlobalDirector* instance;
};
