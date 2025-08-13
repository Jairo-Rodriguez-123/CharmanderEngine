#include "EngineGUI.h"
#include "Window.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"
#include <filesystem>
#include "ActorSerializer.h" // Para guardar/cargar actores

namespace fs = std::filesystem;

void
EngineGUI::init(const EngineUtilities::TSharedPointer<Window>& window) {
  ImGui::SFML::Init(*window->m_windowPtr);
  SetupVektorCoreGUIStyle();
  selectedActorIndex = -1;
}

void
EngineGUI::update(const EngineUtilities::TSharedPointer<Window>& window,
  sf::Time deltaTime) {
  ImGui::SFML::Update(*window->m_windowPtr, deltaTime);
}

void
EngineGUI::render(const EngineUtilities::TSharedPointer<Window>& window) {
  ImGui::SFML::Render(*window->m_windowPtr);
}

void
EngineGUI::destroy() {
  ImGui::SFML::Shutdown();
}

void
EngineGUI::processEvent(const sf::Window& window, const sf::Event& event) {
  ImGui::SFML::ProcessEvent(window, event);
}

void
EngineGUI::SetupVektorCoreGUIStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  // Bordes y elementos redondeados sutilmente
  style.WindowRounding = 4.0f;
  style.FrameRounding = 4.0f;
  style.GrabRounding = 4.0f;
  style.ScrollbarRounding = 4.0f;
  style.TabRounding = 3.0f;
  style.WindowBorderSize = 1.5f;
  style.FrameBorderSize = 1.0f;
  style.WindowPadding = ImVec2(10, 10);
  style.FramePadding = ImVec2(8, 4);
  style.ItemSpacing = ImVec2(8, 6);
  style.ItemInnerSpacing = ImVec2(6, 4);

  ImVec4* colors = style.Colors;
  // Negro absoluto para el fondo
  colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.04f, 0.0f, 0.09f, 1.00f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);

  // Texto blanco total
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.1f, 0.7f, 0.6f); // Morado apagado

  // MORADO NEÓN para todo lo interactivo (bordes, líneas, botones, tabs)
  ImVec4 neon = ImVec4(0.89f, 0.08f, 1.00f, 1.00f); // Fuchsia brillante

  colors[ImGuiCol_Border] = neon;
  colors[ImGuiCol_BorderShadow] = ImVec4(0.2f, 0.0f, 0.3f, 0.7f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.00f, 0.13f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = neon;
  colors[ImGuiCol_FrameBgActive] = neon;
  colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.0f, 0.2f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = neon;
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.0f, 0.12f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.04f, 0.0f, 0.07f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.0f, 0.15f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab] = neon;
  colors[ImGuiCol_ScrollbarGrabHovered] = neon;
  colors[ImGuiCol_ScrollbarGrabActive] = neon;
  colors[ImGuiCol_CheckMark] = neon;
  colors[ImGuiCol_SliderGrab] = neon;
  colors[ImGuiCol_SliderGrabActive] = neon;
  colors[ImGuiCol_Button] = ImVec4(0.18f, 0.0f, 0.25f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = neon;
  colors[ImGuiCol_ButtonActive] = neon;
  colors[ImGuiCol_Header] = ImVec4(0.20f, 0.0f, 0.25f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = neon;
  colors[ImGuiCol_HeaderActive] = neon;
  colors[ImGuiCol_Separator] = neon;
  colors[ImGuiCol_SeparatorHovered] = neon;
  colors[ImGuiCol_SeparatorActive] = neon;
  colors[ImGuiCol_ResizeGrip] = neon;
  colors[ImGuiCol_ResizeGripHovered] = neon;
  colors[ImGuiCol_ResizeGripActive] = neon;
  colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.0f, 0.19f, 1.00f);
  colors[ImGuiCol_TabHovered] = neon;
  colors[ImGuiCol_TabActive] = neon;
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.0f, 0.16f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = neon;
  colors[ImGuiCol_PlotLines] = neon;
  colors[ImGuiCol_PlotLinesHovered] = neon;
  colors[ImGuiCol_PlotHistogram] = neon;
  colors[ImGuiCol_PlotHistogramHovered] = neon;
  colors[ImGuiCol_TextSelectedBg] = neon;
  colors[ImGuiCol_DragDropTarget] = neon;
  colors[ImGuiCol_NavHighlight] = neon;
  colors[ImGuiCol_NavWindowingHighlight] = neon;
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

  // Extra: Si quieres que hasta los child-windows, combos y popups sean neón
  colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.0f, 0.12f, 0.98f);
}


// ---- BAR MENU tipo Unity ----
void
EngineGUI::menuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    /* ====================  FILE  ==================== */
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New Scene", "Ctrl+N")) {/* TODO */ }
      if (ImGui::MenuItem("Open Scene...", "Ctrl+O")) {/* TODO */ }
      if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {/* TODO */ }
      if (ImGui::MenuItem("Save Scene As…")) {/* TODO */ }
      ImGui::Separator();

      /* ----------  Sub-menú con los archivos recientes ---------- */
      if (ImGui::BeginMenu("Recent Files"))
      {
        // En la práctica, llena este array leyendo un historial.
        const char* recents[] = { "level01.scene", "tutorial.scene", "myTest.scene" };
        for (const char* f : recents)
          if (ImGui::MenuItem(f)) {/* TODO: abrir f */ }
        ImGui::EndMenu();
      }

      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "Alt+F4")) {/* TODO: salir */ }
      ImGui::EndMenu();
    }

    /* ====================  EDIT  ==================== */
    if (ImGui::BeginMenu("Edit"))
    {
      ImGui::MenuItem("Undo", "Ctrl+Z");
      ImGui::MenuItem("Redo", "Ctrl+Y");
      ImGui::Separator();
      ImGui::MenuItem("Cut", "Ctrl+X");
      ImGui::MenuItem("Copy", "Ctrl+C");
      ImGui::MenuItem("Paste", "Ctrl+V");
      ImGui::EndMenu();
    }

    /* ====================  VIEW  ==================== */
    if (ImGui::BeginMenu("View"))
    {
      ImGui::MenuItem("Hierarchy");
      ImGui::MenuItem("Inspector");
      ImGui::MenuItem("Console");
      ImGui::MenuItem("File Manager");
      ImGui::EndMenu();
    }

    /* ====================  WINDOW  ==================== */
    if (ImGui::BeginMenu("Window"))
    {
      ImGui::MenuItem("Maximize");
      ImGui::MenuItem("Minimize");
      ImGui::MenuItem("Reset Layout");
      ImGui::EndMenu();
    }

    /* ====================  HELP  ==================== */
    if (ImGui::BeginMenu("Help"))
    {
      ImGui::MenuItem("Documentation  (F1)");
      ImGui::MenuItem("Report a Bug");
      ImGui::MenuItem("About VektorCoreEngine");
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

// ---- HIERARCHY ----
void
EngineGUI::hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
  ImGui::Begin("Hierarchy");
  for (int i = 0; i < actors.size(); ++i) {
    std::string name = actors[i]->getName();
    bool isSelected = (selectedActorIndex == i);
    if (ImGui::Selectable(name.c_str(), isSelected, ImGuiSelectableFlags_AllowDoubleClick)) {
      selectedActorIndex = i;
    }
    if (isSelected) {
      ImDrawList* draw_list = ImGui::GetWindowDrawList();
      ImVec2 p_min = ImGui::GetItemRectMin();
      ImVec2 p_max = ImGui::GetItemRectMax();
      draw_list->AddRect(p_min, p_max, IM_COL32(180, 40, 255, 255), 4.0f, 0, 3.5f);
    }
  }
  ImGui::End();
}

// ---- INSPECTOR (modifica el actor seleccionado con botones XYZ a color y sliders) ----
void
EngineGUI::inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
  ImGui::Begin("Inspector");

  if (selectedActorIndex >= 0 && selectedActorIndex < actors.size() && actors[selectedActorIndex]) {
    auto actor = actors[selectedActorIndex];

    bool isStatic = false;
    ImGui::Checkbox("##Static", &isStatic);
    ImGui::SameLine();

    char objectName[128];
    std::string name = actor->getName();
    std::copy(name.begin(), name.end(), objectName);
    objectName[name.size()] = '\0';

    ImGui::InputText("##ObjectName", objectName, IM_ARRAYSIZE(objectName));
    ImGui::SameLine();

    if (ImGui::Button("Icon")) {
    }

    ImGui::Separator();

    const char* tags[] = { "Untagged", "Player", "Enemy", "Environment" };
    static int currentTag = 0;
    ImGui::Combo("Tag", &currentTag, tags, IM_ARRAYSIZE(tags));
    ImGui::SameLine();

    const char* layers[] = { "Default", "TransparentFX", "Ignore Raycast", "Water", "UI" };
    static int currentLayer = 0;
    ImGui::Combo("Layer", &currentLayer, layers, IM_ARRAYSIZE(layers));

    ImGui::Separator();
    // --- Fin bloque nuevo ---

    auto transform = actor->getComponent<Transform>();
    if (transform) {
      float pos[3] = { transform->getPosition().x, transform->getPosition().y, 0.0f };
      float rot[3] = { transform->getRotation().x, transform->getRotation().y, 0.0f };
      float sca[3] = { transform->getScale().x, transform->getScale().y, 1.0f };

      ImGui::PushItemWidth(60);

      // Position
      ImGui::Text("Position");
      ImGui::SameLine(100);
      ImGui::PushID("PosX");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.85f, 0.25f, 0.25f, 1.0f));
      ImGui::Button("X"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##PosX", &pos[0], 0.5f);
      ImGui::PopID();

      ImGui::SameLine(); ImGui::PushID("PosY");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.85f, 0.25f, 1.0f));
      ImGui::Button("Y"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##PosY", &pos[1], 0.5f);
      ImGui::PopID();

      ImGui::SameLine(); ImGui::PushID("PosZ");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.85f, 1.0f));
      ImGui::Button("Z"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##PosZ", &pos[2], 0.5f);
      ImGui::PopID();

      // Rotation
      ImGui::Text("Rotation");
      ImGui::SameLine(100);
      ImGui::PushID("RotX");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.85f, 0.25f, 0.25f, 1.0f));
      ImGui::Button("X"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##RotX", &rot[0], 1.0f);
      ImGui::PopID();

      ImGui::SameLine(); ImGui::PushID("RotY");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.85f, 0.25f, 1.0f));
      ImGui::Button("Y"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##RotY", &rot[1], 1.0f);
      ImGui::PopID();

      ImGui::SameLine(); ImGui::PushID("RotZ");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.85f, 1.0f));
      ImGui::Button("Z"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##RotZ", &rot[2], 1.0f);
      ImGui::PopID();

      // Scale
      ImGui::Text("Scale");
      ImGui::SameLine(100);
      ImGui::PushID("ScaX");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.85f, 0.25f, 0.25f, 1.0f));
      ImGui::Button("X"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##ScaX", &sca[0], 0.05f, 0.01f, 100.0f);
      ImGui::PopID();

      ImGui::SameLine(); ImGui::PushID("ScaY");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.85f, 0.25f, 1.0f));
      ImGui::Button("Y"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##ScaY", &sca[1], 0.05f, 0.01f, 100.0f);
      ImGui::PopID();

      ImGui::SameLine(); ImGui::PushID("ScaZ");
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.85f, 1.0f));
      ImGui::Button("Z"); ImGui::PopStyleColor();
      ImGui::SameLine(); ImGui::DragFloat("##ScaZ", &sca[2], 0.05f, 0.01f, 100.0f);
      ImGui::PopID();

      // Aplicar cambios
      transform->setPosition(sf::Vector2f(pos[0], pos[1]));
      transform->setRotation(sf::Vector2f(rot[0], rot[1]));
      transform->setScale(sf::Vector2f(sca[0], sca[1]));

      ImGui::PopItemWidth();
    }
  }

  ImGui::End();
}



// ---- CONSOLE ----
void
EngineGUI::console() {
  ImGui::Begin("Console");
  ImGui::Text("Logs and messages will appear here.");
  ImGui::End();
}

// ---- OUTLINE DRAW ----
void
EngineGUI::drawSelectedOutline(
  sf::RenderWindow* renderWindow,
  const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors)
{
  int idx = selectedActorIndex;
  if (idx >= 0 && idx < actors.size() && actors[idx]) {
    auto shapeComp = actors[idx]->getComponent<CShape>();
    if (shapeComp) {
      auto shapePtr = shapeComp->getShapePtr();
      if (shapePtr) {
        float thickness = 2.0f; // Default
        // If is track, thinner
        if (actors[idx]->getName() == "Track Actor")
          thickness = 0.5f;
        sf::Color oldOutlineColor = shapePtr->getOutlineColor();
        float oldThickness = shapePtr->getOutlineThickness();
        sf::Color oldFill = shapePtr->getFillColor();

        shapePtr->setOutlineThickness(thickness);
        shapePtr->setOutlineColor(sf::Color(180, 40, 255)); // neon purple
        shapePtr->setFillColor(sf::Color(0, 0, 0, 0));
        renderWindow->draw(*shapePtr);

        // Restore
        shapePtr->setOutlineColor(oldOutlineColor);
        shapePtr->setOutlineThickness(oldThickness);
        shapePtr->setFillColor(oldFill);
      }
    }
  }
}


// ---- FILE MANAGER PANEL ----
void
EngineGUI::fileManagerPanel(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
  ImGui::Begin("File Manager");
  static char fileName[128] = "actors.txt";
  ImGui::InputText("Actors File", fileName, IM_ARRAYSIZE(fileName));
  if (ImGui::Button("Save Actors")) {
    ActorSerializer::saveActorsToFile(fileName, actors);
  }
  ImGui::SameLine();
  if (ImGui::Button("Load Actors")) {
    actors.clear();
    ActorSerializer::loadActorsFromFile(fileName, actors);
  }
  ImGui::Separator();
  ImGui::Text("Available files:");
  for (const auto& entry : fs::directory_iterator(".")) {
    std::string fname = entry.path().filename().string();
    if (fname.size() >= 4 && fname.substr(fname.size() - 4) == ".txt") {
      if (ImGui::Selectable(fname.c_str())) {
        strncpy(fileName, fname.c_str(), sizeof(fileName));
      }
    }
  }
  ImGui::End();
}