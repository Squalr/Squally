#pragma once
#include <stack>

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Scene;
}

class GlobalHud;
class GlobalScene;
class SmartScene;

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	static void loadScene(std::function<SmartScene*()> sceneCreator);
	static void registerGlobalNode(GlobalNode* node);
	static void registerGlobalNode(GlobalHud* node);
	static void registerGlobalScene(GlobalScene* node);

protected:
	GlobalDirector();
	virtual ~GlobalDirector();

	SmartScene* activeScene;
	std::vector<SmartNode*> globalNodes;
	std::vector<GlobalScene*> globalScenes;

	static GlobalDirector* instance;
private:
	typedef GlobalNode super;
};
