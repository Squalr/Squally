/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

// ideas taken from:
//     . The ocean spray in your face [Jeff Lander]
//        http://www.double.co.nz/dust/col0798.pdf
//     . Building an Advanced Particle System [John van der Burg]
//        http://www.gamasutra.com/features/20000623/vanderburg_01.htm
//   . LOVE game engine
//        http://love2d.org/
//
//
// Radius mode support, from 71 squared
//        http://particledesigner.71squared.com/
//
// IMPORTANT: Particle Designer is supported by cocos2d, but
// 'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guaranteed in cocos2d,
//  cocos2d uses a another approach, but the results are almost identical. 
//

#include "2d/CCParticleSystem.h"

#include <string>

#include "2d/CCParticleBatchNode.h"
#include "base/CCConsole.h"
#include "base/base64.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTextureCache.h"
#include "platform/CCFileUtils.h"

using namespace std;

NS_CC_BEGIN

const float ParticleSystem::DURATION_INFINITY = -1.0f;
const float ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE = -1.0f;
const float ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS = -1.0f;

// ideas taken from:
//     . The ocean spray in your face [Jeff Lander]
//        http://www.double.co.nz/dust/col0798.pdf
//     . Building an Advanced Particle System [John van der Burg]
//        http://www.gamasutra.com/features/20000623/vanderburg_01.htm
//   . LOVE game engine
//        http://love2d.org/
//
//
// Radius mode support, from 71 squared
//        http://particledesigner.71squared.com/
//
// IMPORTANT: Particle Designer is supported by cocos2d, but
// 'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guaranteed in cocos2d,
//  cocos2d uses a another approach, but the results are almost identical. 
//


inline void normalize_point(float x, float y, particle_point* out)
{
    float n = x * x + y * y;
    // Already normalized.
    if (n == 1.0f)
        return;
    
    n = sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;
    
    n = 1.0f / n;
    out->x = x * n;
    out->y = y * n;
}

/**
 A more effect random number getter function, get from ejoy2d.
 */
inline static float RANDOM_M11(unsigned int *seed) {
    *seed = *seed * 134775813 + 1;
    union {
        uint32_t d;                                     
        float f;
    } u;
    u.d = (((uint32_t)(*seed) & 0x7fff) << 8) | 0x40000000;
    return u.f - 3.0f;
}

ParticleData::ParticleData()
{
    memset(this, 0, sizeof(ParticleData));
}

bool ParticleData::init(int count)
{
    maxCount = count;

    range = std::vector<int>(count);

    for (int index = 0; index < count; index++)
    {
        range[index] = index;
    }
    
    posx= (float*)malloc(count * sizeof(float));
    posy= (float*)malloc(count * sizeof(float));
    startPosX= (float*)malloc(count * sizeof(float));
    startPosY= (float*)malloc(count * sizeof(float));
    colorR= (float*)malloc(count * sizeof(float));
    colorG= (float*)malloc(count * sizeof(float));
    colorB= (float*)malloc(count * sizeof(float));
    colorA= (float*)malloc(count * sizeof(float));
    deltaColorR= (float*)malloc(count * sizeof(float));
    deltaColorG= (float*)malloc(count * sizeof(float));
    deltaColorB= (float*)malloc(count * sizeof(float));
    deltaColorA= (float*)malloc(count * sizeof(float));
    size= (float*)malloc(count * sizeof(float));
    deltaSize= (float*)malloc(count * sizeof(float));
    rotation= (float*)malloc(count * sizeof(float));
    deltaRotation= (float*)malloc(count * sizeof(float));
    timeToLive= (float*)malloc(count * sizeof(float));
    atlasIndex= (unsigned int*)malloc(count * sizeof(unsigned int));
    
    modeA.dirX= (float*)malloc(count * sizeof(float));
    modeA.dirY= (float*)malloc(count * sizeof(float));
    modeA.radialAccel= (float*)malloc(count * sizeof(float));
    modeA.tangentialAccel= (float*)malloc(count * sizeof(float));
    
    modeB.angle= (float*)malloc(count * sizeof(float));
    modeB.degreesPerSecond= (float*)malloc(count * sizeof(float));
    modeB.deltaRadius= (float*)malloc(count * sizeof(float));
    modeB.radius= (float*)malloc(count * sizeof(float));
    
    return posx && posy && startPosY && startPosX && colorR && colorG && colorB && colorA &&
    deltaColorR && deltaColorG && deltaColorB && deltaColorA && size && deltaSize &&
    rotation && deltaRotation && timeToLive && atlasIndex && modeA.dirX && modeA.dirY &&
    modeA.radialAccel && modeA.tangentialAccel && modeB.angle && modeB.degreesPerSecond &&
    modeB.deltaRadius && modeB.radius;
}

void ParticleData::release()
{
    CC_SAFE_FREE(posx);
    CC_SAFE_FREE(posy);
    CC_SAFE_FREE(startPosX);
    CC_SAFE_FREE(startPosY);
    CC_SAFE_FREE(colorR);
    CC_SAFE_FREE(colorG);
    CC_SAFE_FREE(colorB);
    CC_SAFE_FREE(colorA);
    CC_SAFE_FREE(deltaColorR);
    CC_SAFE_FREE(deltaColorG);
    CC_SAFE_FREE(deltaColorB);
    CC_SAFE_FREE(deltaColorA);
    CC_SAFE_FREE(size);
    CC_SAFE_FREE(deltaSize);
    CC_SAFE_FREE(rotation);
    CC_SAFE_FREE(deltaRotation);
    CC_SAFE_FREE(timeToLive);
    CC_SAFE_FREE(atlasIndex);
    
    CC_SAFE_FREE(modeA.dirX);
    CC_SAFE_FREE(modeA.dirY);
    CC_SAFE_FREE(modeA.radialAccel);
    CC_SAFE_FREE(modeA.tangentialAccel);
    
    CC_SAFE_FREE(modeB.angle);
    CC_SAFE_FREE(modeB.degreesPerSecond);
    CC_SAFE_FREE(modeB.deltaRadius);
    CC_SAFE_FREE(modeB.radius);
}

Vector<ParticleSystem*> ParticleSystem::__allInstances;
std::map<std::string, ValueMap> ParticleSystem::DictCache = std::map<std::string, ValueMap>();
float ParticleSystem::__totalParticleCountFactor = 1.0f;

ParticleSystem::ParticleSystem()
: _isBlendAdditive(false)
, _isAutoRemoveOnFinish(false)
, _plistFile("")
, _elapsed(0)
, _configName("")
, _emitCounter(0)
, _batchNode(nullptr)
, _atlasIndex(0)
, _transformSystemDirty(false)
, _allocatedParticles(0)
, _isActive(true)
, _particleCount(0)
, _duration(0)
, _life(0)
, _lifeVar(0)
, _angle(0)
, _angleVar(0)
, _emitterMode(Mode::GRAVITY)
, _startSize(0)
, _startSizeVar(0)
, _endSize(0)
, _endSizeVar(0)
, _startSpin(0)
, _startSpinVar(0)
, _endSpin(0)
, _endSpinVar(0)
, _emissionRate(0)
, _totalParticles(0)
, _texture(nullptr)
, _blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
, _opacityModifyRGB(false)
, _yCoordFlipped(1)
, _positionType(PositionType::FREE)
, _paused(false)
, _canUpdate(true)
, _sourcePositionCompatible(true) // In the furture this member's default value maybe false or be removed.
{
    modeA.gravity.setZero();
    modeA.speed = 0;
    modeA.speedVar = 0;
    modeA.tangentialAccel = 0;
    modeA.tangentialAccelVar = 0;
    modeA.radialAccel = 0;
    modeA.radialAccelVar = 0;
    modeA.rotationIsDir = false;
    modeB.startRadius = 0;
    modeB.startRadiusVar = 0;
    modeB.endRadius = 0;
    modeB.endRadiusVar = 0;            
    modeB.rotatePerSecond = 0;
    modeB.rotatePerSecondVar = 0;
}
// implementation ParticleSystem

ParticleSystem * ParticleSystem::create(const std::string& plistFile)
{
    ParticleSystem *ret = new (std::nothrow) ParticleSystem();
    if (ret && ret->initWithFile(plistFile))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

ParticleSystem* ParticleSystem::createWithTotalParticles(int numberOfParticles)
{
    ParticleSystem *ret = new (std::nothrow) ParticleSystem();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

// static
Vector<ParticleSystem*>& ParticleSystem::getAllParticleSystems()
{
    return __allInstances;
}

void ParticleSystem::setTotalParticleCountFactor(float factor)
{
    __totalParticleCountFactor = factor;
}

bool ParticleSystem::init()
{
    return initWithTotalParticles(150);
}

bool ParticleSystem::initWithFile(const std::string& plistFile)
{
    bool ret = false;
    
    _plistFile = FileUtils::getInstance()->fullPathForFilename(plistFile);

    if (ParticleSystem::DictCache.find(plistFile) == ParticleSystem::DictCache.end())
    {
        ParticleSystem::DictCache[plistFile] = FileUtils::getInstance()->getValueMapFromFile(_plistFile);

        CCASSERT( !ParticleSystem::DictCache[plistFile].empty(), "Particles: file not found");
    }
    
    // FIXME: compute path from a path, should define a function somewhere to do it
    string listFilePath = plistFile;
    
    if (listFilePath.find('/') != string::npos)
    {
        listFilePath = listFilePath.substr(0, listFilePath.rfind('/') + 1);
        ret = this->initWithDictionary(ParticleSystem::DictCache[plistFile], listFilePath);
    }
    else
    {
        ret = this->initWithDictionary(ParticleSystem::DictCache[plistFile], "");
    }
    
    return ret;
}

bool ParticleSystem::initWithDictionary(ValueMap& dictionary)
{
    return initWithDictionary(dictionary, "");
}

bool ParticleSystem::initWithDictionary(ValueMap& dictionary, const std::string& dirname)
{
    bool ret = false;
    unsigned char *buffer = nullptr;
    unsigned char *deflated = nullptr;
    Image *image = nullptr;
    do 
    {
        int maxParticles = dictionary["maxParticles"].asInt();
        // self, not super
        if(this->initWithTotalParticles(maxParticles))
        {
            // Emitter name in particle designer 2.0
            _configName = dictionary["configName"].asString();

            // angle
            _angle = dictionary["angle"].asFloat();
            _angleVar = dictionary["angleVariance"].asFloat();

            // duration
            _duration = dictionary["duration"].asFloat();

            // blend function 
            if (!_configName.empty())
            {
                _blendFunc.src = dictionary["blendFuncSource"].asFloat();
            }
            else
            {
                _blendFunc.src = dictionary["blendFuncSource"].asInt();
            }
            _blendFunc.dst = dictionary["blendFuncDestination"].asInt();

            // color
            _startColor.r = dictionary["startColorRed"].asFloat();
            _startColor.g = dictionary["startColorGreen"].asFloat();
            _startColor.b = dictionary["startColorBlue"].asFloat();
            _startColor.a = dictionary["startColorAlpha"].asFloat();

            _startColorVar.r = dictionary["startColorVarianceRed"].asFloat();
            _startColorVar.g = dictionary["startColorVarianceGreen"].asFloat();
            _startColorVar.b = dictionary["startColorVarianceBlue"].asFloat();
            _startColorVar.a = dictionary["startColorVarianceAlpha"].asFloat();

            _endColor.r = dictionary["finishColorRed"].asFloat();
            _endColor.g = dictionary["finishColorGreen"].asFloat();
            _endColor.b = dictionary["finishColorBlue"].asFloat();
            _endColor.a = dictionary["finishColorAlpha"].asFloat();

            _endColorVar.r = dictionary["finishColorVarianceRed"].asFloat();
            _endColorVar.g = dictionary["finishColorVarianceGreen"].asFloat();
            _endColorVar.b = dictionary["finishColorVarianceBlue"].asFloat();
            _endColorVar.a = dictionary["finishColorVarianceAlpha"].asFloat();

            // particle size
            _startSize = dictionary["startParticleSize"].asFloat();
            _startSizeVar = dictionary["startParticleSizeVariance"].asFloat();
            _endSize = dictionary["finishParticleSize"].asFloat();
            _endSizeVar = dictionary["finishParticleSizeVariance"].asFloat();

            // position
            float x = dictionary["sourcePositionx"].asFloat();
            float y = dictionary["sourcePositiony"].asFloat();
	    if(!_sourcePositionCompatible) {
                this->setSourcePosition(Vec2(x, y));
	    }
            else {
		this->setPosition(Vec2(x, y));
	    }
            _posVar.x = dictionary["sourcePositionVariancex"].asFloat();
            _posVar.y = dictionary["sourcePositionVariancey"].asFloat();

            // Spinning
            _startSpin = dictionary["rotationStart"].asFloat();
            _startSpinVar = dictionary["rotationStartVariance"].asFloat();
            _endSpin= dictionary["rotationEnd"].asFloat();
            _endSpinVar= dictionary["rotationEndVariance"].asFloat();

            _emitterMode = (Mode) dictionary["emitterType"].asInt();

            // Mode A: Gravity + tangential accel + radial accel
            if (_emitterMode == Mode::GRAVITY)
            {
                // gravity
                modeA.gravity.x = dictionary["gravityx"].asFloat();
                modeA.gravity.y = dictionary["gravityy"].asFloat();

                // speed
                modeA.speed = dictionary["speed"].asFloat();
                modeA.speedVar = dictionary["speedVariance"].asFloat();

                // radial acceleration
                modeA.radialAccel = dictionary["radialAcceleration"].asFloat();
                modeA.radialAccelVar = dictionary["radialAccelVariance"].asFloat();

                // tangential acceleration
                modeA.tangentialAccel = dictionary["tangentialAcceleration"].asFloat();
                modeA.tangentialAccelVar = dictionary["tangentialAccelVariance"].asFloat();
                
                // rotation is dir
                modeA.rotationIsDir = dictionary["rotationIsDir"].asBool();
            }

            // or Mode B: radius movement
            else if (_emitterMode == Mode::RADIUS)
            {
                if (!_configName.empty())
                {
                    modeB.startRadius = dictionary["maxRadius"].asInt();
                }
                else
                {
                    modeB.startRadius = dictionary["maxRadius"].asFloat();
                }
                modeB.startRadiusVar = dictionary["maxRadiusVariance"].asFloat();
                if (!_configName.empty())
                {
                    modeB.endRadius = dictionary["minRadius"].asInt();
                }
                else
                {
                    modeB.endRadius = dictionary["minRadius"].asFloat();
                }
                
                if (dictionary.find("minRadiusVariance") != dictionary.end())
                {
                    modeB.endRadiusVar = dictionary["minRadiusVariance"].asFloat();
                }
                else
                {
                    modeB.endRadiusVar = 0.0f;
                }
                
                if (!_configName.empty())
                {
                    modeB.rotatePerSecond = dictionary["rotatePerSecond"].asInt();
                }
                else
                {
                    modeB.rotatePerSecond = dictionary["rotatePerSecond"].asFloat();
                }
                modeB.rotatePerSecondVar = dictionary["rotatePerSecondVariance"].asFloat();

            } else {
                CCASSERT( false, "Invalid emitterType in config file");
                CC_BREAK_IF(true);
            }

            // life span
            _life = dictionary["particleLifespan"].asFloat();
            _lifeVar = dictionary["particleLifespanVariance"].asFloat();

            // emission Rate
            _emissionRate = _totalParticles / _life;

            //don't get the internal texture if a batchNode is used
            if (!_batchNode)
            {
                // Set a compatible default for the alpha transfer
                _opacityModifyRGB = false;

                // texture        
                // Try to get the texture from the cache
                std::string textureName = dictionary["textureFileName"].asString();

                
                if(dictionary.find("textureImageData") != dictionary.end())
                {
                    Texture2D* tex = Director::getInstance()->getTextureCache()->getTextureForKey(_plistFile);
                
                    if (tex)
                    {
                        setTexture(tex);
                    }
                    else
                    {
                        std::string textureData = dictionary.at("textureImageData").asString();
                        CCASSERT(!textureData.empty(), "textureData can't be empty!");
                        
                        auto dataLen = textureData.size();
                        if (dataLen != 0)
                        {
                            // if it fails, try to get it from the base64-data (must not be zipped)
                            int decodeLen = base64Decode((unsigned char*)textureData.c_str(), (unsigned int)dataLen, &buffer);
                            CCASSERT( buffer != nullptr, "CCParticleSystem: error decoding textureImageData");
                            CC_BREAK_IF(!buffer);
                            
                            // For android, we should retain it in VolatileTexture::addImage which invoked in Director::getInstance()->getTextureCache()->addUIImage()
                            image = new (std::nothrow) Image();
                            bool isOK = image->initWithImageData(buffer, decodeLen);
                            CCASSERT(isOK, "CCParticleSystem: error init image with Data");
                            CC_BREAK_IF(!isOK);
                            
                            setTexture(Director::getInstance()->getTextureCache()->addImage(image, _plistFile));

                            image->release();
                        }
                    }
                }
                else
                {
                    size_t rPos = textureName.rfind('/');
                
                    if (rPos != string::npos)
                    {
                        string textureDir = textureName.substr(0, rPos + 1);
                        
                        if (!dirname.empty() && textureDir != dirname)
                        {
                            textureName = textureName.substr(rPos+1);
                            textureName = dirname + textureName;
                        }
                    }
                    else if (!dirname.empty() && !textureName.empty())
                    {
                        textureName = dirname + textureName;
                    }
                    
                    if (!textureName.empty())
                    {
                        setTexture(Director::getInstance()->getTextureCache()->addImage(textureName));
                    }
                }
                
                _yCoordFlipped = dictionary.find("yCoordFlipped") == dictionary.end() ? 1 : dictionary.at("yCoordFlipped").asInt();

                if(!this->_texture)
                {
                    CCLOGWARN("cocos2d: Warning: ParticleSystemQuad system without a texture");
                }
            }
            ret = true;
        }
    } while (0);
    free(buffer);
    free(deflated);
    return ret;
}

bool ParticleSystem::initWithTotalParticles(int numberOfParticles)
{
    _totalParticles = numberOfParticles;
    
    _particleData.release();

    if( !_particleData.init(_totalParticles) )
    {
        CCLOG("Particle system: not enough memory");
        this->release();
        return false;
    }
    _allocatedParticles = numberOfParticles;

    if (_batchNode)
    {
        for (int i = 0; i < _totalParticles; i++)
        {
            _particleData.atlasIndex[i] = i;
        }
    }
    // default, active
    _isActive = true;

    // default blend function
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    // default movement type;
    _positionType = PositionType::FREE;

    // by default be in mode A:
    _emitterMode = Mode::GRAVITY;

    // default: modulate
    // FIXME:: not used
    //    colorModulate = YES;

    _isAutoRemoveOnFinish = false;

    // Optimization: compile updateParticle method
    //updateParticleSel = @selector(updateQuadWithParticle:newPosition:);
    //updateParticleImp = (CC_UPDATE_PARTICLE_IMP) [self methodForSelector:updateParticleSel];
    //for batchNode
    _transformSystemDirty = false;

    return true;
}

ParticleSystem::~ParticleSystem()
{
    // Since the scheduler retains the "target (in this case the ParticleSystem)
	// it is not needed to call "unscheduleUpdate" here. In fact, it will be called in "cleanup"
    //unscheduleUpdate();
    _particleData.release();
    CC_SAFE_RELEASE(_texture);
}

void ParticleSystem::addParticles(int count)
{
    if (_paused)
        return;
    uint32_t RANDSEED = rand();

    int start = _particleCount;
    _particleCount += count;
    
    Vec2 pos = (_positionType == PositionType::FREE) ? this->convertToWorldSpace(Vec2::ZERO) : _position;
    
    //color
    #define SET_COLOR(c, b, v)\
    c[i] = clampf( b + v * RANDOM_M11(&RANDSEED) , 0 , 1 );
        
    #define SET_DELTA_COLOR(c, dc)\
    dc[i] = (dc[i] - c[i]) / _particleData.timeToLive[i];
    
    for (int i = start; i < _particleCount ; ++i)
    {
        float theLife = _life + _lifeVar * RANDOM_M11(&RANDSEED);
        _particleData.timeToLive[i] = MAX(0, theLife);
        _particleData.posx[i] = _sourcePosition.x + _posVar.x * RANDOM_M11(&RANDSEED);
        _particleData.posy[i] = _sourcePosition.y + _posVar.y * RANDOM_M11(&RANDSEED);
    
        SET_COLOR(_particleData.colorR, _startColor.r, _startColorVar.r);
        SET_COLOR(_particleData.colorG, _startColor.g, _startColorVar.g);
        SET_COLOR(_particleData.colorB, _startColor.b, _startColorVar.b);
        SET_COLOR(_particleData.colorA, _startColor.a, _startColorVar.a);

        SET_COLOR(_particleData.deltaColorR, _endColor.r, _endColorVar.r);
        SET_COLOR(_particleData.deltaColorG, _endColor.g, _endColorVar.g);
        SET_COLOR(_particleData.deltaColorB, _endColor.b, _endColorVar.b);
        SET_COLOR(_particleData.deltaColorA, _endColor.a, _endColorVar.a);
    
        SET_DELTA_COLOR(_particleData.colorR, _particleData.deltaColorR);
        SET_DELTA_COLOR(_particleData.colorG, _particleData.deltaColorG);
        SET_DELTA_COLOR(_particleData.colorB, _particleData.deltaColorB);
        SET_DELTA_COLOR(_particleData.colorA, _particleData.deltaColorA);

        _particleData.size[i] = _startSize + _startSizeVar * RANDOM_M11(&RANDSEED);
        _particleData.size[i] = MAX(0, _particleData.size[i]);
        _particleData.deltaSize[i] = (_endSize != START_SIZE_EQUAL_TO_END_SIZE) 
            ? (MAX(0, _endSize + _endSizeVar * RANDOM_M11(&RANDSEED)) - _particleData.size[i]) / _particleData.timeToLive[i]
            : 0.0f;
        _particleData.rotation[i] = _startSpin + _startSpinVar * RANDOM_M11(&RANDSEED);
        _particleData.deltaRotation[i] = ((_endSpin + _endSpinVar * RANDOM_M11(&RANDSEED)) - _particleData.rotation[i]) / _particleData.timeToLive[i];
        _particleData.startPosX[i] = pos.x;
        _particleData.startPosY[i] = pos.y;
    }
    
    // Mode Gravity: A
    if (_emitterMode == Mode::GRAVITY)
    {
        // rotation is dir
        if( modeA.rotationIsDir )
        {
            for (int i = start; i < _particleCount; ++i)
            {
                _particleData.modeA.radialAccel[i] = modeA.radialAccel + modeA.radialAccelVar * RANDOM_M11(&RANDSEED);
                _particleData.modeA.tangentialAccel[i] = modeA.tangentialAccel + modeA.tangentialAccelVar * RANDOM_M11(&RANDSEED);
                float a = CC_DEGREES_TO_RADIANS( _angle + _angleVar * RANDOM_M11(&RANDSEED) );
                Vec2 v(cosf( a ), sinf( a ));
                float s = modeA.speed + modeA.speedVar * RANDOM_M11(&RANDSEED);
                Vec2 dir = v * s;
                _particleData.modeA.dirX[i] = dir.x;//v * s ;
                _particleData.modeA.dirY[i] = dir.y;
                _particleData.rotation[i] = -CC_RADIANS_TO_DEGREES(dir.getAngle());
            }
        }
        else
        {
            for (int i = start; i < _particleCount; ++i)
            {
                _particleData.modeA.radialAccel[i] = modeA.radialAccel + modeA.radialAccelVar * RANDOM_M11(&RANDSEED);
                _particleData.modeA.tangentialAccel[i] = modeA.tangentialAccel + modeA.tangentialAccelVar * RANDOM_M11(&RANDSEED);
                float a = CC_DEGREES_TO_RADIANS( _angle + _angleVar * RANDOM_M11(&RANDSEED) );
                Vec2 v(cosf( a ), sinf( a ));
                float s = modeA.speed + modeA.speedVar * RANDOM_M11(&RANDSEED);
                Vec2 dir = v * s;
                _particleData.modeA.dirX[i] = dir.x;//v * s ;
                _particleData.modeA.dirY[i] = dir.y;
            }
        }
        
    }
    // Mode Radius: B
    else
    {
        for (int i = start; i < _particleCount; ++i)
        {
            _particleData.modeB.radius[i] = modeB.startRadius + modeB.startRadiusVar * RANDOM_M11(&RANDSEED);
            _particleData.modeB.angle[i] = CC_DEGREES_TO_RADIANS( _angle + _angleVar * RANDOM_M11(&RANDSEED));
            _particleData.modeB.degreesPerSecond[i] = CC_DEGREES_TO_RADIANS(modeB.rotatePerSecond + modeB.rotatePerSecondVar * RANDOM_M11(&RANDSEED));
            _particleData.modeB.deltaRadius[i] = (modeB.endRadius == START_RADIUS_EQUAL_TO_END_RADIUS)
                ? 0.0f
                : ((modeB.endRadius + modeB.endRadiusVar * RANDOM_M11(&RANDSEED)) - _particleData.modeB.radius[i]) / _particleData.timeToLive[i];
        
        }
    }
}

void ParticleSystem::onEnter()
{
    Node::onEnter();
    
    // update after action in run!
    this->scheduleUpdate();

    __allInstances.pushBack(this);
}

void ParticleSystem::onExit()
{
    this->unscheduleUpdate();
    Node::onExit();

    auto iter = std::find(std::begin(__allInstances), std::end(__allInstances), this);
    if (iter != std::end(__allInstances))
    {
        __allInstances.erase(iter);
    }
}

void ParticleSystem::stopSystem()
{
    _isActive = false;
    _elapsed = _duration;
    _emitCounter = 0;
}

void ParticleSystem::resetSystem()
{
    _isActive = true;
    _elapsed = 0;
    for (int i = 0; i < _particleCount; ++i)
    {
        _particleData.timeToLive[i] = 0.0f;
    }
}

bool ParticleSystem::isFull()
{
    return (_particleCount == _totalParticles);
}

// ParticleSystem - MainLoop
void ParticleSystem::update(float dt)
{
    if (!this->canUpdate())
    {
        return;
    }

    if (_isActive && _emissionRate)
    {
        float rate = 1.0f / _emissionRate;
        int totalParticles = static_cast<int>(_totalParticles * __totalParticleCountFactor);
        
        //issue #1201, prevent bursts of particles, due to too high emitCounter
        if (_particleCount < totalParticles)
        {
            _emitCounter += dt;
            if (_emitCounter < 0.f)
                _emitCounter = 0.f;
        }
        
        int emitCount = MIN(totalParticles - _particleCount, _emitCounter / rate);
        addParticles(emitCount);
        _emitCounter -= rate * emitCount;
        
        _elapsed += dt;
        if (_elapsed < 0.f)
        {
            _elapsed = 0.f;
        }

        if (_duration != DURATION_INFINITY && _duration < _elapsed)
        {
            this->stopSystem();
        }
    }
    
    {
        for (int i = 0; i < _particleCount; ++i)
        {
            _particleData.timeToLive[i] -= dt;
        }
        
        for (int i = 0; i < _particleCount; ++i)
        {
            if (_particleData.timeToLive[i] <= 0.0f)
            {
                int j = _particleCount - 1;
                while (j > 0 && _particleData.timeToLive[j] <= 0)
                {
                    _particleCount--;
                    j--;
                }
                _particleData.copyParticle(i, _particleCount - 1);
                if (_batchNode)
                {
                    //disable the switched particle
                    int currentIndex = _particleData.atlasIndex[i];
                    _batchNode->disableParticle(_atlasIndex + currentIndex);
                    //switch indexes
                    _particleData.atlasIndex[_particleCount - 1] = currentIndex;
                }
                --_particleCount;
                if( _particleCount == 0 && _isAutoRemoveOnFinish )
                {
                    this->unscheduleUpdate();
                    _parent->removeChild(this, true);
                    return;
                }
            }
        }
        
        if (_emitterMode == Mode::GRAVITY)
        {
            for (int i = 0 ; i < _particleCount; ++i)
            {
                particle_point tmp, radial = {0.0f, 0.0f}, tangential;
                
                // radial acceleration
                if (_particleData.posx[i] || _particleData.posy[i])
                {
                    normalize_point(_particleData.posx[i], _particleData.posy[i], &radial);
                }
                tangential = radial;
                radial.x *= _particleData.modeA.radialAccel[i];
                radial.y *= _particleData.modeA.radialAccel[i];
                
                // tangential acceleration
                std::swap(tangential.x, tangential.y);
                tangential.x *= - _particleData.modeA.tangentialAccel[i];
                tangential.y *= _particleData.modeA.tangentialAccel[i];
                
                // (gravity + radial + tangential) * dt
                tmp.x = radial.x + tangential.x + modeA.gravity.x;
                tmp.y = radial.y + tangential.y + modeA.gravity.y;
                tmp.x *= dt;
                tmp.y *= dt;
                
                _particleData.modeA.dirX[i] += tmp.x;
                _particleData.modeA.dirY[i] += tmp.y;
                
                // this is cocos2d-x v3.0
                // if (_configName.length()>0 && _yCoordFlipped != -1)
                
                // this is cocos2d-x v3.0
                tmp.x = _particleData.modeA.dirX[i] * dt * _yCoordFlipped;
                tmp.y = _particleData.modeA.dirY[i] * dt * _yCoordFlipped;
                _particleData.posx[i] += tmp.x;
                _particleData.posy[i] += tmp.y;
                
                _particleData.colorR[i] += _particleData.deltaColorR[i] * dt;
                _particleData.colorG[i] += _particleData.deltaColorG[i] * dt;
                _particleData.colorB[i] += _particleData.deltaColorB[i] * dt;
                _particleData.colorA[i] += _particleData.deltaColorA[i] * dt;
                _particleData.size[i] += (_particleData.deltaSize[i] * dt);
                _particleData.size[i] = MAX(0, _particleData.size[i]);
                _particleData.rotation[i] += _particleData.deltaRotation[i] * dt;
            }
        }
        else
        {
            for (int i = 0; i < _particleCount; ++i)
            {
                _particleData.modeB.angle[i] += _particleData.modeB.degreesPerSecond[i] * dt;
                _particleData.modeB.radius[i] += _particleData.modeB.deltaRadius[i] * dt;
                _particleData.posx[i] = - cosf(_particleData.modeB.angle[i]) * _particleData.modeB.radius[i];
                _particleData.posy[i] = - sinf(_particleData.modeB.angle[i]) * _particleData.modeB.radius[i] * _yCoordFlipped;

                _particleData.colorR[i] += _particleData.deltaColorR[i] * dt;
                _particleData.colorG[i] += _particleData.deltaColorG[i] * dt;
                _particleData.colorB[i] += _particleData.deltaColorB[i] * dt;
                _particleData.colorA[i] += _particleData.deltaColorA[i] * dt;
                _particleData.size[i] += (_particleData.deltaSize[i] * dt);
                _particleData.size[i] = MAX(0, _particleData.size[i]);
                _particleData.rotation[i] += _particleData.deltaRotation[i] * dt;
            }
        }
        
        updateParticleQuads();
        _transformSystemDirty = false;
    }

    // only update gl buffer when visible
    if (_visible && ! _batchNode)
    {
        postStep();
    }
}

void ParticleSystem::updateWithNoTime(void)
{
    this->update(0.0f);
}

void ParticleSystem::updateParticleQuads()
{
    //should be overridden
}

void ParticleSystem::postStep()
{
    // should be overridden
}

// ParticleSystem - Texture protocol
void ParticleSystem::setTexture(Texture2D* var)
{
    if (_texture != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(_texture);
        _texture = var;
        updateBlendFunc();
    }
}

void ParticleSystem::updateBlendFunc()
{
    CCASSERT(! _batchNode, "Can't change blending functions when the particle is being batched");

    if(_texture)
    {
        bool premultiplied = _texture->hasPremultipliedAlpha();
        
        _opacityModifyRGB = false;
        
        if( _texture && ( _blendFunc.src == CC_BLEND_SRC && _blendFunc.dst == CC_BLEND_DST ) )
        {
            if( premultiplied )
            {
                _opacityModifyRGB = true;
            }
            else
            {
                _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
            }
        }
    }
}

Texture2D * ParticleSystem::getTexture() const
{
    return _texture;
}

// ParticleSystem - Additive Blending
void ParticleSystem::setBlendAdditive(bool additive)
{
    if( additive )
    {
        _blendFunc = BlendFunc::ADDITIVE;
    }
    else
    {
        if( _texture && ! _texture->hasPremultipliedAlpha() )
            _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
        else 
            _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    }
}

bool ParticleSystem::isBlendAdditive() const
{
    return( _blendFunc.src == GL_SRC_ALPHA && _blendFunc.dst == GL_ONE);
}

// ParticleSystem - Properties of Gravity Mode 
void ParticleSystem::setTangentialAccel(float t)
{
    CCASSERT( _emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.tangentialAccel = t;
}

float ParticleSystem::getTangentialAccel() const
{
    CCASSERT( _emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.tangentialAccel;
}

void ParticleSystem::setTangentialAccelVar(float t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.tangentialAccelVar = t;
}

float ParticleSystem::getTangentialAccelVar() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.tangentialAccelVar;
}    

void ParticleSystem::setRadialAccel(float t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.radialAccel = t;
}

float ParticleSystem::getRadialAccel() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.radialAccel;
}

void ParticleSystem::setRadialAccelVar(float t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.radialAccelVar = t;
}

float ParticleSystem::getRadialAccelVar() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.radialAccelVar;
}

void ParticleSystem::setRotationIsDir(bool t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.rotationIsDir = t;
}

bool ParticleSystem::getRotationIsDir() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.rotationIsDir;
}

void ParticleSystem::setGravity(const Vec2& g)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.gravity = g;
}

const Vec2& ParticleSystem::getGravity()
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.gravity;
}

void ParticleSystem::setSpeed(float speed)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.speed = speed;
}

float ParticleSystem::getSpeed() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.speed;
}

void ParticleSystem::setSpeedVar(float speedVar)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.speedVar = speedVar;
}

float ParticleSystem::getSpeedVar() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.speedVar;
}

// ParticleSystem - Properties of Radius Mode
void ParticleSystem::setStartRadius(float startRadius)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.startRadius = startRadius;
}

float ParticleSystem::getStartRadius() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.startRadius;
}

void ParticleSystem::setStartRadiusVar(float startRadiusVar)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.startRadiusVar = startRadiusVar;
}

float ParticleSystem::getStartRadiusVar() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.startRadiusVar;
}

void ParticleSystem::setEndRadius(float endRadius)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.endRadius = endRadius;
}

float ParticleSystem::getEndRadius() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.endRadius;
}

void ParticleSystem::setEndRadiusVar(float endRadiusVar)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.endRadiusVar = endRadiusVar;
}

float ParticleSystem::getEndRadiusVar() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.endRadiusVar;
}

void ParticleSystem::setRotatePerSecond(float degrees)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.rotatePerSecond = degrees;
}

float ParticleSystem::getRotatePerSecond() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.rotatePerSecond;
}

void ParticleSystem::setRotatePerSecondVar(float degrees)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.rotatePerSecondVar = degrees;
}

float ParticleSystem::getRotatePerSecondVar() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.rotatePerSecondVar;
}

bool ParticleSystem::isActive() const
{
    return _isActive;
}

int ParticleSystem::getTotalParticles() const
{
    return _totalParticles;
}

void ParticleSystem::setTotalParticles(int var)
{
    CCASSERT( var <= _allocatedParticles, "Particle: resizing particle array only supported for quads");
    _totalParticles = var;
}

const BlendFunc& ParticleSystem::getBlendFunc() const
{
    return _blendFunc;
}

void ParticleSystem::setBlendFunc(const BlendFunc &blendFunc)
{
    if( _blendFunc.src != blendFunc.src || _blendFunc.dst != blendFunc.dst ) {
        _blendFunc = blendFunc;
        this->updateBlendFunc();
    }
}

bool ParticleSystem::isAutoRemoveOnFinish() const
{
    return _isAutoRemoveOnFinish;
}

void ParticleSystem::setAutoRemoveOnFinish(bool var)
{
    _isAutoRemoveOnFinish = var;
}


// ParticleSystem - methods for batchNode rendering

ParticleBatchNode* ParticleSystem::getBatchNode(void) const
{
    return _batchNode;
}

void ParticleSystem::setBatchNode(ParticleBatchNode* batchNode)
{
    if( _batchNode != batchNode ) {

        _batchNode = batchNode; // weak reference

        if( batchNode ) {
            //each particle needs a unique index
            for (int i = 0; i < _totalParticles; i++)
            {
                _particleData.atlasIndex[i] = i;
            }
        }
    }
}

//don't use a transform matrix, this is faster
void ParticleSystem::setScale(float s)
{
    _transformSystemDirty = true;
    Node::setScale(s);
}

void ParticleSystem::setRotation(float newRotation)
{
    _transformSystemDirty = true;
    Node::setRotation(newRotation);
}

void ParticleSystem::setScaleX(float newScaleX)
{
    _transformSystemDirty = true;
    Node::setScaleX(newScaleX);
}

void ParticleSystem::setScaleY(float newScaleY)
{
    _transformSystemDirty = true;
    Node::setScaleY(newScaleY);
}

void ParticleSystem::start()
{
    resetSystem();
}

void ParticleSystem::stop()
{
    stopSystem();
}

bool ParticleSystem::isPaused() const
{
    return _paused;
}

void ParticleSystem::pauseEmissions()
{
    _paused = true;
}

void ParticleSystem::resumeEmissions()
{
    _paused = false;
}



NS_CC_END
