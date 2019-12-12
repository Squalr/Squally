#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ErrorPool : public MinMaxPool
{
public:
	static ErrorPool* create();

	static const std::string PoolName;

protected:
	ErrorPool();
	virtual ~ErrorPool();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
