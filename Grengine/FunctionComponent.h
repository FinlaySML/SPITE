#pragma once
#include "Component.h"

namespace Spite {
    class FunctionComponent : public Component {
	public:
		FunctionComponent(Entity* parent, ComponentID id);
		void Update(float dt) override;
		std::function<void(FunctionComponent*, float)> updateFunc;
    };
}
