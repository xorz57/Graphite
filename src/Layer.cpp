/// @author Georgios Fotopoulos

#include "Layer.hpp"

void Layer::SetName(std::string name) { m_Name = std::move(name); }

const std::string &Layer::GetName() const { return m_Name; }
