#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/MatrixRain/MatrixRain.h"
#include "Level/LevelCamera.h"
#include "Level/Parser/Parser.h"
#include "Entities/Player/Player.h"
#include "Input/InputManager.h"
#include "Utils/GameUtils.h"
#include "Shaders/PostProcess.h"
#include "GUI/HUD/Hud.h"
#include "GUI/HUD/HackerModeHud.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Menus/Dialog/DialogMenu.h"
#include "GUI/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

class Fight : public FadeScene
{
public:
	static Fight* create();

	// TODO: Potentially just have an internal struct, and have a full Entity pointer passed. May need to dynamic upcast to get specialized info for player/enemies tho.
	struct EntityData
	{
		int health;
		int maxHealth;
		float energy;
		float maxEnergy;
		void* inventory; // TODO, maybe

		EntityData(int health, int maxHealth, float energy, float maxEnergy) : health(health), maxHealth(maxHealth), energy(energy), maxEnergy(maxEnergy) {}
	};

	struct FightData
	{

	};

	void loadFight(FightData fightData);

protected:
	Fight();
	~Fight();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	Layer * background;
	Sprite * hackerModeBackground;
	Layer * entityLayer;
	Layer * objectLayer;
};
