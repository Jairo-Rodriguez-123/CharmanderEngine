#pragma once
#include <imgui.h>
#include <string>
#include "../Core/Timer.hpp"

struct HUD {
  void draw(float speed, int lap, int totalLaps, float lapT, float bestLap, bool* showDebug){
    ImGui::Begin("HUD", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Vel: %.0f", speed);
    ImGui::Text("Vuelta: %d / %d", lap, totalLaps);
    ImGui::Text("Lap: %s", Timer::format(lapT).c_str());
    ImGui::Text("Best: %s", bestLap < 0 ? "--:--.--" : Timer::format(bestLap).c_str());
    ImGui::Checkbox("Debug IA", showDebug);
    ImGui::End();
  }
};
