#include "RenderUtils.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCRenderTexture.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/renderer/CCGLProgram.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/ccShaders.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

Sprite* RenderUtils::renderNodeToSprite(Node* target, Vec2 offset, Size renderSize, Size padding)
{
	RenderTexture* renderedNode = RenderTexture::create(renderSize.width + padding.width * 2.0f, renderSize.height + padding.height * 2.0f);

	target->setPosition(-offset + Vec2(padding));
	renderedNode->begin();
	target->visit();
	renderedNode->end();

	// Rasterize the texture to a target
	Sprite* renderSprite = renderedNode->getSprite();

	// The target is attached to the render texture -- decouple it before returning
	GameUtils::changeParent(renderSprite, nullptr, false);
	
	renderSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	renderSprite->setContentSize(renderSize);

	return renderSprite;
}

Sprite* RenderUtils::applyShaderOnce(Sprite* target, std::string vertexShader, std::string fragmentShader, std::function<void(GLProgramState*)> bindStateVariablesCallback)
{
	GLProgram* program = GLProgram::createWithFilenames(vertexShader, fragmentShader);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(program);

	if (bindStateVariablesCallback != nullptr)
	{
		bindStateVariablesCallback(state);
	}

	Vec2 position = target->getPosition();
	Vec2 anchor = target->getAnchorPoint();

	target->setPosition(Vec2::ZERO);
	target->setAnchorPoint(Vec2::ZERO);
	target->setGLProgram(program);
	target->setGLProgramState(state);
	program->use();

	RenderTexture* renderedSprite = RenderTexture::create(target->getContentSize().width, target->getContentSize().height);

	renderedSprite->begin();
	target->visit();
	renderedSprite->end();

	Sprite* rasterizedSprite = renderedSprite->getSprite();

	// The sprite is attached to the render texture -- decouple it before returning
	GameUtils::changeParent(rasterizedSprite, nullptr, false);

	rasterizedSprite->setPosition(position);
	rasterizedSprite->setAnchorPoint(anchor);

	return rasterizedSprite;
}

void RenderUtils::applyShader(cocos2d::Node* target, std::string vertexShader, std::string fragmentShader, std::function<void(GLProgramState*)> bindStateVariablesCallback)
{
	GLProgram* program = GLProgram::createWithFilenames(vertexShader, fragmentShader);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(program);

	if (bindStateVariablesCallback != nullptr)
	{
		bindStateVariablesCallback(state);
	}

	target->setGLProgram(program);
	target->setGLProgramState(state);
	program->use();
}
