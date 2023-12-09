#pragma once
#include "Component.h"

namespace Spite {
    class FunctionComponent : public Component {
		std::function<void(FunctionComponent*, double)> f;
	public:
		FunctionComponent(Entity* parent, ComponentID id);
		void Update(float dt) override;
		void SetFunction(const std::function<void(FunctionComponent*,double)>& function);
    };
}
