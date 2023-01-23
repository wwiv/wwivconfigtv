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

/* ---------------------------------------------------------------------- */
/*      class TProgram                                                    */
/*                                                                        */
/*      Palette layout                                                    */
/*          1 = TBackground                                               */
/*       2- 7 = TMenuView and TStatusLine                                 */
/*       8-15 = TWindow(Blue)                                             */
/*      16-23 = TWindow(Cyan)                                             */
/*      24-31 = TWindow(Gray)                                             */
/*      32-63 = TDialog                                                   */
/* ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- */
/*      class TMenuView                                                   */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Normal text                                                 */
/*        2 = Disabled text                                               */
/*        3 = Shortcut text                                               */
/*        4 = Normal selection                                            */
/*        5 = Disabled selection                                          */
/*        6 = Shortcut selection                                          */
/* ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- */
/*      class TWindow                                                     */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Frame passive                                               */
/*        2 = Frame active                                                */
/*        3 = Frame icon                                                  */
/*        4 = ScrollBar page area                                         */
/*        5 = ScrollBar controls                                          */
/*        6 = Scroller normal text                                        */
/*        7 = Scroller selected text                                      */
/*        8 = Reserved                                                    */
/* ---------------------------------------------------------------------- */

#define cpWWIVAppColor \
       "\x03\x13\x18\x1E\x30\x38\x3E\x17\x1F\x1A\x08\x08\x0E\x01\x1F" \
    "\x37\x3F\x3A\x13\x13\x3E\x21\x3F\x70\x7F\x7A\x13\x13\x70\x7F\x7E" \
    "\x08\x09\x0A\x08\x0B\x03\x03\x0E\x0E\x20\x2B\x2F\x78\x2E\x08\x03" \
    "\x3F\x3E\x1F\x2F\x1A\x20\x72\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
    "\x17\x1F\x1A\x71\x71\x1E\x17\x1F\x1E\x20\x2B\x2F\x78\x2E\x10\x30" \
    "\x3F\x3E\x70\x2F\x7A\x20\x12\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
    "\x37\x3F\x3A\x13\x13\x3E\x30\x3F\x3E\x20\x2B\x2F\x78\x2E\x30\x70" \
    "\x7F\x7E\x1F\x2F\x1A\x20\x32\x31\x71\x70\x2F\x7E\x71\x13\x78\x00" \
    "\x37\x3F\x3A\x13\x13\x30\x3E\x1E"    // help colors

#define cpAppColor \
       "\x71\x70\x78\x74\x20\x28\x24\x17\x1F\x1A\x31\x31\x1E\x71\x1F" \
    "\x37\x3F\x3A\x13\x13\x3E\x21\x3F\x70\x7F\x7A\x13\x13\x70\x7F\x7E" \
    "\x70\x7F\x7A\x13\x13\x70\x70\x7F\x7E\x20\x2B\x2F\x78\x2E\x70\x30" \
    "\x3F\x3E\x1F\x2F\x1A\x20\x72\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
    "\x17\x1F\x1A\x71\x71\x1E\x17\x1F\x1E\x20\x2B\x2F\x78\x2E\x10\x30" \
    "\x3F\x3E\x70\x2F\x7A\x20\x12\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
    "\x37\x3F\x3A\x13\x13\x3E\x30\x3F\x3E\x20\x2B\x2F\x78\x2E\x30\x70" \
    "\x7F\x7E\x1F\x2F\x1A\x20\x32\x31\x71\x70\x2F\x7E\x71\x13\x78\x00" \
    "\x37\x3F\x3A\x13\x13\x30\x3E\x1E"    // help colors


TPalette& ConfigApp::getPalette() const
{
  static TPalette color(cpWWIVAppColor, sizeof(cpAppColor) - 1);
  static TPalette blackwhite(cpAppBlackWhite, sizeof(cpAppBlackWhite) - 1);
  static TPalette monochrome(cpAppMonochrome, sizeof(cpAppMonochrome) - 1);
  static TPalette* palettes[] =
  {
  &color,
  &blackwhite,
  &monochrome
  };
  return *(palettes[appPalette]);
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
  c.add("System phone:", new TFormInputLine(&sysphone, 13));
  c.add("System pw:", new TFormInputLine(&systempw, 60));
  TForm form(&c);
  form.addOKButton();
  c.set_ypad(0);
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
                                   "\003~WWIVconfig~\n\n"
                                   "\003Copyright (c) 2023\n\n"
                                   "\003WWIV Software Services"));

  aboutBox->insert(new TButton(TRect(24, 8, 35, 10), " OK", cmOK, bfDefault));
  aboutBox->options |= ofCentered;

  executeDialog(aboutBox);
}



