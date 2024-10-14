#include "ImGuiLayer.h"
#include "../DisplayWindow.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

namespace engine {
	ImGuiLayer::ImGuiLayer(DisplayWindow* window)
		: Layer("ImGuiLayer", LAYER_ORDER_MAX)
	{
		_nativeWindow = window->GetNativeWindow();
	}

	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(_nativeWindow), true);
		ImGui_ImplOpenGL3_Init();
	}

	void ImGuiLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}