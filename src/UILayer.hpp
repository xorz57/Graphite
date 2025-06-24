/// @author Georgios Fotopoulos

#include "Layer.hpp"

class UILayer final : public Layer {
public:
  UILayer();
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float deltaTime) override;
  void OnRenderUI() override;
  void Begin();
  void End();
};
