#pragma once
#include "Engine/GlobalNode.h"

class MapLoader : public GlobalNode
{
public:
    virtual ~MapLoader() = default;

private:
    typedef GlobalNode super;
};
