#include "LayerGroup.h"

namespace engine {
	void LayerGroup::RemoveLayer(int id) {
		auto pair = _idToIndex.find(id);
		if(pair == _idToIndex.end()) {
			return;
		}
		for(int i = pair->second; i < _layers.size() - 1; i++) {
			SwapLayers(i, i + 1);
		}

		Layer* layer = _layers.back();

		_indexToId.erase(_idToIndex[id]);
		_idToIndex.erase(pair);
		_layers.pop_back();

		delete layer;
	}

	void LayerGroup::Destroy() {
		for(auto& layer : _layers) {
			delete layer;
		}
		_layers.clear();
	}

	void LayerGroup::SwapLayers(int index1, int index2) {
		std::swap(_layers[index1], _layers[index2]);
		std::swap(_indexToId[index1], _indexToId[index2]);
		std::swap(_idToIndex[_indexToId[index1]], _idToIndex[_indexToId[index2]]);
	}
}