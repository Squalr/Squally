#include "RenderUtils.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCRenderTexture.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/renderer/CCGLProgram.h"

using namespace cocos2d;

Sprite* RenderUtils::renderDrawNode(DrawNode* drawNode, Vec2 offset, Size renderSize)
{
	RenderTexture* renderedDrawNode = RenderTexture::create(renderSize.width, renderSize.height);

	drawNode->setPosition(-offset);
	renderedDrawNode->begin();
	drawNode->visit();
	renderedDrawNode->end();

	// Rasterize the texture to a sprite
	Sprite* renderSprite = renderedDrawNode->getSprite();

	renderSprite->setAnchorPoint(Vec2::ZERO);
	renderSprite->setPosition(offset);
	renderSprite->setContentSize(renderSize);

	return renderSprite;
}

Sprite* RenderUtils::applyShaderOnce(Sprite* sprite, GLProgram* program, GLProgramState* state)
{
	Vec2 position = sprite->getPosition();
	Vec2 anchor = sprite->getAnchorPoint();

	sprite->setPosition(Vec2::ZERO);
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setGLProgram(program);
	sprite->setGLProgramState(state);
	program->use();

	RenderTexture* renderedSprite = RenderTexture::create(sprite->getContentSize().width, sprite->getContentSize().height);

	renderedSprite->begin();
	sprite->visit();
	renderedSprite->end();

	Sprite* rasterizedSprite = renderedSprite->getSprite();

	rasterizedSprite->setPosition(position);
	rasterizedSprite->setAnchorPoint(anchor);

	return rasterizedSprite;
}
