#include "Game/Game.hpp"
#include <fmt/format.h>

void DrawFPSGraph(float deltaTime) {
    static std::vector<float> frameTimes(90, 0.0f);  // Rolling buffer for 60 frames
    static int currentIndex = 0;                     // Current index in the rolling buffer
    static float totalTime = 0.0f;                   // Total time for the last 60 frames

    // Calculate FPS
    float fps = 1.0f / deltaTime;

    // Update rolling buffer
    totalTime -= frameTimes[currentIndex];                  // Subtract the old value at the index
    frameTimes[currentIndex] = deltaTime;                   // Update with new delta time
    totalTime += frameTimes[currentIndex];                  // Add new value
    currentIndex = (currentIndex + 1) % frameTimes.size();  // Move to next index

    // Average FPS over the buffer
    float averageFPS = frameTimes.size() / totalTime;

    // Draw FPS Graph

    // Create an array for plotting
    std::vector<float> fpsValues(frameTimes.size());
    for (size_t i = 0; i < frameTimes.size(); ++i) {
        fpsValues[i] = 1.0f / frameTimes[(currentIndex + i) % frameTimes.size()];
    }

    // Plot graph
    ImGui::PlotLines("FPS", fpsValues.data(), fpsValues.size(), 0, nullptr, 0.0f, 70.0f, ImVec2(0, 120));
}

void Game::applyUserInterfaceSystem() {
    if (debug_view) {

        ImGui::Begin("Visual Debugger");
        if (ImGui::BeginTabBar("TabBar")) {
            if (ImGui::BeginTabItem("General")) {
                auto& pc = player->get<PlayerInputComponent>();
                ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

                DrawFPSGraph(ImGui::GetIO().DeltaTime);
                ImGui::Text("Mouse: (X=%d, Y=%d)", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                ImGui::Text("Movement: %c%c%c%c", pc.move_up ? 'W' : ' ', pc.move_left ? 'A' : ' ', pc.move_down ? 'S' : ' ', pc.move_right ? 'D' : ' ');
                ImGui::Text("Shooting: %s", player->get<PlayerInputComponent>().shoot ? "YES" : "NO");
                ImGui::Checkbox("Paused", &paused);
                ImGui::Checkbox("Spwn Enemry", &should_spawn);
                ImGui::Checkbox("Immunity", &player->get<ImmunityComponent>().exists);
                ImGui::Text("Player Health: %.1f", player->get<HealthComponent>().current_helth);
                ImGui::Text("Angular Momentum"); ImGui::SameLine();
                ImGui::SliderFloat("", &this->player->get<TransformComponent>().angular_momentum, 0.0, 5, "%.3f");
                ImGui::Text("Number of Entities: %d", (int)entity_manager.numEntities());
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Entities")) {
                ImGui::Text("Number of Entities: %d", (int)entity_manager.numEntities());
                for (auto entt : entity_manager.getAllEntities()) {
                    const auto& t = entt->get<TransformComponent>().pos;
                    bool isOutOfBound = false;

                    ImGui::PushID(entt->id());  // Push unique ID for ImGui.

                    // Create a table row
                    if (ImGui::BeginTable("EntityRow", 4, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit)) {
                        ImGui::TableNextRow();

                        // Column 1: Button
                        ImGui::TableSetColumnIndex(0);
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));  // Green otherwise
                        if (entt->isPermanant()) {
                            ImGui::BeginDisabled();
                            ImGui::Button("x");
                            ImGui::EndDisabled();
                        } else if (ImGui::Button("x")) {
                            entt->destroy();
                        }
                        ImGui::PopStyleColor();

                        // Column 2: Entity ID
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("ID: %d", entt->id());

                        // Column 3: Position
                        ImGui::TableSetColumnIndex(2);
                        if (isOutOfBound) {
                            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Red text
                            ImGui::Text("Pos: (%.2f, %.2f)", t.x, t.y);
                            ImGui::PopStyleColor();
                        } else {
                            ImGui::Text("Pos: (%.2f, %.2f)", t.x, t.y);
                        }

                        // Column 4: Tag
                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text("Tag: %s", entt->tagStr());

                        ImGui::EndTable();
                    }

                    ImGui::PopID();  // Restore ID scope.
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();
    }

    score_text.setPosition(10, 10);
    score_text.setString(fmt::format("Score: {}", score));
    this->window.draw(score_text);

    if (game_over) {
        game_status_text.setFillColor(sf::Color(255, 20, 60, 255));
        game_status_text.setString("    <GAME OVER>\nPress 'R' to restart");
    } else if (paused) {
        game_status_text.setFillColor(sf::Color(50, 255, 60, 255));
        game_status_text.setString("<PAUSED>");
    }

    if (paused || game_over) {
        auto game_status_bounds = game_status_text.getLocalBounds();
        game_status_text.setOrigin(game_status_bounds.left + game_status_bounds.width / 2.0f, game_status_bounds.top + game_status_bounds.height / 2.0f);
        game_status_text.setPosition(window_size.x / 2, (window_size.y / 2) - 150);
        this->window.draw(game_status_text);
    }
}