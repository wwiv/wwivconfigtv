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

#define Uses_MsgBox
#define Uses_TApplication
#define Uses_TButton
#define Uses_TChDirDialog
#define Uses_TCheckBoxes
#define Uses_TDeskTop
#define Uses_TDialog
#define Uses_TEditor
#define Uses_TEditWindow
#define Uses_TFileDialog
#define Uses_TFileEditor
#define Uses_THistory
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TLabel
#define Uses_TMenuBar
#define Uses_TMenuItem
#define Uses_TObject
#define Uses_TPoint
#define Uses_TProgram
#define Uses_TRect
#define Uses_TSItem
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TStatusLine
#define Uses_TSubMenu

#include <chrono>
#include <fstream>
#include "tvision/tv.h"
#include "tvwcommon/form.h"
#include "tvwcommon/inputline.h"
#include "fmt/format.h"
#include "app.h"
#include "commands.h"
#include "menu.h"



TMenuBar *ConfigApp::initMenuBar(TRect r) { 
  return CreateMenuBar(r); 
}

TStatusLine *ConfigApp::initStatusLine(TRect r) {
  return CreateStatusLine(r);
}

void ConfigApp::outOfMemory() {
  messageBox("Not enough memory for this operation.", mfError | mfOKButton);
}

void ConfigApp::getEvent(TEvent& event) {

  TApplication::getEvent(event);
}

void ConfigApp::idle() { 
  TApplication::idle(); 
}




ConfigApp::ConfigApp(int argc, char **argv)
    : TProgInit(ConfigApp::initStatusLine, ConfigApp::initMenuBar,
                ConfigApp::initDeskTop),
      TApplication() {
  cascade();
}

ConfigApp::~ConfigApp() { 
}


void ConfigApp::changeDir() { executeDialog(new TChDirDialog(cdNormal, 0), 0); }

void ConfigApp::handleEvent(TEvent &event) {
  TApplication::handleEvent(event);
  switch (event.what) { 
  case evCommand:
    handleCommand(event);
    break;
  case evBroadcast:
    handleBroadcast(event);
    break;
  }
}

void ConfigApp::showGeneralSettings() {
  std::string sysname, sysphone, sysopname, systempw;
  int port;
  TFormColumn c(8, 30, TFormColumn::LabelPosition::left);
  c.add("System name:", new TFormInputLine(&sysname, 60));
  c.add("Sysop name:", new TFormInputLine(&sysopname, 60));
  c.add("System phone:", new TFormInputLine(&sysphone, 12));
  c.add("System pw:", new TFormInputLine(&systempw, 60));
  TForm form(&c);
  form.addOKButton();
  if (auto o = form.createDialog("Settings")) {
    o.value()->options |= ofCentered;
    if (executeDialog(o.value()) == cmOK) {
      //saveSettings();
      return;
    }
  }
}

void ConfigApp::handleBroadcast(TEvent &event) {
  switch (event.message.command) { 
  default:
    return;
  }
  clearEvent(event);
}

void ConfigApp::handleCommand(TEvent &event) {
  switch (event.message.command) {

  case cmHelpAbout:
    ShowAboutBox();
    break;

  case cmGeneralSettings:
    showGeneralSettings();
    break;

  default:
    return;
  }
  clearEvent(event);
}

void ConfigApp::eventError(TEvent &event) {
  if (event.what == evBroadcast && event.message.command >= 100) {
    auto text = fmt::format("Event Error: cmd:{} data:{}\n",
                            event.message.command, event.message.infoLong);
#ifdef _WIN32
    OutputDebugString(text.c_str());
#endif
  }
}

bool ConfigApp::valid(ushort cmd) { 
  //if (cmd == cmQuit && debug_->attached()) {
  //  debug_->Detach();
  //}
  return TApplication::valid(cmd); 
}



void ConfigApp::ShowAboutBox() {
  TDialog *aboutBox = new TDialog(TRect(0, 0, 59, 11), "About");
  aboutBox->insert(new TStaticText(TRect(9, 2, 50, 7),
                                   "\003WWIVconfig\n\n"
                                   "\003Copyright (c) 2023\n\n"
                                   "\003WWIV Software Services"));

  aboutBox->insert(new TButton(TRect(24, 8, 35, 10), " OK", cmOK, bfDefault));
  aboutBox->options |= ofCentered;

  executeDialog(aboutBox);
}



