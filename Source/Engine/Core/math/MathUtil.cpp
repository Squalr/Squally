/**
Copyright 2013 BlackBerry Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 
Original file from GamePlay3D: http://gameplay3d.org

This file was modified to fit the cocos2d-x project
*/

#include "math/MathUtil.h"
#include "base/ccMacros.h"

//#define USE_SSE           : SSE code used
//#define INCLUDE_SSE       : SSE code included

#if defined (__SSE__)
#define USE_SSE
#define INCLUDE_SSE
#endif

#ifdef INCLUDE_SSE
#include "math/MathUtilSSE.inl"
#endif

#include "math/MathUtil.inl"

NS_CC_MATH_BEGIN

void MathUtil::smooth(float* x, float target, float elapsedTime, float responseTime)
{
    GP_ASSERT(x);
    
    if (elapsedTime > 0)
    {
        *x += (target - *x) * elapsedTime / (elapsedTime + responseTime);
    }
}

void MathUtil::smooth(float* x, float target, float elapsedTime, float riseTime, float fallTime)
{
    GP_ASSERT(x);
    
    if (elapsedTime > 0)
    {
        float delta = target - *x;
        *x += delta * elapsedTime / (elapsedTime + (delta > 0 ? riseTime : fallTime));
    }
}

float MathUtil::lerp(float from, float to, float alpha)
{
    return from * (1.0f - alpha) + to * alpha;
}

void MathUtil::addMatrix(const float* m, float scalar, float* dst)
{
    MathUtilC::addMatrix(m, scalar, dst);
}

void MathUtil::addMatrix(const float* m1, const float* m2, float* dst)
{
    MathUtilC::addMatrix(m1, m2, dst);
}

void MathUtil::subtractMatrix(const float* m1, const float* m2, float* dst)
{
    MathUtilC::subtractMatrix(m1, m2, dst);
}

void MathUtil::multiplyMatrix(const float* m, float scalar, float* dst)
{
    MathUtilC::multiplyMatrix(m, scalar, dst);
}

void MathUtil::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
    MathUtilC::multiplyMatrix(m1, m2, dst);
}

void MathUtil::negateMatrix(const float* m, float* dst)
{
    MathUtilC::negateMatrix(m, dst);
}

void MathUtil::transposeMatrix(const float* m, float* dst)
{
    MathUtilC::transposeMatrix(m, dst);
}

void MathUtil::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
    MathUtilC::transformVec4(m, x, y, z, w, dst);
}

void MathUtil::transformVec4(const float* m, const float* v, float* dst)
{
    MathUtilC::transformVec4(m, v, dst);
}

void MathUtil::crossVec3(const float* v1, const float* v2, float* dst)
{
    MathUtilC::crossVec3(v1, v2, dst);
}

NS_CC_MATH_END
