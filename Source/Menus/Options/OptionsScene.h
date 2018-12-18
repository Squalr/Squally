#pragma once
#include "cocos2d.h"

#include "Engine/GlobalScene.h"

using namespace cocos2d;

namespace cocos2d
{
	class Node;
}

class OptionsMenu;

class OptionsScene : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	OptionsScene();
	~OptionsScene();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* backgroundNode;
	OptionsMenu* menu;

	static OptionsScene* instance;
};

