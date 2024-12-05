#include "PoolObject.h"

PoolObject::PoolObject() : inUse(false) {}

bool PoolObject::isInUse() { return inUse; }

void PoolObject::setInUse(bool inUse) { this->inUse = inUse; }

PoolObject::~PoolObject() {}
