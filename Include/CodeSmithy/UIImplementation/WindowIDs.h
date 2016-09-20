/*
    Copyright (c) 2015-2016 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _CODESMITHY_UIIMPLEMENTATION_WINDOWIDS_H_
#define _CODESMITHY_UIIMPLEMENTATION_WINDOWIDS_H_

#include <wx/defs.h>

namespace CodeSmithy
{

const wxWindowID WorkspaceOpenFileMenuID = wxID_HIGHEST + 1;
const wxWindowID WorkspaceSaveFileMenuID = WorkspaceOpenFileMenuID + 1;
const wxWindowID WorkspaceSaveFileAsMenuID = WorkspaceSaveFileMenuID + 1;
const wxWindowID WorkspaceSaveAllMenuID = WorkspaceSaveFileAsMenuID + 1;
const wxWindowID WorkspaceCloseFileMenuID = WorkspaceSaveAllMenuID + 1;
const wxWindowID WorkspaceCloseAllMenuID = WorkspaceCloseFileMenuID + 1;

const wxWindowID ProjectChoiceProjectRadioButtonID = WorkspaceCloseAllMenuID + 1;
const wxWindowID ProjectChoiceStandaloneButtonID = ProjectChoiceProjectRadioButtonID + 1;

const wxWindowID PreferencesCloseButtonID = ProjectChoiceStandaloneButtonID + 1;

const wxWindowID PreferencesDefaultEditorThemeChoiceID = PreferencesCloseButtonID + 1;
const wxWindowID PreferencesDefaultEditorOverrideThemeCheckBoxID = PreferencesDefaultEditorThemeChoiceID + 1;
const wxWindowID PreferencesDefaultEditorSizeSelectionButtonID = PreferencesDefaultEditorOverrideThemeCheckBoxID + 1;
const wxWindowID PreferencesDefaultEditorFontSelectionButtonID = PreferencesDefaultEditorSizeSelectionButtonID + 1;
const wxWindowID PreferencesDefaultEditorPreferencesApplyButtonID = PreferencesDefaultEditorFontSelectionButtonID + 1;

const wxWindowID PreferencesBakefileEditorPreferencesApplyButtonID = PreferencesDefaultEditorPreferencesApplyButtonID + 1;

const wxWindowID PreferencesCppEditorPreferencesApplyButtonID = PreferencesBakefileEditorPreferencesApplyButtonID + 1;

const wxWindowID PreferencesXMLEditorPreferencesApplyButtonID = PreferencesCppEditorPreferencesApplyButtonID + 1;

const wxWindowID PreferencesStartupFixedSizeButtonID = PreferencesXMLEditorPreferencesApplyButtonID + 1;
const wxWindowID PreferencesStartupPreviousSizeButtonID = PreferencesStartupFixedSizeButtonID + 1;

const wxWindowID PreferencesFileTypeAssociationsApplyButtonID = PreferencesStartupPreviousSizeButtonID + 1;

const wxWindowID OpenDocumentsContextMenuSave = PreferencesFileTypeAssociationsApplyButtonID + 1;
const wxWindowID OpenDocumentsContextMenuClose = OpenDocumentsContextMenuSave + 1;
const wxWindowID OpenDocumentsContextMenuCloseAllDocuments = OpenDocumentsContextMenuClose + 1;
const wxWindowID OpenDocumentsContextMenuCloseAllOtherDocuments = OpenDocumentsContextMenuCloseAllDocuments + 1;
const wxWindowID OpenDocumentsContextMenuCopyFullPath = OpenDocumentsContextMenuCloseAllOtherDocuments + 1;
const wxWindowID OpenDocumentsContextMenuOpenFolder = OpenDocumentsContextMenuCopyFullPath + 1;
const wxWindowID OpenDocumentsContextMenuOpenPrompt = OpenDocumentsContextMenuOpenFolder + 1;

}

#endif
