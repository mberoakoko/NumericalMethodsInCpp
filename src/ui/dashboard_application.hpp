//
// Created by mbero on 28/05/2025.
//

#ifndef DASHBOARD_APPLICATION_HPP
#define DASHBOARD_APPLICATION_HPP
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <imgui.h>
#include "src/ui/dashboard/window.hpp"

namespace Dashboard {
    class Application {
    public:
        explicit Application() {
            std::cout << "Dashboard application created" << std::endl;
            if (
                bool result = SDL_Init({SDL_INIT_VIDEO|SDL_INIT_EVENTS });
                result == false) {
                std::cout << "Entered This block "<<std::endl;
                std::cout << SDL_GetError() << std::endl;
                exit_status = 1;
                }
            window_ = std::make_unique<Window>(Window::Settings{.name = "Main Window ", .width = 1080, .height = 720});
        };
        ~Application() {
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();;
            SDL_Quit();
        };

        auto  run() -> int {
            if (exit_status == 1) {
                return exit_status;
            }
            running = true;
            std::cout<< "Running ... \n";
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
            ImGui::StyleColorsDark();

            ImGui_ImplSDL3_InitForSDLRenderer(
                window_->window(),
                window_->renderer()
            );
            ImGui_ImplSDLRenderer3_Init(window_->renderer());
            while (running) {
                SDL_Event event {};
                while (SDL_PollEvent(&event)) {
                    ImGui_ImplSDL3_ProcessEvent(&event);
                    if (event.type == SDL_EVENT_QUIT) {
                        stop();
                    }
                }
                ImGui_ImplSDLRenderer3_NewFrame();
                ImGui_ImplSDL3_NewFrame();
                ImGui::NewFrame();

                // Render "some panel".
                ImGui::Begin("Some panel", &m_show_some_panel);
                ImGui::Text("Hello World");
                ImGui::End();

                ImGui::Render();
                SDL_SetRenderDrawColor(
                    window_->renderer(), 100, 100, 100, 100);
                SDL_RenderClear(window_->renderer());
                SDL_RenderPresent(window_->renderer());

                ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), window_->renderer());
                SDL_RenderPresent(window_->renderer());
            }
            return exit_status;
        };
        auto stop() -> void {
            running = false;
        }

    private:
        auto initialize_appliction_() -> void {

        };
        int running { 0 };
        int exit_status { 0 };
        std::unique_ptr<Window> window_ {nullptr};
        bool m_show_some_panel { true };


    };
}
#endif //DASHBOARD_APPLICATION_HPP
