#include "LiquidTop.h"

#if __GNUC__ || __clang__
    // #include <execution>
#else
    #include <execution>
#endif

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCConsole.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCCustomCommand.h"
#include "cocos/renderer/CCGLProgramCache.h"
#include "cocos/renderer/ccGLStateCache.h"
#include "cocos/renderer/CCRenderer.h"

#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const int LiquidTop::ColumnsPer128px = 8;

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
    this->columnIndicies = std::vector<int>();
    this->colorArray = std::vector<cocos2d::Color4B>();
    this->customDrawCommand = new CustomCommand();
    this->tension = tension;
    this->dampening = dampening;
    this->spread = spread;
    this->columnCount = int((this->surfaceSize.width / 128.0f) * float(LiquidTop::ColumnsPer128px));
    this->lastIndex = std::max(0, columnCount - 1);

    for (int index = 0; index < columnCount; index++)
    {
        ColumnData column = ColumnData(this->surfaceSize.height, this->surfaceSize.height, 0);
        const uint16_t x = uint16_t((float(index) / float(this->lastIndex)) * this->surfaceSize.width);

        this->colorArray.push_back(surfaceColor);
        this->colorArray.push_back(bodyColor);
        this->vertexArray.push_back(Vertex(x, uint16_t(this->surfaceSize.height)));
        this->vertexArray.push_back(Vertex(x, 0));
        this->leftDeltas.push_back(0.0f);
        this->rightDeltas.push_back(0.0f);
        this->columns.push_back(column);
        this->columnIndicies.push_back(index);
    }
}

LiquidTop::~LiquidTop()
{
    delete(this->customDrawCommand);
}

void LiquidTop::onEnter()
{
    super::onEnter();

    this->scheduleUpdate();
}

void LiquidTop::update(float dt)
{
    super::update(dt);

    if (this->lastIndex < 2)
    {
        return;
    }

    ColumnData* column = &columns[1];

    // First iteration is done out-of-loop
    const float deltaHeight = column->targetHeight - column->height;
    column->speed += this->tension * deltaHeight - column->speed * this->dampening;
    column->height += column->speed;

    ColumnData* prevPrevColumn = &columns[0];
    ColumnData* prevColumn = column;

    // See git history for unoptimized version
    for (int index = 2; index < this->lastIndex; index++)
    {
        column = &columns[index];

        const float deltaHeight = column->targetHeight - column->height;
        column->speed += this->tension * deltaHeight - column->speed * this->dampening;
        column->height += column->speed;

        const float delta = this->spread * (column->height - prevColumn->height) + 
            this->spread * (prevPrevColumn->height - prevColumn->height);
        prevColumn->speed += delta;
        prevColumn->height += delta;

        this->vertexArray[2 * index].y = uint16_t(column->height);

        prevPrevColumn = prevColumn;
        prevColumn = column;
    }
}

void LiquidTop::splash(float x, float speed, float splashRadius, float decay)
{
    int centralIndex = int((x / this->surfaceSize.width) * float(this->columns.size()));
    int minIndex = int(((x - splashRadius) / this->surfaceSize.width) * float(this->columns.size()));
    int maxIndex = int(((x + splashRadius) / this->surfaceSize.width) * float(this->columns.size()));

    centralIndex = MathUtils::clamp(centralIndex, 0, this->lastIndex);
    minIndex = MathUtils::clamp(minIndex, 0, this->lastIndex);
    maxIndex = MathUtils::clamp(maxIndex, 0, this->lastIndex);

    for (int index = minIndex; index <= maxIndex; index++)
    {
        int distance = std::abs(centralIndex - index);

        columns[index].speed = speed - decay * float(distance);
    }
}

void LiquidTop::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    this->customDrawCommand->init(0);
    this->customDrawCommand->func = CC_CALLBACK_0(LiquidTop::onCustomDraw, this, transform);

    renderer->addCommand(customDrawCommand);
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
