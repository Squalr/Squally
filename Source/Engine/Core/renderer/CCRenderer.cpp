/****************************************************************************
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

#include "renderer/CCRenderer.h"

#include <algorithm>

#include "2d/CCCamera.h"
#include "2d/CCScene.h"
#include "base/CCConfiguration.h"
#include "base/CCConsole.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCBatchCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCRenderState.h"
#include "renderer/ccGLStateCache.h"

NS_CC_BEGIN

// queue
RenderQueue::RenderQueue()
{
    // ZAC: I'm arbitrarily setting the limits according to the needs of Squally
    // Apparently, only GLOBALZ_ZERO seems to be used.

    _commandMaximums[GLOBALZ_NEG] = 4;
    _commandMaximums[OPAQUE_3D] = 4;
    _commandMaximums[TRANSPARENT_3D] = 4;
    _commandMaximums[GLOBALZ_ZERO] = 65536;
    _commandMaximums[GLOBALZ_POS] = 4;
    
    _commands[GLOBALZ_NEG] = std::vector<RenderCommand*>(_commandMaximums[GLOBALZ_NEG]);
    _commands[OPAQUE_3D] = std::vector<RenderCommand*>(_commandMaximums[OPAQUE_3D]);
    _commands[TRANSPARENT_3D] = std::vector<RenderCommand*>(_commandMaximums[TRANSPARENT_3D]);
    _commands[GLOBALZ_ZERO] = std::vector<RenderCommand*>(_commandMaximums[GLOBALZ_ZERO]);
    _commands[GLOBALZ_POS] = std::vector<RenderCommand*>(_commandMaximums[GLOBALZ_POS]);

    for (int index = 0; index < QUEUE_COUNT; index++)
    {
        _commandCounts[index] = 0;
    }
}

void RenderQueue::push_back(RenderCommand* command)
{
    if (_commandCounts[QUEUE_GROUP::GLOBALZ_ZERO] < _commandMaximums[GLOBALZ_ZERO])
    {
        _commands[QUEUE_GROUP::GLOBALZ_ZERO][_commandCounts[QUEUE_GROUP::GLOBALZ_ZERO]++] = command;
    }
}

ssize_t RenderQueue::size() const
{
    ssize_t result(0);

    for(int index = 0; index < QUEUE_GROUP::QUEUE_COUNT; ++index)
    {
        result += _commandCounts[index];
    }
    
    return result;
}

void RenderQueue::sort()
{
    // Don't sort _queue0, it already comes sorted
    /*std::stable_sort(std::begin(_commands[QUEUE_GROUP::TRANSPARENT_3D]), std::end(_commands[QUEUE_GROUP::TRANSPARENT_3D]), compare3DCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_NEG]), std::end(_commands[QUEUE_GROUP::GLOBALZ_NEG]), compareRenderCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_POS]), std::end(_commands[QUEUE_GROUP::GLOBALZ_POS]), compareRenderCommand);*/
}

RenderCommand* RenderQueue::operator[](ssize_t index) const
{
    for(int queIndex = 0; queIndex < QUEUE_GROUP::QUEUE_COUNT; ++queIndex)
    {
        if(index < static_cast<ssize_t>(_commands[queIndex].size()))
        {
            return _commands[queIndex][index];
        }
        else
        {
            index -= _commandCounts[queIndex];
        }
    }
    
    CCASSERT(false, "invalid index");
    return nullptr;
}

void RenderQueue::clear()
{
    for(int i = 0; i < QUEUE_COUNT; ++i)
    {
        _commandCounts[i] = 0;
    }
}

void RenderQueue::realloc(size_t reserveSize)
{
    clear();
}

void RenderQueue::saveRenderState()
{
    _isDepthEnabled = glIsEnabled(GL_DEPTH_TEST) != GL_FALSE;
    _isCullEnabled = glIsEnabled(GL_CULL_FACE) != GL_FALSE;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &_isDepthWrite);
    
    CHECK_GL_ERROR_DEBUG();
}

void RenderQueue::restoreRenderState()
{
    if (_isCullEnabled)
    {
        glEnable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(true);
    }
    else
    {
        glDisable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(false);
    }

    if (_isDepthEnabled)
    {
        glEnable(GL_DEPTH_TEST);
        RenderState::StateBlock::_defaultState->setDepthTest(true);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        RenderState::StateBlock::_defaultState->setDepthTest(false);
    }
    
    glDepthMask(_isDepthWrite);
    RenderState::StateBlock::_defaultState->setDepthWrite(_isDepthEnabled);

    CHECK_GL_ERROR_DEBUG();
}

//
// constructors, destructor, init
//
Renderer::Renderer() : _filledVertex(0)
,_filledIndex(0)
,_glViewAssigned(false)
,_isRendering(false)
,_isDepthTestFor2D(false)
,_triBatchesToDraw(nullptr)
,_triBatchesToDrawCapacity(-1)
{
    _groupCommandManager = new (std::nothrow) GroupCommandManager();
    
    _renderQueue = RenderQueue();
    _queuedTriangleCommands.reserve(BATCH_TRIAGCOMMAND_RESERVED_SIZE);

    // default clear color
    _clearColor = Color4F::BLACK;

    // for the batched TriangleCommand
    _triBatchesToDrawCapacity = 500;
    _triBatchesToDraw = (TriBatchToDraw*) malloc(sizeof(_triBatchesToDraw[0]) * _triBatchesToDrawCapacity);
}

Renderer::~Renderer()
{
    _groupCommandManager->release();
    
    glDeleteBuffers(2, _buffersVBO);

    free(_triBatchesToDraw);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_buffersVAO);
        GL::bindVAO(0);
    }
}

void Renderer::initGLView()
{
    setupBuffer();
    
    _glViewAssigned = true;
}

void Renderer::setupBuffer()
{
    if(Configuration::getInstance()->supportsShareableVAO())
    {
        setupVBOAndVAO();
    }
    else
    {
        setupVBO();
    }
}

void Renderer::setupVBOAndVAO()
{
    //generate vbo and vao for trianglesCommand
    glGenVertexArrays(1, &_buffersVAO);
    GL::bindVAO(_buffersVAO);

    glGenBuffers(2, &_buffersVBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    // Issue #15652
    // Should not initialize VBO with a large size (VBO_SIZE=65536),
    // it may cause low FPS on some Android devices like LG G4 & Nexus 5X.
    // It's probably because some implementations of OpenGLES driver will
    // copy the whole memory of VBO which initialized at the first time
    // once glBufferData/glBufferSubData is invoked.
    // For more discussion, please refer to https://github.com/cocos2d/cocos2d-x/issues/15652
    //glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * VBO_SIZE, _verts, GL_DYNAMIC_DRAW);

    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, vertices));

    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, colors));

    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * INDEX_VBO_SIZE, _indices, GL_STATIC_DRAW);

    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

void Renderer::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);
    // Issue #15652
    // Should not initialize VBO with a large size (VBO_SIZE=65536),
    // it may cause low FPS on some Android devices like LG G4 & Nexus 5X.
    // It's probably because some implementations of OpenGLES driver will
    // copy the whole memory of VBO which initialized at the first time
    // once glBufferData/glBufferSubData is invoked.
    // For more discussion, please refer to https://github.com/cocos2d/cocos2d-x/issues/15652
//    mapBuffers();
}

void Renderer::mapBuffers()
{
    // Avoid changing the element buffer for whatever VAO might be bound.
    GL::bindVAO(0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * VBO_SIZE, _verts, GL_DYNAMIC_DRAW);
    

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * INDEX_VBO_SIZE, _indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

void Renderer::addCommand(RenderCommand* command)
{
    _renderQueue.push_back(command);
}

void Renderer::pushGroup(int renderQueueID)
{
}

void Renderer::popGroup()
{
}

int Renderer::createRenderQueue()
{
    return 0;
}

void Renderer::processRenderCommand(RenderCommand* command)
{
    auto commandType = command->getType();

    switch(commandType)
    {
        case RenderCommand::Type::TRIANGLES_COMMAND:
        {
            auto cmd = static_cast<TrianglesCommand*>(command);
            
            // flush own queue when buffer is full
            if(_filledVertex + cmd->getVertexCount() > VBO_SIZE || _filledIndex + cmd->getIndexCount() > INDEX_VBO_SIZE)
            {
                CCASSERT(cmd->getVertexCount()>= 0 && cmd->getVertexCount() < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
                CCASSERT(cmd->getIndexCount()>= 0 && cmd->getIndexCount() < INDEX_VBO_SIZE, "VBO for index is not big enough, please break the data down or use customized render command");
                drawBatchedTriangles();
            }
            
            // queue it
            _queuedTriangleCommands.push_back(cmd);
            _filledIndex += cmd->getIndexCount();
            _filledVertex += cmd->getVertexCount();
            break;
        }
        case RenderCommand::Type::GROUP_COMMAND:
        {
            flush();
            break;
        }
        case RenderCommand::Type::CUSTOM_COMMAND:
        {
            flush();
            auto cmd = static_cast<CustomCommand*>(command);
            CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_CUSTOM_COMMAND");
            cmd->execute();
            break;
        }
        case RenderCommand::Type::BATCH_COMMAND:
        {
            flush();
            auto cmd = static_cast<BatchCommand*>(command);
            CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_BATCH_COMMAND");
            cmd->execute();
            break;
        }
        default:
        {
            CCLOGERROR("Unknown commands in renderQueue");
            break;
        }
    }
}

void Renderer::visitRenderQueue(RenderQueue& queue)
{
    //
    //Process Global-Z = 0 Queue
    //
    const auto& zZeroQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_ZERO);
    auto queueSize = queue.getSubQueueSize(RenderQueue::QUEUE_GROUP::GLOBALZ_ZERO);
    
    if (queueSize > 0)
    {
        if(_isDepthTestFor2D)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthMask(true);
            glEnable(GL_BLEND);

            RenderState::StateBlock::_defaultState->setDepthTest(true);
            RenderState::StateBlock::_defaultState->setDepthWrite(true);
            RenderState::StateBlock::_defaultState->setBlend(true);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glDepthMask(false);
            glEnable(GL_BLEND);

            RenderState::StateBlock::_defaultState->setDepthTest(false);
            RenderState::StateBlock::_defaultState->setDepthWrite(false);
            RenderState::StateBlock::_defaultState->setBlend(true);
        }
        glDisable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(false);
        
        for (int index = 0; index < queueSize; index++)
        {
            processRenderCommand(zZeroQueue[index]);
        }

        flush();
    }
}

void Renderer::render()
{
    //Uncomment this once everything is rendered by new renderer
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _isRendering = true;
    
    if (_glViewAssigned)
    {
        visitRenderQueue(_renderQueue);
    }

    clean();
    _isRendering = false;
}

void Renderer::clean()
{
    // Clear batch commands
    _renderQueue.clear();
    _queuedTriangleCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
}

void Renderer::clear()
{
    //Enable Depth mask to make sure glClear clear the depth buffer correctly
    glDepthMask(true);
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(false);

    RenderState::StateBlock::_defaultState->setDepthWrite(false);
}

void Renderer::setDepthTest(bool enable)
{
    if (enable)
    {
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        RenderState::StateBlock::_defaultState->setDepthTest(true);
        RenderState::StateBlock::_defaultState->setDepthFunction(RenderState::DEPTH_LEQUAL);

//        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);

        RenderState::StateBlock::_defaultState->setDepthTest(false);
    }

    _isDepthTestFor2D = enable;
    CHECK_GL_ERROR_DEBUG();
}

void Renderer::fillVerticesAndIndices(const TrianglesCommand* cmd)
{
    memcpy(&_verts[_filledVertex], cmd->getVertices(), sizeof(V3F_C4B_T2F) * cmd->getVertexCount());

    // fill vertex, and convert them to world coordinates
    const Mat4& modelView = cmd->getModelView();
    for(ssize_t i=0; i < cmd->getVertexCount(); ++i)
    {
        modelView.transformPoint(&(_verts[i + _filledVertex].vertices));
    }

    // fill index
    const unsigned short* indices = cmd->getIndices();
    for(ssize_t i=0; i< cmd->getIndexCount(); ++i)
    {
        _indices[_filledIndex + i] = _filledVertex + indices[i];
    }

    _filledVertex += cmd->getVertexCount();
    _filledIndex += cmd->getIndexCount();
}

void Renderer::drawBatchedTriangles()
{
    if(_queuedTriangleCommands.empty())
        return;

    CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_BATCH_TRIANGLES");

    _filledVertex = 0;
    _filledIndex = 0;

    /************** 1: Setup up vertices/indices *************/

    _triBatchesToDraw[0].offset = 0;
    _triBatchesToDraw[0].indicesToDraw = 0;
    _triBatchesToDraw[0].cmd = nullptr;

    int batchesTotal = 0;
    int prevMaterialID = -1;
    bool firstCommand = true;

    for(const auto& cmd : _queuedTriangleCommands)
    {
        auto currentMaterialID = cmd->getMaterialID();
        const bool batchable = !cmd->isSkipBatching();

        fillVerticesAndIndices(cmd);

        // in the same batch ?
        if (batchable && (prevMaterialID == int(currentMaterialID) || firstCommand))
        {
            CC_ASSERT((firstCommand || _triBatchesToDraw[batchesTotal].cmd->getMaterialID() == cmd->getMaterialID()) && "argh... error in logic");
            _triBatchesToDraw[batchesTotal].indicesToDraw += cmd->getIndexCount();
            _triBatchesToDraw[batchesTotal].cmd = cmd;
        }
        else
        {
            // is this the first one?
            if (!firstCommand) {
                batchesTotal++;
                _triBatchesToDraw[batchesTotal].offset = _triBatchesToDraw[batchesTotal-1].offset + _triBatchesToDraw[batchesTotal-1].indicesToDraw;
            }

            _triBatchesToDraw[batchesTotal].cmd = cmd;
            _triBatchesToDraw[batchesTotal].indicesToDraw = (int) cmd->getIndexCount();

            // is this a single batch ? Prevent creating a batch group then
            if (!batchable)
                currentMaterialID = -1;
        }

        // capacity full ?
        if (batchesTotal + 1 >= _triBatchesToDrawCapacity) {
            _triBatchesToDrawCapacity *= 1.4;
            _triBatchesToDraw = (TriBatchToDraw*) realloc(_triBatchesToDraw, sizeof(_triBatchesToDraw[0]) * _triBatchesToDrawCapacity);
        }

        prevMaterialID = currentMaterialID;
        firstCommand = false;
    }
    batchesTotal++;

    /************** 2: Copy vertices/indices to GL objects *************/
    auto conf = Configuration::getInstance();
    if (conf->supportsShareableVAO() && conf->supportsMapBuffer())
    {
        //Bind VAO
        GL::bindVAO(_buffersVAO);
        //Set VBO data
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

        // option 1: subdata
//        glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );

        // option 2: data
//        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * _filledVertex, _verts, GL_STATIC_DRAW);

        // option 3: orphaning + glMapBuffer
        // FIXME: in order to work as fast as possible, it must "and the exact same size and usage hints it had before."
        //  source: https://www.opengl.org/wiki/Buffer_Object_Streaming#Explicit_multiple_buffering
        // so most probably we won't have any benefit of using it
        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * _filledVertex, nullptr, GL_STATIC_DRAW);

        void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		if (buf != nullptr)
		{
			memcpy(buf, _verts, sizeof(_verts[0]) * _filledVertex);
		}

        glUnmapBuffer(GL_ARRAY_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _filledIndex, _indices, GL_STATIC_DRAW);
    }
    else
    {
        // Client Side Arrays
        #define kQuadSize sizeof(_verts[0])
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * _filledVertex , _verts, GL_DYNAMIC_DRAW);

        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));

        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));

        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _filledIndex, _indices, GL_STATIC_DRAW);
    }

    /************** 3: Draw *************/
    for (int i=0; i<batchesTotal; ++i)
    {
        CC_ASSERT(_triBatchesToDraw[i].cmd && "Invalid batch");
        _triBatchesToDraw[i].cmd->useMaterial();
        glDrawElements(GL_TRIANGLES, (GLsizei) _triBatchesToDraw[i].indicesToDraw, GL_UNSIGNED_SHORT, (GLvoid*) (_triBatchesToDraw[i].offset*sizeof(_indices[0])) );
        _drawnBatches++;
        _drawnVertices += _triBatchesToDraw[i].indicesToDraw;
    }

    /************** 4: Cleanup *************/
    if (conf->supportsShareableVAO() && conf->supportsMapBuffer())
    {
        //Unbind VAO
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    _queuedTriangleCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
}

void Renderer::flush()
{
    drawBatchedTriangles();
}

// helpers
bool Renderer::checkVisibility(const Mat4 &transform, const CSize &size)
{
    auto director = Director::getInstance();
    auto scene = director->getRunningScene();
    
    //If draw to Rendertexture, return true directly.
    // only cull the default camera. The culling algorithm is valid for default camera.
    if (!scene || (scene && scene->_defaultCamera != Camera::getVisitingCamera()))
        return true;

    CRect visibleRect(director->getVisibleOrigin(), director->getVisibleSize());
    
    // transform center point to screen space
    float hSizeX = size.width/2;
    float hSizeY = size.height/2;
    Vec3 v3p(hSizeX, hSizeY, 0);
    transform.transformPoint(&v3p);
    Vec2 v2p = Camera::getVisitingCamera()->projectGL(v3p);

    // convert content size to world coordinates
    float wshw = std::max(fabsf(hSizeX * transform.m[0] + hSizeY * transform.m[4]), fabsf(hSizeX * transform.m[0] - hSizeY * transform.m[4]));
    float wshh = std::max(fabsf(hSizeX * transform.m[1] + hSizeY * transform.m[5]), fabsf(hSizeX * transform.m[1] - hSizeY * transform.m[5]));

    // ZAC: The culling for sprites is too zealous when the sprite is close to the camera -- this is an "elegant hack" to solve that
    const float buffer = v3p.z > 0.0f ? v3p.z * 2.0f : 0.0f;
    
    // enlarge visible rect half size in screen coord
    visibleRect.origin.x -= wshw + buffer;
    visibleRect.origin.y -= wshh + buffer;
    visibleRect.size.width += (wshw + buffer) * 2;
    visibleRect.size.height += (wshh + buffer) * 2;
    bool ret = visibleRect.containsPoint(v2p);
    return ret;
}


void Renderer::setClearColor(const Color4F &clearColor)
{
    _clearColor = clearColor;
}

NS_CC_END
