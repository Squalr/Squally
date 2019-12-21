#include "CombatFadeInHudFactory.h"

#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/CombatFadeInHud.h"
#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/TriangleFadeIn.h"

using namespace cocos2d;

CombatFadeInHud* CombatFadeInHudFactory::getRandomFadeIn()
{
	return TriangleFadeIn::create();
}
