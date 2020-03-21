#include "NavigationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

const std::string NavigationEvents::EventNavigateScene = "EVENT_LOAD_SCENE";

void NavigationEvents::LoadScene(LoadSceneArgs args)
{
	GlobalDirector::loadScene(args.sceneCreator);
}
