#pragma once

class PoolObject
{
private:
	bool inUse;
public:
	PoolObject();

	bool isInUse();
	void setInUse(bool inUse);

	~PoolObject();
};