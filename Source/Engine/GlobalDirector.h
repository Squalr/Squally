#pragma once
#include <stack>

#include "Engine/GlobalNode.h"

class GlobalHud;
class GlobalScene;
class SmartScene;

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	static void loadScene(std::function<SmartScene*()> sceneCreator);
	static void RegisterGlobalNode(GlobalNode* node);
	static void RegisterGlobalNode(GlobalHud* node);
	static void RegisterGlobalScene(GlobalScene* node);

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
