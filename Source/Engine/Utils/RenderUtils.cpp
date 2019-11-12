#include "RenderUtils.h"

#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCRenderTexture.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCGLProgram.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/ccShaders.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Camera/GameCamera.h"

using namespace cocos2d;

Sprite* RenderUtils::renderNodeToSprite(Node* target, Vec2 offset, Size renderSize, Size padding)
{
	if (renderSize.width <= 0 || renderSize.height <= 0)
	{
		return Sprite::create();
	}

	RenderTexture* renderedNode = RenderTexture::create(int(renderSize.width + padding.width * 2.0f), int(renderSize.height + padding.height * 2.0f));

	if (renderedNode == nullptr)
	{
		return Sprite::create();
	}

	target->setPosition(Vec2(padding.width - offset.x, padding.height - offset.y));
	
	// Reset camera such that the rendering performs properly
	Vec3 cameraPosition = GameCamera::getInstance()->getCameraPosition3();

	if (Camera::getDefaultCamera() != nullptr)
	{
		Camera::getDefaultCamera()->initDefault();
	}

	renderedNode->begin();
	target->visit();
	renderedNode->end();

	// Restore camera
	GameCamera::getInstance()->setCameraPosition3(cameraPosition);

	// Rasterize the texture to a target
	Sprite* renderSprite = renderedNode->getSprite();

	// The target is attached to the render texture -- decouple it before returning
	GameUtils::changeParent(renderSprite, nullptr, false);
	
	renderSprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	return renderSprite;
}

Sprite* RenderUtils::applyShaderOnce(Sprite* target, std::string vertexShader, std::string fragmentShader, std::function<void(GLProgramState*)> bindStateVariablesCallback)
{
	if (target == nullptr)
	{
		return nullptr;
	}

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

	RenderTexture* renderedSprite = RenderTexture::create(int(target->getContentSize().width), int(target->getContentSize().height));

	if (renderedSprite == nullptr)
	{
		return target;
	}

	// Reset camera such that the rendering performs properly
	Vec3 cameraPosition = GameCamera::getInstance()->getCameraPosition3();

	if (Camera::getDefaultCamera() != nullptr)
	{
		Camera::getDefaultCamera()->initDefault();
	}

	renderedSprite->begin();
	target->visit();
	renderedSprite->end();

	// Restore camera
	GameCamera::getInstance()->setCameraPosition3(cameraPosition);

	Sprite* rasterizedSprite = renderedSprite->getSprite();

	if (rasterizedSprite == nullptr)
	{
		return target;
	}

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
