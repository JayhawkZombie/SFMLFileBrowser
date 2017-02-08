#ifndef GLOBAL_HOOKS_H
#define GLOBAL_HOOKS_H

#include <SFML\Graphics.hpp>
#include <TGUI/TGUI.hpp>

extern sf::Vector2u WindowSize;
extern std::shared_ptr<tgui::Gui> GUI;

extern void MessageAlert(const std::string &message);

#endif
