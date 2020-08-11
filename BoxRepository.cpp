#include "BoxRepository.h"
#include <utility>

void BoxRepository::addBox(std::string id) {
	_boxMap.insert(std::pair<std::string, BoxPtr>(id, BoxPtr(new Box())));
}

Box* BoxRepository::getBox(std::string id) {
	return _boxMap[id].get();
}