#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/MatrixRain/MatrixRain.h"
#include "Level/LevelCamera.h"
#include "Level/Parser/Parser.h"
#include "Minigames/Minigames.h"
#include "Entities/Player/Player.h"
#include "Input/InputManager.h"
#include "Utils/Utils.h"
#include "Shaders/PostProcess.h"
#include "GUI/HUD/Hud.h"
#include "GUI/HUD/HackerModeHud.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Menus/Dialog/DialogMenu.h"
#include "GUI/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

class Level : public FadeScene
{
public:
	static Level* create(std::string levelResourceFilePath);

protected:
	Level(std::string levelResourceFilePath);
	~Level();

private:
	void initializeListeners();
	void enableHackerMode();
	void disableHackerMode();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	virtual void resume(void) override;
	void update(float) override;
	void onEnter() override;

	Layer * background;
	Sprite * hackerModeBackground;
	MatrixRain * hackerModeRain;
	PostProcess* hackerModePostProcessGlow;
	Layer * backgroundLayer;
	Layer * backgroundDecor;
	Layer * backgroundParallax;
	Layer * midgroundLayer;
	Layer * midgroundDecor;
	Layer * entityLayer;
	Layer * objectLayer;
	Layer * collisionLayer;
	Layer * foregroundLayer;
	Layer * foregroundDecor;
	Layer * environmentLayer;
	Layer * gameLayers;
	PostProcess* gamePostProcessInversion;
	PostProcess* gamePostProcessNightVision;
	Hud * hud;
	HackerModeHud * hackerModeHud;

	static Size mapSize;
	static bool hackerMode;
};
