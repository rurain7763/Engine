#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include "EngineHeader.h"
#include "Layer.h"

namespace engine {
	class EG_API LayerGroup {
	public:
		LayerGroup() = default;
		~LayerGroup() = default;

		template<typename TLayer, typename... TArgs>
		int AddLayer(TArgs&&... args) {
			int id = _layerCount++;
			TLayer* layer = new TLayer(std::forward<TArgs>(args)...);
			_layers.push_back(layer);
			_idToIndex[id] = _layers.size() - 1;
			_indexToId[_layers.size() - 1] = id;
			for (int i = _layers.size() - 1; i > 0; i--) {
				if (_layers[i]->GetOrder() < _layers[i - 1]->GetOrder()) {
					SwapLayers(i, i - 1);
				} else {
					break;
				}
			}
			layer->OnAttach();
			return id;
		}
		void RemoveLayer(int id);
		void Render();
		void Destroy();

	private:
		void SwapLayers(int index1, int index2);

	private:
		int _layerCount = 0;
		std::vector<Layer*> _layers;

		std::unordered_map<int, int> _idToIndex;
		std::unordered_map<int, int> _indexToId;
	};
}

#endif