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

#include "tvision/tv.h"
#include "commands.h"
#include <sstream>
#include <string>

TMenuBar *CreateMenuBar(TRect &r) {
  TSubMenu &menuFile =
      *new TSubMenu("~\360~", kbAltF) +
      *new TMenuItem("~C~hange dir...", cmChangeDrct, kbNoKey) +
      *new TMenuItem("~D~OS shell", cmDosShell, kbNoKey) + newLine() +
      *new TMenuItem("E~x~it", cmQuit, kbAltX, hcNoContext, "Alt-X") + newLine() +
      *new TMenuItem("~A~bout...", cmHelpAbout, kbNoKey);

  TSubMenu &menuEdit =
      *new TSubMenu("~E~dit", kbAltE) +
      *new TMenuItem("~U~ndo", cmUndo, kbCtrlZ, hcNoContext, "Ctrl-Z") +
      newLine() +
      *new TMenuItem("Cu~t~", cmCut, kbCtrlX, hcNoContext, "Ctrl-X") +
      *new TMenuItem("~C~opy", cmCopy, kbCtrlC, hcNoContext, "Ctrl-C") +
      *new TMenuItem("~P~aste", cmPaste, kbCtrlV, hcNoContext, "Ctrl-V") +
      newLine() + *new TMenuItem("~C~lear", cmClear, kbNoKey);

  TSubMenu &menuSystem =
      *new TSubMenu("~S~ettings", kbAltV) +
      *new TMenuItem("~G~eneral", cmGeneralSettings,kbNoKey) +
    *new TMenuItem("New User", cmViewVars, kbNoKey) +
    *new TMenuItem("Toggles", cmViewVars, kbNoKey) +
    *new TMenuItem("Ratios", cmViewVars, kbNoKey) +
    *new TMenuItem("Limits", cmViewVars, kbNoKey) +
    *new TMenuItem("Colors", cmViewVars, kbNoKey) +
    *new TMenuItem("Paths", cmViewStack, kbNoKey) +
    *new TMenuItem("Scripting", cmViewStack, kbNoKey) +
    *new TMenuItem("Sub/Dir Max", cmViewSource, kbNoKey);

  TSubMenu& menuSecurity =
    *new TSubMenu("~S~ecurity", kbAltV) +
    *new TMenuItem("Security Levels", cmViewVars, kbNoKey) +
    *new TMenuItem("Auto-Validation", cmViewVars, kbNoKey);
  
  TSubMenu& menuManagers =
    *new TSubMenu("~M~anager", kbAltV) +
    *new TMenuItem("Editors", cmViewVars, kbNoKey) +
    *new TMenuItem("Protocols", cmViewVars, kbNoKey) +
    *new TMenuItem("Archivers", cmViewVars, kbNoKey) +
    *new TMenuItem("Menus", cmViewVars, kbNoKey) +
    *new TMenuItem("Networks", cmViewVars, kbNoKey) +
    *new TMenuItem("Users", cmViewVars, kbNoKey);

  r.b.y = r.a.y + 1;
  return new TMenuBar(r, menuFile + menuEdit + menuSystem + menuSecurity + menuManagers);
}


TStatusLine *CreateStatusLine(TRect &r) {
  r.a.y = r.b.y - 1;
  return new TStatusLine(
      r, *new TStatusDef(0, 0xFFFF) + *new TStatusItem(0, kbAltX, cmQuit) +
             //*new TStatusItem("~F2~ Save", kbF2, cmSave) +
             //*new TStatusItem("~F3~ Open", kbF3, cmOpen) +
             *new TStatusItem("~Ctrl-W~ Close", kbAltF3, cmClose) +
             *new TStatusItem("~F5~ Zoom", kbF5, cmZoom) +
             //*new TStatusItem("~F6~ Next", kbF6, cmNext) +
             *new TStatusItem("~F10~ Menu", kbF10, cmMenu) +
             *new TStatusItem(0, kbShiftDel, cmCut) +
             *new TStatusItem(0, kbCtrlIns, cmCopy) +
             *new TStatusItem(0, kbShiftIns, cmPaste) +
             *new TStatusItem(0, kbCtrlF5, cmResize));

}

