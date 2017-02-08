#include <TGUI\TGUI.hpp>

#include <string>
#include <filesystem>

#include "FileBrowser.h"

void FileSelected(std::string file)
{
  std::cout << "Selected file: " << file << std::endl;
}


int main()
{
  sf::RenderWindow Window(sf::VideoMode(800, 800), "File Browser Test");

  sf::Event event;
  WindowSize = Window.getSize();
  GUI = std::make_shared <tgui::Gui>(Window);

  FileBrowser Browser;

  tgui::Theme::Ptr Theme = std::make_shared<tgui::Theme>("UIDark.txt");

  Browser.Open(std::experimental::filesystem::v1::current_path(), FileSelected, Theme);

  while (Window.isOpen())
  {

    while (Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        Window.close();
      
      GUI->handleEvent(event);

    }


    Window.clear();
    GUI->draw();
    Window.display();

  }

}