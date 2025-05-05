#include "GameObject.h"

namespace Entity {
	void ModelData::setTransform(utils::Matrix4x4 const& transform) {
		this->props.transformation = transform;
	}
}


