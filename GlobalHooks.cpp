#include "GlobalHooks.h"

sf::Vector2u WindowSize;
std::shared_ptr<tgui::Gui> GUI;

void MessageAlert(const std::string & message)
{
  tgui::MessageBox::Ptr mbox = std::make_shared<tgui::MessageBox>();
  mbox->setText(message);
  mbox->setSize({ 400, 400 });

  float xDiff = WindowSize.x - 400.f;
  float yDiff = WindowSize.y - 400.f;

  mbox->setPosition({ xDiff / 2.f, yDiff / 2.f });

  tgui::Button::Ptr btn = std::make_shared<tgui::Button>();
  btn->setText("OK");
  btn->setPosition({ 180, 350 });
  mbox->add(btn);

  GUI->add(mbox, "errorAlert");
  GUI->focusWidget(mbox);
  mbox->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

  mbox->connect("closed", [mbox]() { mbox->hide(); GUI->remove(mbox); });
  btn->connect("clicked", [mbox]() { mbox->hide(); GUI->remove(mbox); });
}
