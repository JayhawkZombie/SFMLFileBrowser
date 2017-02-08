#include <TGUI\TGUI.hpp>

#include <string>
#include <filesystem>

tgui::ListBox::Ptr dirview;
std::experimental::filesystem::v1::path CurrentPath;
std::experimental::filesystem::v1::directory_iterator CurrentDirectory;

std::vector<std::string> GetDirectoryEntries(std::experimental::filesystem::v1::directory_iterator &iter)
{
  std::vector<std::string> paths;

  for (auto & path : iter) {
    paths.push_back(path.path().string());
  }

  return paths;
}

bool IsItemPath(std::string maybepath)
{
  if (std::experimental::filesystem::v1::exists(maybepath)) {
    return true;
  }

  return false;
}

void FillTableWithCurrentPath()
{
  auto dir_iter = std::experimental::filesystem::v1::directory_iterator(CurrentPath);

  dirview->removeAllItems();
  std::cerr << "New directory : " << CurrentPath.string() << std::endl;

  auto v = GetDirectoryEntries(dir_iter);
  for (auto & item : v) {
    dirview->addItem(item);
  }
}

void DoubleClicked(std::string filepath)
{
  //If it is a path, then we will travel to it
  if (std::experimental::filesystem::v1::is_directory(filepath)) {
    CurrentPath = std::experimental::filesystem::v1::path(filepath);
    FillTableWithCurrentPath();
  }
}

void ItemSelected(std::string fileorpath)
{
  auto __path = std::experimental::filesystem::v1::path(fileorpath);
  std::cout << "Entry selected : " << __path.string() << std::endl;
}

void TravelToPath(std::string path)
{

}

void GoUp()
{
  auto path = CurrentDirectory->path();

  std::cerr << "Current path : " << CurrentPath.string() << std::endl;
  std::cerr << "Parent path : " << CurrentPath.parent_path().string() << std::endl;

  if (std::experimental::filesystem::v1::exists(CurrentPath.parent_path())) {
    CurrentPath = CurrentPath.parent_path();
    FillTableWithCurrentPath();
  }
  else {
    std::cerr << "Path does not exist" << std::endl;
  }
}


int main()
{
  sf::RenderWindow Window(sf::VideoMode(800, 800), "File Browser Test");

  sf::Event event;
  tgui::Gui GUI{ Window };

  tgui::Scrollbar::Ptr sbar = std::make_shared<tgui::Scrollbar>();
  sbar->setPosition({ 785, 0 });
  sbar->setSize({ 15, 800 });

  tgui::Button::Ptr UpPath = std::make_shared<tgui::Button>();
  UpPath->setPosition({ 10,10 });
  UpPath->setSize({ 20,20 });
  UpPath->setText("../");
  GUI.add(UpPath);
  UpPath->connect("clicked", []() {GoUp(); });

  dirview = std::make_shared<tgui::ListBox>();
  dirview->setPosition({ 0, 50 });
  dirview->setSize({ 800, 800 });
  dirview->setScrollbar(sbar);

  dirview->connect("doubleclicked", [](std::string path) {DoubleClicked(path); });
  dirview->connect("itemselected", [](std::string path) {ItemSelected(path); });
  CurrentDirectory = std::experimental::filesystem::v1::directory_iterator(std::experimental::filesystem::v1::current_path());
  
  auto path = CurrentDirectory->path();

  //fill the initail list
  auto v = GetDirectoryEntries(CurrentDirectory);
  for (auto & dir_entry : v) {
    dirview->addItem(dir_entry);
  }

  CurrentDirectory = std::experimental::filesystem::v1::directory_iterator(std::experimental::filesystem::v1::current_path());
  CurrentPath = CurrentDirectory->path().parent_path();
  GUI.add(dirview);

  while (Window.isOpen())
  {

    while (Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        Window.close();
      
      GUI.handleEvent(event);

    }


    Window.clear();
    GUI.draw();
    Window.display();

  }

}
