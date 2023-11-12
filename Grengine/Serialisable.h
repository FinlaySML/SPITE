#pragma once
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/emitter.h>
namespace Spite {
	class Serialisable {
	public:
		virtual void Serialise(YAML::Emitter&) const = 0;
		virtual void Deserialise(const YAML::Node&) = 0;
	};
}

