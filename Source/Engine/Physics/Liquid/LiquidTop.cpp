#include "LiquidTop.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCCustomCommand.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/ccGLStateCache.h"
#include "cocos/renderer/CCRenderer.h"

#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const int LiquidTop::ColumnsPer128px = 16;

LiquidTop* LiquidTop::create(Size surfaceSize, Color4B surfaceColor, Color4B bodyColor, float tension, float dampening, float spread)
{
    LiquidTop* instance = new LiquidTop(surfaceSize, surfaceColor, bodyColor, tension, dampening, spread);

    instance->autorelease();

    return instance;
}

LiquidTop::LiquidTop(Size surfaceSize, Color4B surfaceColor, Color4B bodyColor, float tension, float dampening, float spread)
{
    this->surfaceSize = surfaceSize;
    this->vertexArray = std::vector<Vertex>();
    this->leftDeltas = std::vector<float>();
    this->rightDeltas = std::vector<float>();
    this->columns = std::vector<ColumnData>();
    this->colorArray = std::vector<cocos2d::Color4B>();
    this->customCommand = new CustomCommand();
    this->tension = tension;
    this->dampening = dampening;
    this->spread = spread;

    int columnCount = int((this->surfaceSize.width / 128.0f) * float(LiquidTop::ColumnsPer128px));

    for (int index = 0; index < columnCount; index++)
    {
        ColumnData column = ColumnData(this->surfaceSize.height, this->surfaceSize.height, 0);

        this->colorArray.push_back(surfaceColor);
        this->colorArray.push_back(bodyColor);
        this->vertexArray.push_back(Vertex());
        this->vertexArray.push_back(Vertex());
        this->leftDeltas.push_back(0.0f);
        this->rightDeltas.push_back(0.0f);
        this->columns.push_back(column);
    }
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
        (*it).update(this->dampening, this->tension);
    }

    const int SpreadIterations = 8;

    for (int iteration = 0; iteration < SpreadIterations; iteration++)
    {
        // Ignore the first and last columns as an optimization. No apparent visual impact, much cleaner code.
        for (int index = 1; index < int(this->columns.size()) - 1; index++)
        {
            leftDeltas[index] = this->spread * (columns[index].height - columns[index - 1].height);
            rightDeltas[index] = this->spread * (columns[index].height - columns[index + 1].height);
            columns[index - 1].speed += leftDeltas[index];
            columns[index + 1].speed += rightDeltas[index];
        }

        for (int index = 1; index < int(this->columns.size()) - 1; index++)
        {
            columns[index - 1].height += leftDeltas[index];
            columns[index + 1].height += rightDeltas[index];
        }
    }

    for (int index = 0; index < int(this->columns.size()); index++)
    {
        uint16_t x = uint16_t((float(index) / float(this->columns.size() - 1)) * this->surfaceSize.width);
        uint16_t y = uint16_t(columns[index].height);
        
        this->vertexArray[2 * index] = Vertex(x, y);
        this->vertexArray[2 * index + 1] = Vertex(x, 0);
    }
}

void LiquidTop::splash(float x, float speed)
{
    int index = int((x / this->surfaceSize.width) * float(this->columns.size()));

    index = MathUtils::clamp(index, 0, this->columns.size() - 1);

    columns[index].speed = speed;
}

void LiquidTop::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    this->customCommand->init(_globalZOrder);
    this->customCommand->func = CC_CALLBACK_0(LiquidTop::onCustomDraw, this, transform);

    renderer->addCommand(customCommand);
}

void LiquidTop::onCustomDraw(const Mat4 &transform)
{
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    CHECK_GL_ERROR_DEBUG();
    
    this->getGLProgram()->use();
    this->getGLProgram()->setUniformsForBuiltins();
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    
    // glEnableVertexAttribArray(GL::VERTEX_ATTRIB_FLAG_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, this->vertexArray.data());
    // glEnableVertexAttribArray(GL::VERTEX_ATTRIB_FLAG_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, this->colorArray.data());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, this->columns.size() * 2);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, this->columns.size() * 2);
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
