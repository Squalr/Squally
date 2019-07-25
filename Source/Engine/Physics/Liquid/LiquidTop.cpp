#include "LiquidTop.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCCustomCommand.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/ccGLStateCache.h"
#include "cocos/renderer/CCRenderer.h"

#include "Engine/Physics/Liquid/LiquidColumn.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

LiquidTop* LiquidTop::create(Size surfaceSize)
{
    LiquidTop* instance = new LiquidTop(surfaceSize);

    instance->autorelease();

    return instance;
}

LiquidTop::LiquidTop(Size surfaceSize)
{
    this->surfaceSize = surfaceSize;
    this->customCommand = new CustomCommand();

    for (int index = 1; index < kColumnCount * 2; index += 2)
    {
        this->colorArray[index - 1] = topColor;
        this->colorArray[index] = bottomColor;
    }

    this->columns = std::vector<LiquidColumn*>();

    for (int index = 0; index < kColumnCount; index++)
    {
        LiquidColumn* column = LiquidColumn::create();

        column->initWithTargetHeight(this->surfaceSize.height, this->surfaceSize.height, 0);

        this->columns.push_back(column);
    }
    
    // this node will have the SHADER_NAME_POSITION_COLOR shader
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
}

LiquidTop::~LiquidTop()
{
    delete(this->customCommand);
}

void LiquidTop::onEnter()
{
    super::onEnter();

    this->scheduleUpdate();
}

void LiquidTop::update(float dt)
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
                (columns[i - 1])->speed += leftDeltas[i];
            }
            if (i < kColumnCount - 1)
            {
                rightDeltas[i] = kSpread * (columns[i]->height - columns[i+1]->height);
                (columns[i + 1])->speed += rightDeltas[i];
            }
        }

        for (int i = 0; i < kColumnCount; i++)
        {
            if (i > 0)
            {
                (columns[i - 1])->height += leftDeltas[i];
            }
            if (i < kColumnCount - 1)
            {
                (columns[i + 1])->height += rightDeltas[i];
            }
        }
    }
}

void LiquidTop::splash(float x, float speed)
{
    int index = int(x / this->surfaceSize.width);

    if (index >= 0 && index < kColumnCount)
    {
        columns[index]->speed = speed;
    }
}

void LiquidTop::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    this->customCommand->init(_globalZOrder);
    this->customCommand->func = CC_CALLBACK_0(LiquidTop::onCustomDraw, this, transform);

    renderer->addCommand(customCommand);
}

void LiquidTop::onCustomDraw(const Mat4 &transform)
{
    // update the matrix
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    for (int index = 0; index < kColumnCount; index++)
    {
        uint16_t x = (float(index) / float(kColumnCount - 1)) * this->surfaceSize.width;
        uint16_t y = columns[index]->height;
        
        vertexArray[2 * index] = Vertex(x, y);
        vertexArray[2 * index + 1] = Vertex(x, 0);
    }
    
    // now finally call the low-level opengGL calls to render the GL_TRIANGLE_STRIP in a simple way
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    this->getGLProgram()->use();
    this->getGLProgram()->setUniformsForBuiltins();

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, vertexArray);
    glEnableVertexAttribArray(GL::VERTEX_ATTRIB_FLAG_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, this->colorArray);
    glEnableVertexAttribArray(GL::VERTEX_ATTRIB_FLAG_COLOR);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, kColumnCount * 2);
}
