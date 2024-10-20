#include "Layer2D.h"

#include "imgui/imgui.h"

void Layer2D::OnAttach(engine::Application& app) {
    _cameraCtrl = std::make_shared<engine::OrthoGraphicCameraController>();
    _cameraCtrl->Init(app);

    _texture.reset( engine::Texture2D::Create("assets/images/dog.png"));
}

void Layer2D::OnDetach() {
	_texture.reset();
	_cameraCtrl.reset();
}

void Layer2D::OnUpdate(engine::Timestem deltaTime) {
    _cameraCtrl->Update(deltaTime);

    engine::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    engine::RenderCommand::Clear();

    engine::Renderer2D::BeginScene(_cameraCtrl->GetCamera());
    engine::Renderer2D::DrawRect({ 0.0f, 0.0f, 0.f}, { 1.0f, 1.0f }, 0.0f, { 0.2f, 0.3f, 0.8f, 1.0f });
    engine::Renderer2D::DrawRect({ 0.5f, 0.5f, 0.f}, { 0.5f, 0.5f }, 0.0f, { 0.8f, 0.3f, 0.2f, 1.0f });
    engine::Renderer2D::DrawRect({ 0.0f, 0.0f, -0.5f}, { 10.f, 10.f }, 0.0f, _texture.get());
    engine::Renderer2D::EndScene();
}

void Layer2D::OnGUIUpdate() {
    ImGui::Begin("2D Layer");
    ImGui::Text("Hello, 2D Layer!");
    ImGui::End();
}