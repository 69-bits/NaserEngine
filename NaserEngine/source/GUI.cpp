#include "GUI.h"
#include "BaseApp.h"

extern BaseApp g_app;

void 
GUI::Init(void* window, ID3D11Device* device, ID3D11DeviceContext* devicecontext) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

  setupGUIStyle();

  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, devicecontext);
}

void 
GUI::update() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void 
GUI::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();
  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
}

void 
GUI::destroy() {
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void 
GUI::transformWindow() {
  static int selectedActorIndex = -1;

  ImGui::Begin("Transform Window");

  ImGui::Text("Actors in Scene:");
  for (int i = 0; i < (int)g_app.m_actors.size(); ++i) {
    auto& actor = g_app.m_actors[i];
    if (!actor) continue;
    bool isSelected = (selectedActorIndex == i);
    // Visible label: actor name; Internal ID: "##Actor_i"
    std::string label = actor->getName() + "##Actor_" + std::to_string(i);
    if (ImGui::Selectable(label.c_str(), isSelected)) {
      selectedActorIndex = i;
    }
  }

  ImGui::Separator();

  if (selectedActorIndex >= 0 && selectedActorIndex < (int)g_app.m_actors.size()) {
    auto& selectedActor = g_app.m_actors[selectedActorIndex];
    if (selectedActor) {
      auto transform = selectedActor->getComponent<Transform>();
      if (!transform.isNull()) {
        // Ahora los sliders modifican al transform del actor seleccionado
        ImGui::Text("Editing: %s", selectedActor->getName().c_str());

        ImGui::BeginChild("Position Sliders", ImVec2(0, 100), true);
        ImGui::Text("Position");
        ImGui::Separator();
        ImGui::SliderFloat("Pos X", &transform->position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Pos Y", &transform->position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Pos Z", &transform->position.z, -10.0f, 10.0f);
        ImGui::EndChild();

        ImGui::BeginChild("Rotation Sliders", ImVec2(0, 100), true);
        ImGui::Text("Rotation");
        ImGui::Separator();
        ImGui::SliderFloat("Rot X", &transform->rotation.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Rot Y", &transform->rotation.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Rot Z", &transform->rotation.z, -10.0f, 10.0f);
        ImGui::EndChild();

        ImGui::BeginChild("Scale Sliders", ImVec2(0, 100), true);
        ImGui::Text("Scale");
        ImGui::Separator();
        ImGui::SliderFloat("Scale X", &transform->scale.x, 0.1f, 10.0f);
        ImGui::SliderFloat("Scale Y", &transform->scale.y, 0.1f, 10.0f);
        ImGui::SliderFloat("Scale Z", &transform->scale.z, 0.1f, 10.0f);
        ImGui::EndChild();
      }
    }
  }

  ImGui::End();
}

void 
GUI::setupGUIStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  style.FrameBorderSize = 1.0f;
  style.WindowBorderSize = 1.0f;

  ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Fondo oscuro
  colors[ImGuiCol_Border] = ImVec4(0.9f, 0.7f, 0.0f, 1.0f);   // Color del borde
  colors[ImGuiCol_TitleBg] = ImVec4(0.8f, 0.4f, 0.0f, 1.0f);  // Fondo del título
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.9f, 0.5f, 0.0f, 1.0f); // Fondo del título activo
}
