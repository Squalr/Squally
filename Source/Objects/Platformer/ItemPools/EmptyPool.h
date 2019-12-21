#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class EmptyPool : public MinMaxPool
{
public:
	static EmptyPool* create();

	static const std::string PoolName;

protected:
	EmptyPool();
	virtual ~EmptyPool();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
