#pragma once

#include "Hazel/Core.h"
#include "Hazel/Layer.h"

#include <vector>

namespace Hazel
{
class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* overlay);

	std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
	std::vector<Layer*>::iterator end() { return mLayers.end(); }
	
private:
	std::vector<Layer*> mLayers;
	std::vector<Layer*>::iterator mLayerInsert;
};
}
