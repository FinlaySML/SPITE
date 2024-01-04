#include "pch.h"
#include "Transform.h"

Spite::Transform::Transform() : position{0,0}, scale{1,1}, rotation{0} {}

glm::mat3x3 Spite::Transform::GetMatrix() const {
    glm::mat3x3 t{ 1.0 };
    t = glm::translate(t, position);
    t = glm::rotate(t, -rotation);
    t = glm::scale(t, scale);
    return t;
}

void Spite::Transform::Serialise(YAML::Emitter& out) const {
    out << YAML::Key << "Position" << YAML::Value << YAML::Flow << YAML::BeginSeq << position.x << position.y << YAML::EndSeq;
    out << YAML::Key << "Scale" << YAML::Value << YAML::Flow << YAML::BeginSeq << scale.x << scale.y << YAML::EndSeq;
    out << YAML::Key << "Rotation" << YAML::Value << rotation;
}

Spite::Transform Spite::Transform::Deserialise(const YAML::Node& node) {
    Transform tf{};
    tf.position.x = node["Position"][0].as<float>();
    tf.position.y = node["Position"][1].as<float>();
    tf.scale.x = node["Scale"][0].as<float>();
    tf.scale.y = node["Scale"][1].as<float>();
    tf.rotation = node["Rotation"].as<float>();
    return tf;
}
