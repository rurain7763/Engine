#include "Layer2D.h"

#include "imgui/imgui.h"

void Layer2D::OnAttach(engine::Application& app) {
    engine::Renderer2D::Init();
}

void Layer2D::OnDetach() {
    engine::Renderer2D::Destroy();
}

void Layer2D::OnUpdate(engine::Timestem deltaTime) {
    engine::Renderer2D::BeginScene(_camera->GetCamera());
    engine::Renderer2D::DrawRect({ 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, { 0.2f, 0.3f, 0.8f, 1.0f });
    engine::Renderer2D::EndScene();
}

void Layer2D::OnGUIUpdate() {
    ImGui::Begin("2D Layer");
    ImGui::Text("Hello, 2D Layer!");
    ImGui::End();
}