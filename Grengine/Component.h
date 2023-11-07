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
	};
}

