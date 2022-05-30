#include "GraphicsBufferManager.h"

GraphicsBufferManager::~GraphicsBufferManager()
{
	clear();
}

void GraphicsBufferManager::addGraphicsBuffer(const std::string& key, GraphicsBuffer* graphicsBuffer)
{
	mGraphicsBuffers[key] = graphicsBuffer;
}

void GraphicsBufferManager::removeGraphicsBuffer(const std::string& key)
{
	delete mGraphicsBuffers[key];
	mGraphicsBuffers.erase(key);
}

void GraphicsBufferManager::clear()
{
	for (auto it : mGraphicsBuffers) {
		delete it.second;
	}
	mGraphicsBuffers.clear();
}
