//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#include "PluginDefinition.h"
#include "common\statics.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
static const TCHAR* txtAbout = TEXT("About");

class CEditor;
extern CEditor* g_editor;

void about(){
	/*
		If we had dockable visible at last closing of N++, tries N++ to create it at next start 
		by sending this command. Because we dont have special menu entry uses DockableDialog the same
		MenuCmdId while registering of new dockable dialog instances.

		g_editor == NULL helps us to detect this issue :-)
	*/

	if (g_editor == NULL)
		return;

	TCHAR buf[1024];
	int r = LoadString(Statics::instance().hInstance, 1, buf, sizeof(buf));
	MessageBox(nppData._nppHandle, buf, txtAbout, MB_OK|MB_ICONINFORMATION);
}

//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index,const TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}



//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
//	mysite->Release();
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(0, txtAbout, about, NULL, false);
}



//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}
