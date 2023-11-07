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
		virtual void Update(double dt) = 0;
		virtual void Draw(double dt) = 0;
		Entity& GetParent() const;
	};
}

