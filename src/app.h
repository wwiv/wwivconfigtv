/*
 * Copyright (C)2023 WWIV Software Services
 *
 * Licensed  under the  Apache License, Version  2.0 (the "License");
 * you may not use this  file  except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless  required  by  applicable  law  or agreed to  in  writing,
 * software  distributed  under  the  License  is  distributed on an
 * "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,
 * either  express  or implied.  See  the  License for  the specific
 * language governing permissions and limitations under the License.
 */

#ifndef INCLUDED_WWIVCONFIGTV_APP_H
#define INCLUDED_WWIVCONFIGTV_APP_H

#include "tvision/tv.h"
#include <chrono>
#include <memory>
#include <string>
#include <mutex>
#include <thread>

class TMenuBar;
class TStatusLine;
class TEditWindow;
class TDialog;

class ConfigApp : public TApplication {

public:
  ConfigApp(int argc, char** argv);
  ~ConfigApp();

  virtual TPalette& getPalette() const;

  virtual void handleEvent(TEvent& event) override;
  void showGeneralSettings();
  void handleCommand(TEvent& event);
  void handleBroadcast(TEvent& event);
  virtual void eventError(TEvent& event) override;
  virtual bool valid(ushort cmd) override;

  static TMenuBar* initMenuBar(TRect);
  static TStatusLine* initStatusLine(TRect);
  virtual void outOfMemory() override;
  virtual void getEvent(TEvent& event) override;
  virtual void idle() override;

private:
  void changeDir();

  void ShowAboutBox();

  int windowNumber_{ 0 };

  std::mutex idle_mu_;
};

#endif
