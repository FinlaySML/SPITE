#pragma once

namespace Spite {
	class Entity;
	class Component
	{
		friend class Entity;
	private:
		Entity& parent;
	public:
		/// <summary>
		/// DO NOT USE THIS!!!
		/// Use the AddComponent() member function of Entity.
		/// </summary>
		Component(Entity& entity);
		virtual ~Component();
		virtual void Update(double dt);
		virtual void Draw(double dt);
		Entity& GetParent() const;
		/// <summary>
		/// Returns a string that I identifies this component's type
		/// <para>
		/// When creating a new component type:
		/// Create a static member of type std::string called "name", return it here
		/// </para>
		/// </summary>
		/// <returns></returns>
		virtual const std::string& GetName() = 0;
		/// <summary>
		/// Serialise the component; this will be called after YAML::BeginMap, so you must format the emitted YAML as key value pairs.
		/// <c>&apos;emitter &lt;&lt; YAML::Key &lt;&lt; &quot;Transparent&quot; &lt;&lt; YAML::Value &lt;&lt; transparent;&apos;</c>
		/// </summary>
		virtual void Serialise(YAML::Emitter&) const;
		virtual void Deserialise(const YAML::Node&);
	};
}

