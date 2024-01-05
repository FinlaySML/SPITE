#pragma once
#include "Transform.h"
#include "PauseState.h"

namespace Spite {
	class Entity;
	using ComponentID = std::uint32_t;
	class Component
	{
		friend class Entity;
	private:
		Entity* entity;
	protected:
		Component(Entity* parent, ComponentID id);
	public:
		Component(Component&) = delete;
		Component& operator=(Component&) = delete;
		Component(Component&&) = delete;
		Component& operator=(Component&&) = delete;
		ComponentID id;
		Transform transform;
		PauseState paused;
		virtual ~Component();
		virtual void Update(float dt);
		virtual void Draw(const glm::mat3x3& worldTransform);
		Entity* GetEntity() const;
		/// <summary>
		/// Serialise the component; this will be called after YAML::BeginMap, so you must format the emitted YAML as key value pairs.
		/// <c>&apos;emitter &lt;&lt; YAML::Key &lt;&lt; &quot;Transparent&quot; &lt;&lt; YAML::Value &lt;&lt; transparent;&apos;</c>
		/// </summary>
		virtual void Serialise(YAML::Emitter&) const;
		virtual void Deserialise(const YAML::Node&);
	};
}

