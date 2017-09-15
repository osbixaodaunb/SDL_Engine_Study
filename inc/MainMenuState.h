/*Copyright 2017 MIT*/
#ifndef INC_MAINMENUSTATE_H_
#define INC_MAINMENUSTATE_H_

#include "MenuState.h"

#include <vector>
#include <string>

class MainMenuState : public MenuState {
 public:
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const {
    return s_menuID;
  }

 private:
  void setCallbacks(const std::vector<Callback> &callbacks);

  static void s_menuToPlay();
  static void s_exitFromMenu();

  static const std::string s_menuID;
};


#endif  // INC_MAINMENUSTATE_H_
