#include "NavigationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

const std::string NavigationEvents2::EventNavigateScene = "EVENT_LOAD_SCENE";

void NavigationEvents2::LoadScene(LoadSceneArgs args)
{
	GlobalDirector::loadScene(args.scene);
}

void NavigationEvents2::NavigateBack(int backCount)
{
	GlobalDirector::navigateBack(backCount);
}
