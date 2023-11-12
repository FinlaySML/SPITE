#pragma once
#include "Serialisable.h"

namespace Spite {
	class Entity;
	class Component : public Serialisable
	{
		friend class Entity;
	private:
		Entity& parent;
	public:
		Component(Entity&);
		virtual ~Component();
		virtual void Update(double dt);
		virtual void Draw(double dt);
		Entity& GetParent() const;
		virtual const std::string& GetName() = 0;
		void Serialise(YAML::Emitter&) const override;
		void Deserialise(const YAML::Node&) override;
	};
}

