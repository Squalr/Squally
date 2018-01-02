#include "EffectSprite.h"
#include "LightEffect.h"

EffectSprite *EffectSprite::create(const std::string& filename)
{
	EffectSprite* ret = new EffectSprite();

	if (ret && ret->initWithFile(filename))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_RELEASE(ret);
	return nullptr;
}

EffectSprite *EffectSprite::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
{
	EffectSprite* ret = new EffectSprite();

	if (ret && ret->initWithSpriteFrame(spriteFrame))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_RELEASE(ret);
	return nullptr;

}

void EffectSprite::setEffect(LightEffect *newEffect, const std::string &normalMapFilename)
{
	this->normalmap = cocos2d::Director::getInstance()->getTextureCache()->addImage(normalMapFilename);

	if (this->effect != newEffect) {

		CC_SAFE_RELEASE(this->effect);
		this->effect = newEffect;
		CC_SAFE_RETAIN(this->effect);

		setGLProgramState(this->effect->getGLProgramState());
	}
}

void EffectSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	if (this->effect != nullptr)
	{
		this->effect->prepareForRender(this, this->normalmap);
	}

	Sprite::draw(renderer, transform, flags);
	renderer->render();
}

EffectSprite::~EffectSprite()
{
	CC_SAFE_RELEASE(effect);
}
