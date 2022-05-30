#pragma once
#include <Trackable.h>
#include <unordered_map>
#include <GraphicsBuffer.h>

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager() {};
	~GraphicsBufferManager();
	void addGraphicsBuffer(const std::string& key, GraphicsBuffer* graphicsBuffer);
	void removeGraphicsBuffer(const std::string& key);
	GraphicsBuffer* getGraphicsBuffer(const std::string& key) const { return mGraphicsBuffers.at(key); };
	void clear();
private:
	std::unordered_map<std::string, GraphicsBuffer*> mGraphicsBuffers;
};
