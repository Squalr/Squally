#pragma once
#include <stack>

#include "Engine/GlobalNode.h"
#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Scene;
}

class GlobalHud;

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	static void loadScene(cocos2d::Scene* scene, bool saveToHistory = true);
	static void navigateBack(int backCount = 1);
	static void registerGlobalNode(GlobalNode* node);
	static void registerGlobalNode(GlobalHud* node);
	static void registerGlobalScene(GlobalScene* node);

protected:
	GlobalDirector();
	virtual ~GlobalDirector();

	cocos2d::Scene* activeScene;
	std::stack<cocos2d::Scene*> sceneHistory;
	std::vector<SmartNode*> globalNodes;
	std::vector<GlobalScene*> globalScenes;

	static GlobalDirector* instance;
private:
	typedef GlobalNode super;
};
