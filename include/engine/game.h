
#pragma once

#include <iostream>
#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "nonRules.h"
#include "state.h"
#include "logger.h"

namespace engine
{
    class Game : public NonCopyable, public NonMovable
    {
    public:
        Game() : m_window({ 1280, 720 }, "BaseRunner")
        {
            m_window.setFramerateLimit(60);

            ImGui::SFML::Init(m_window);

            logger::init(true);

            //pushState(std::make_unique<state>(start));  //verify if this works
        }

        void run()
        {
            constexpr unsigned TPS = 60;
            const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
            unsigned ticks = 0;

            sf::Clock timer;
            sf::Time lastTime = sf::Time::Zero;
            sf::Time lag = sf::Time::Zero;

            while (m_window.isOpen() && !m_states.empty()) {
                auto& state = getCurrentState();

                auto time = timer.getElapsedTime();
                auto elapsed = time - lastTime;
                lastTime = time;
                lag += elapsed;

                state.handleInput();
                state.update(elapsed);

                while (lag >= timePerUpdate)
                {
                    ticks++;
                    lag -= timePerUpdate;
                    state.fixedUpdate(elapsed);

                    ImGui::EndFrame();
                }

                ImGui::SFML::Update(m_window, elapsed);

                m_window.clear();

                state.render(m_window);

                ImGui::SFML::Render(m_window);

                m_window.display();

                handleEvent();
                tryPop();
            }
        }

        template<typename T, typename... Args>
        void pushState(Args&&... args)
        {
            pushState(std::make_unique<T>(std::forward<Args>(args)...));
        }

        void pushState(std::unique_ptr<state> f_state)
        {
            m_states.push_back(std::move(f_state));
        }

        void popNStates(unsigned n) {
            if (n > m_states.size())
                throw "tried to pop more states that there are";

            m_shouldPop = n;
        }

        void popState()
        {   
            m_shouldPop = true;
        }

        void exitGame()
        {
            m_shouldPop = true;
            m_shouldExit = true;
        }

        template<typename T, typename... Args>
        void changeState(Args&&... args)
        {
            m_change = std::make_unique<T>(std::forward<Args>(args)...);
            m_shouldPop = true;
            m_shouldChangeState = true;
        }

        const sf::RenderWindow& getWindow() const
        {
            return m_window;
        }

    private:
        void handleEvent()
        {
            sf::Event e;

            while (m_window.pollEvent(e)) {
                ImGui::SFML::ProcessEvent(e);

                getCurrentState().handleEvent(e);
                switch (e.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                default:
                    break;
                }
            }
        }

        void tryPop()
        {
            if (m_shouldPop) {
                if (m_shouldExit) {
                    m_states.clear();
                    return;
                }
                else if (m_shouldChangeState) {
                    m_shouldChangeState = false;

                    m_states.pop_back();

                    pushState(std::move(m_change));

                    return;
                }

                for (int i = 0; i < m_shouldPop; i++)
                    m_states.pop_back();

                m_shouldPop = false;
            }
        }

        state& getCurrentState()
        {
            return *m_states.back();
        }

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<state>> m_states;

        unsigned m_shouldPop = 0;
        bool m_shouldExit = false;
        bool m_shouldChangeState = false;

        std::unique_ptr<state> m_change;
    };
}