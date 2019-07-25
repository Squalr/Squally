#include "LiquidColumn.h"
#include "LiquidNode.h"

#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/CCGLProgramState.h"
#include "cocos/renderer/CCGLProgramStateCache.h"
#include "cocos/renderer/CCGLProgram.h"
#include "cocos/renderer/CCTextureCache.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/ccGLStateCache.h"
#include "cocos/renderer/CCRenderer.h"
#include "cocos/renderer/CCVertexIndexBuffer.h"

using namespace cocos2d;

LiquidNode* LiquidNode::create(Size liquidSize)
{
    LiquidNode* instance = new LiquidNode(liquidSize);

    instance->autorelease();

    return instance;
}

LiquidNode::LiquidNode(Size liquidSize)
{
    this->liquidSize = liquidSize;

    // init the vertex colors, with two different colors
    for (int index = 1; index < kColumnCount * 2; index += 2)
    {
        colorArray[index - 1].color = topColor;
        colorArray[index].color = bottomColor;
    }

    this->columns = std::vector<LiquidColumn*>();

    for (int index = 0; index < kColumnCount; index++)
    {
        LiquidColumn* column = LiquidColumn::create();

        column->initWithTargetHeight(this->liquidSize.height, this->liquidSize.height, 0);

        this->columns.push_back(column);
    }
    
    // this node will have the SHADER_NAME_POSITION_COLOR shader
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
}

LiquidNode::~LiquidNode()
{
}

void LiquidNode::onEnter()
{
    super::onEnter();

    this->scheduleUpdate();
}

void LiquidNode::update(float dt)
{
    super::update(dt);

    for (auto it = this->columns.begin(); it != this->columns.end(); it++)
    {
        (*it)->update(kDampening, kTension);
    }

    float leftDeltas[kColumnCount];
    float rightDeltas[kColumnCount];

    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < kColumnCount; i++)
        {
            if (i > 0)
            {
                leftDeltas[i] = kSpread * (columns[i]->height - columns[i-1]->height);
                ((LiquidColumn *) columns[i - 1])->speed += leftDeltas[i];
            }
            if (i < kColumnCount - 1)
            {
                rightDeltas[i] = kSpread * (columns[i]->height - columns[i+1]->height);
                ((LiquidColumn *) columns[i + 1])->speed += rightDeltas[i];
            }
        }

        for (int i = 0; i < kColumnCount; i++)
        {
            if (i > 0)
            {
                ((LiquidColumn *)columns[i - 1])->height += leftDeltas[i];
            }
            if (i < kColumnCount - 1)
            {
                ((LiquidColumn *)columns[i + 1])->height += rightDeltas[i];
            }
        }
    }
}

void LiquidNode::onCustomDraw(const Mat4 &transform)
{
    // update the matrix
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    for (int index = 0; index < kColumnCount; index++)
    {
        uint16_t x = (float(index) / float(kColumnCount)) * this->liquidSize.width;
        uint16_t y = columns[index]->height;
        
        vertexArray[2 * index] = (struct Vertex) {x, y};
        vertexArray[2 * index + 1] = (struct Vertex) {x, 0};
    }
    
    // now finally call the low-level opengGL calls to render the GL_TRIANGLE_STRIP in a simple way
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    this->getGLProgram()->use();
    this->getGLProgram()->setUniformsForBuiltins();

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, vertexArray);
    glEnableVertexAttribArray(GL::VERTEX_ATTRIB_FLAG_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colorArray);
    glEnableVertexAttribArray(GL::VERTEX_ATTRIB_FLAG_COLOR);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, kColumnCount * 2);
}

void LiquidNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    customCommand.init(_globalZOrder);
    customCommand.func = CC_CALLBACK_0(LiquidNode::onCustomDraw, this, transform);
    renderer->addCommand(&customCommand);
}

void LiquidNode::splash(float x, float speed)
{
    // called when we want to simulate a splash in the water with speed value (usually negative, but works with positive too)
    int index = int(x / this->liquidSize.width);

    if (index >= 0 && index < kColumnCount)
    {
        LiquidColumn* waterColumn = columns[index];
        waterColumn->speed = speed;
    }
}
