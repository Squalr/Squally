#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"

using namespace cocos2d;

class Background : public SerializableLayer
{
public:
	static Background* create(ValueMap* initProperties, std::string name, Node* child);

private:
	Background(ValueMap* properties, std::string name, Node* child);
	~Background();

	void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
};

