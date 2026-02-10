/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "platform/CCGLView.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "2d/CCCamera.h"
#include "2d/CCScene.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

//default context attributions are set as follows
GLContextAttrs GLView::_glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

void GLView::setGLContextAttrs(GLContextAttrs& glContextAttrs)
{
    _glContextAttrs = glContextAttrs;
}

GLContextAttrs GLView::getGLContextAttrs()
{
    return _glContextAttrs;
}

GLView::GLView()
: _scaleX(1.0f)
, _scaleY(1.0f)
, _resolutionPolicy(ResolutionPolicy::UNKNOWN)
, _designResolutionSize(0,0)
, _screenSize(0,0)
{
}

GLView::~GLView()
{

}

void GLView::pollEvents()
{
}

void GLView::updateDesignResolutionSize()
{
    if (_screenSize.width > 0 && _screenSize.height > 0
        && _designResolutionSize.width > 0 && _designResolutionSize.height > 0)
    {
        _scaleX = (float)_screenSize.width / _designResolutionSize.width;
        _scaleY = (float)_screenSize.height / _designResolutionSize.height;
        
        if (_resolutionPolicy == ResolutionPolicy::NO_BORDER)
        {
            _scaleX = _scaleY = MAX(_scaleX, _scaleY);
        }
        
        else if (_resolutionPolicy == ResolutionPolicy::SHOW_ALL)
        {
            _scaleX = _scaleY = MIN(_scaleX, _scaleY);
        }
        
        else if ( _resolutionPolicy == ResolutionPolicy::FIXED_HEIGHT) {
            _scaleX = _scaleY;
            _designResolutionSize.width = ceilf(_screenSize.width/_scaleX);
        }
        
        else if ( _resolutionPolicy == ResolutionPolicy::FIXED_WIDTH) {
            _scaleY = _scaleX;
            _designResolutionSize.height = ceilf(_screenSize.height/_scaleY);
        }
        
        // calculate the rect of viewport
        float viewPortW = _designResolutionSize.width * _scaleX;
        float viewPortH = _designResolutionSize.height * _scaleY;
        
        _viewPortRect.setRect((_screenSize.width - viewPortW) / 2, (_screenSize.height - viewPortH) / 2, viewPortW, viewPortH);


        // reset director's member variables to fit visible rect
        auto director = Director::getInstance();
        director->_winSizeInPoints = getDesignResolutionSize();
        director->_isStatusLabelUpdated = true;
        director->setProjection(director->getProjection());

        // Github issue #16139
        // A default viewport is needed in order to display the FPS,
        // since the FPS are rendered in the Director, and there is no viewport there.
        // Everything, including the FPS should renderer in the Scene.
        glViewport(0, 0, _screenSize.width, _screenSize.height);
    }
}

void GLView::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    CCASSERT(resolutionPolicy != ResolutionPolicy::UNKNOWN, "should set resolutionPolicy");
    
    if (width == 0.0f || height == 0.0f)
    {
        return;
    }

    _designResolutionSize.setSize(width, height);
    _resolutionPolicy = resolutionPolicy;
    
    updateDesignResolutionSize();
 }

const CSize& GLView::getDesignResolutionSize() const 
{
    return _designResolutionSize;
}

CSize GLView::getFrameSize() const
{
    return _screenSize;
}

void GLView::setFrameSize(float width, float height)
{
    _screenSize = CSize(width, height);

    // Github issue #16003 and #16485
    // only update the designResolution if it wasn't previously set
    if (_designResolutionSize.equals(CSize::ZERO))
        _designResolutionSize = _screenSize;
}

CRect GLView::getVisibleRect() const
{
    CRect ret;
    ret.size = getVisibleSize();
    ret.origin = getVisibleOrigin();
    return ret;
}

CRect GLView::getSafeAreaRect() const
{
    return getVisibleRect();
}

CSize GLView::getVisibleSize() const
{
    if (_resolutionPolicy == ResolutionPolicy::NO_BORDER)
    {
        return CSize(_screenSize.width/_scaleX, _screenSize.height/_scaleY);
    }
    else 
    {
        return _designResolutionSize;
    }
}

Vec2 GLView::getVisibleOrigin() const
{
    if (_resolutionPolicy == ResolutionPolicy::NO_BORDER)
    {
        return Vec2((_designResolutionSize.width - _screenSize.width/_scaleX)/2, 
                           (_designResolutionSize.height - _screenSize.height/_scaleY)/2);
    }
    else 
    {
        return Vec2::ZERO;
    }
}

void GLView::setViewPortInPoints(float x , float y , float w , float h)
{
    cocos_experimental::Viewport vp((float)(x * _scaleX + _viewPortRect.origin.x),
        (float)(y * _scaleY + _viewPortRect.origin.y),
        (float)(w * _scaleX),
        (float)(h * _scaleY));
    Camera::setDefaultViewport(vp);
}

void GLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX + _viewPortRect.origin.x),
              (GLint)(y * _scaleY + _viewPortRect.origin.y),
              (GLsizei)(w * _scaleX),
              (GLsizei)(h * _scaleY));
}

bool GLView::isScissorEnabled()
{
    return (GL_FALSE == glIsEnabled(GL_SCISSOR_TEST)) ? false : true;
}

CRect GLView::getScissorRect() const
{
    GLfloat params[4];
    glGetFloatv(GL_SCISSOR_BOX, params);
    float x = (params[0] - _viewPortRect.origin.x) / _scaleX;
    float y = (params[1] - _viewPortRect.origin.y) / _scaleY;
    float w = params[2] / _scaleX;
    float h = params[3] / _scaleY;
    return CRect(x, y, w, h);
}

void GLView::setViewName(const std::string& viewname )
{
    _viewName = viewname;
}

const std::string& GLView::getViewName() const
{
    return _viewName;
}

const CRect& GLView::getViewPortRect() const
{
    return _viewPortRect;
}

float GLView::getScaleX() const
{
    return _scaleX;
}

float GLView::getScaleY() const
{
    return _scaleY;
}

void GLView::renderScene(Scene* scene, Renderer* renderer)
{
    CCASSERT(scene, "Invalid Scene");
    CCASSERT(renderer, "Invalid Renderer");

    scene->render(renderer, Mat4::IDENTITY, nullptr);
}

NS_CC_END
