#include "TriangleFadeIn.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

using namespace cocos2d;

TriangleFadeIn* TriangleFadeIn::create()
{
	TriangleFadeIn* instance = new TriangleFadeIn();

	instance->autorelease();

	return instance;
}

TriangleFadeIn::TriangleFadeIn()
{
}

TriangleFadeIn::~TriangleFadeIn()
{
}

void TriangleFadeIn::runAnim()
{

}
