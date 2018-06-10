#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Shaders/PostProcess.h"
#include "Resources.h"
#include "Scenes/Menus/Pause/PauseMenu.h"
#include "Utils/GameUtils.h"
#include "Utils/MathUtils.h"

#include "LevelCamera.h"
#include "LevelMap.h"

using namespace cocos2d;

// Forward declarations
class LevelMap;

class LevelEditor : public FadeScene
{
public:
	static LevelEditor* create();

	void loadLevel(LevelMap* levelMap, Vec2 initPosition);

protected:
	LevelEditor();
	~LevelEditor();

private:
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onMouseWheelScroll(EventMouse* event);
	void onMouseMove(EventMouse* event);
	void update(float) override;
	void onEnter() override;

	Node* cameraNode;
	LevelMap* map;
	LevelCamera* camera;
};
