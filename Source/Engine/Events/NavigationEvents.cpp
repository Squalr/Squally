#include "NavigationEvents.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCValue.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

const std::string NavigationEvents::EventNavigateScene = "EVENT_LOAD_SCENE";

void NavigationEvents::LoadScene(LoadSceneArgs args)
{
	GlobalDirector::loadScene(args.sceneCreator);
}
