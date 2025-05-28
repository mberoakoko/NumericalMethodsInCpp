//
// Created by mbero on 28/05/2025.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <bits/stdc++.h>
#include <SDL3/SDL.h>

namespace Dashboard {
    class Window {
    public:
        struct Settings {
            std::string name;
            std::uint16_t width;
            std::uint16_t height;
        };
        explicit Window(const Settings& settings)
        :   name_(std::move(settings.name)),
            width_(settings.width),
            height_(settings.height) {
            initialize_window();
            initialize_renderer();
        };
        explicit Window(const std::string& title, std::uint16_t width, std::uint16_t height)
        :   Window(Window::Settings{.name = std::move(title), .width = width, .height = height}) {};

        ~Window() {
            std::cout << "Closing window" << std::endl;
            SDL_DestroyRenderer(renderer_);
            SDL_DestroyWindow(window_);
        };

        SDL_Window* window() const { return window_; };
        SDL_Renderer* renderer() const { return renderer_; };

    private:
        auto initialize_window() -> void {
            std::cout << "Initializing window" << std::endl;
            auto window_flags {
                static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIGH_PIXEL_DENSITY)
            };
            constexpr int window_center_flag{SDL_WINDOWPOS_CENTERED};
            window_ = SDL_CreateWindow(name_.c_str(), width_, height_, window_flags);
        }

        auto initialize_renderer() -> void {
            // auto renderer_flags{};
            renderer_ = SDL_CreateRenderer(
              window_, nullptr
            );

            if (renderer_ == nullptr) {
                std::cout << SDL_GetError() << std::endl;
                return;
            }
        };

        std::string name_;
        std::uint16_t width_;
        std::uint16_t height_;
        SDL_Window* window_;
        SDL_Renderer* renderer_;
    };
}
#endif //WINDOW_HPP
