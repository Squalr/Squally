/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies
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

#include "math/CCGeometry.h"

#include <algorithm>
#include <cmath>
#include "base/ccMacros.h"

// implementation of Vec2
NS_CC_BEGIN

// implementation of CSize

CSize::CSize(void) : width(0), height(0)
{
}

CSize::CSize(float w, float h) : width(w), height(h)
{
}

CSize::CSize(const CSize& other) : width(other.width), height(other.height)
{
}

CSize::CSize(const Vec2& point) : width(point.x), height(point.y)
{
}

CSize& CSize::operator= (const CSize& other)
{
    setSize(other.width, other.height);
    return *this;
}

CSize& CSize::operator= (const Vec2& point)
{
    setSize(point.x, point.y);
    return *this;
}

CSize CSize::operator+(const CSize& right) const
{
    return CSize(this->width + right.width, this->height + right.height);
}

CSize CSize::operator-(const CSize& right) const
{
    return CSize(this->width - right.width, this->height - right.height);
}

CSize CSize::operator*(float a) const
{
    return CSize(this->width * a, this->height * a);
}

CSize CSize::operator/(float a) const
{
	CCASSERT(a!=0, "CCSize division by 0.");
    return CSize(this->width / a, this->height / a);
}

void CSize::setSize(float w, float h)
{
    this->width = w;
    this->height = h;
}

bool CSize::equals(const CSize& target) const
{
    return (std::abs(this->width  - target.width)  < FLT_EPSILON)
        && (std::abs(this->height - target.height) < FLT_EPSILON);
}

const CSize CSize::ZERO = CSize(0, 0);

// implementation of CRect

CRect::CRect(void)
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

CRect::CRect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}
CRect::CRect(const Vec2& pos, const CSize& dimension)
{
    setRect(pos.x, pos.y, dimension.width, dimension.height);
}

CRect::CRect(const CRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

CRect& CRect::operator= (const CRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void CRect::setRect(float x, float y, float width, float height)
{
    // CGRect can support width<0 or height<0
    // CCASSERT(width >= 0.0f && height >= 0.0f, "width and height of CRect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool CRect::equals(const CRect& rect) const
{
    return (origin.equals(rect.origin) && 
            size.equals(rect.size));
}

float CRect::getMaxX() const
{
    return origin.x + size.width;
}

float CRect::getMidX() const
{
    return origin.x + size.width / 2.0f;
}

float CRect::getMinX() const
{
    return origin.x;
}

float CRect::getMaxY() const
{
    return origin.y + size.height;
}

float CRect::getMidY() const
{
    return origin.y + size.height / 2.0f;
}

float CRect::getMinY() const
{
    return origin.y;
}

bool CRect::containsPoint(const Vec2& point) const
{
    bool bRet = false;

    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }

    return bRet;
}

bool CRect::intersectsRect(const CRect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
                  getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

bool CRect::intersectsCircle(const Vec2& center, float radius) const
{
    Vec2 rectangleCenter((origin.x + size.width / 2),
                         (origin.y + size.height / 2));
    
    float w = size.width / 2;
    float h = size.height / 2;
    
    float dx = std::abs(center.x - rectangleCenter.x);
    float dy = std::abs(center.y - rectangleCenter.y);
    
    if (dx > (radius + w) || dy > (radius + h))
    {
        return false;
    }
    
    Vec2 circleDistance(std::abs(center.x - origin.x - w),
                        std::abs(center.y - origin.y - h));
    
    if (circleDistance.x <= (w))
    {
        return true;
    }
    
    if (circleDistance.y <= (h))
    {
        return true;
    }
    
    float cornerDistanceSq = powf(circleDistance.x - w, 2) + powf(circleDistance.y - h, 2);
    
    return (cornerDistanceSq <= (powf(radius, 2)));
}

void CRect::merge(const CRect& rect)
{
    float minX = std::min(getMinX(), rect.getMinX());
    float minY = std::min(getMinY(), rect.getMinY());
    float maxX = std::max(getMaxX(), rect.getMaxX());
    float maxY = std::max(getMaxY(), rect.getMaxY());
    setRect(minX, minY, maxX - minX, maxY - minY);
}

CRect CRect::unionWithRect(const CRect & rect) const
{
    float thisLeftX = origin.x;
    float thisRightX = origin.x + size.width;
    float thisTopY = origin.y + size.height;
    float thisBottomY = origin.y;
    
    if (thisRightX < thisLeftX)
    {
        std::swap(thisRightX, thisLeftX);   // This rect has negative width
    }
    
    if (thisTopY < thisBottomY)
    {
        std::swap(thisTopY, thisBottomY);   // This rect has negative height
    }
    
    float otherLeftX = rect.origin.x;
    float otherRightX = rect.origin.x + rect.size.width;
    float otherTopY = rect.origin.y + rect.size.height;
    float otherBottomY = rect.origin.y;
    
    if (otherRightX < otherLeftX)
    {
        std::swap(otherRightX, otherLeftX);   // Other rect has negative width
    }
    
    if (otherTopY < otherBottomY)
    {
        std::swap(otherTopY, otherBottomY);   // Other rect has negative height
    }
    
    float combinedLeftX = std::min(thisLeftX, otherLeftX);
    float combinedRightX = std::max(thisRightX, otherRightX);
    float combinedTopY = std::max(thisTopY, otherTopY);
    float combinedBottomY = std::min(thisBottomY, otherBottomY);
    
    return CRect(combinedLeftX, combinedBottomY, combinedRightX - combinedLeftX, combinedTopY - combinedBottomY);
}

const CRect CRect::ZERO = CRect(0, 0, 0, 0);

NS_CC_END
