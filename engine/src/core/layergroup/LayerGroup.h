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

			unsigned int sz = static_cast<unsigned int>(_layers.size());

			_idToIndex[id] = sz - 1;
			_indexToId[sz - 1] = id;
			for (unsigned int i = sz - 1; i > 0; i--) {
				if (_layers[i]->GetOrder() < _layers[i - 1]->GetOrder()) {
					SwapLayers(i, i - 1);
				} else {
					break;
				}
			}
			return id;
		}
		void RemoveLayer(int id);
		void Destroy();

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
		std::vector<Layer*>::const_iterator begin() const { return _layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return _layers.end(); }

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