#include "SmartSprite.h"

#include "cocos2d.h"

#include "Engine/Lighting/LightEffect.h"

using namespace cocos2d;

SmartSprite *SmartSprite::create(const std::string& filename)
{
    auto ret = new (std::nothrow) SmartSprite;

    if(ret && ret->initWithFile(filename))
	{
        ret->autorelease();
        return ret;
    }

    CC_SAFE_RELEASE(ret);
    return nullptr;
}

SmartSprite::~SmartSprite()
{
    CC_SAFE_RELEASE(_effect);
}

SmartSprite *SmartSprite::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
{
    auto ret = new (std::nothrow) SmartSprite;

    if(ret && ret->initWithSpriteFrame(spriteFrame))
	{
        ret->autorelease();

        return ret;
    }

    CC_SAFE_RELEASE(ret);

    return nullptr;
}


void SmartSprite::setEffect(LightEffect *effect, const std::string &normalMapFilename)
{
    _normalmap = cocos2d::Director::getInstance()->getTextureCache()->addImage(normalMapFilename);
    
    if(_effect != effect)
	{
        CC_SAFE_RELEASE(_effect);
        _effect = effect;
        CC_SAFE_RETAIN(_effect);
        
        setGLProgramState(_effect->getGLProgramState());
    }
}

void SmartSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    if (_effect != nullptr)
    {
        _effect->prepareForRender(this, _normalmap);
    }

    Sprite::draw(renderer, transform, flags);
	
    renderer->render();
}
