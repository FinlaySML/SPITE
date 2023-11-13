#pragma once

namespace Spite {
	class Entity;
	class Component
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
		virtual void Serialise(YAML::Emitter&) const;
		virtual void Deserialise(const YAML::Node&);
	};
}

