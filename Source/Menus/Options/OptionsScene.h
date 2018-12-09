#pragma once
#include "cocos2d.h"

#include "Engine/GlobalScene.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/MenuBackground.h"

using namespace cocos2d;

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

	Node* backgroundNode;
	OptionsMenu* menu;

	static OptionsScene* instance;
};

