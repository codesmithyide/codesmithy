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
const wxWindowID WorkspaceCloseFileMenuID = WorkspaceSaveFileAsMenuID + 1;

const wxWindowID ProjectChoiceProjectRadioButtonID = WorkspaceCloseFileMenuID + 1;
const wxWindowID ProjectChoiceStandaloneButtonID = ProjectChoiceProjectRadioButtonID + 1;

const wxWindowID PreferencesCloseButtonID = ProjectChoiceStandaloneButtonID + 1;

const wxWindowID PreferencesDefaultEditorThemeChoiceID = PreferencesCloseButtonID + 1;
const wxWindowID PreferencesDefaultEditorOverrideThemeCheckBoxID = PreferencesDefaultEditorThemeChoiceID + 1;
const wxWindowID PreferencesDefaultEditorSizeSelectionButtonID = PreferencesDefaultEditorOverrideThemeCheckBoxID + 1;
const wxWindowID PreferencesDefaultEditorFontSelectionButtonID = PreferencesDefaultEditorSizeSelectionButtonID + 1;
const wxWindowID PreferencesDefaultEditorPreferencesApplyButtonID = PreferencesDefaultEditorFontSelectionButtonID + 1;

const wxWindowID PreferencesBakefileEditorUseDefaultSettingsCheckBoxID = PreferencesDefaultEditorPreferencesApplyButtonID + 1;
const wxWindowID PreferencesBakefileEditorSizeSelectionButtonID = PreferencesBakefileEditorUseDefaultSettingsCheckBoxID + 1;
const wxWindowID PreferencesBakefileEditorFontSelectionButtonID = PreferencesBakefileEditorSizeSelectionButtonID + 1;
const wxWindowID PreferencesBakefileEditorPreferencesApplyButtonID = PreferencesBakefileEditorFontSelectionButtonID + 1;

const wxWindowID PreferencesCppEditorUseDefaultSettingsCheckBoxID = PreferencesBakefileEditorPreferencesApplyButtonID + 1;
const wxWindowID PreferencesCppEditorSizeSelectionButtonID = PreferencesCppEditorUseDefaultSettingsCheckBoxID + 1;
const wxWindowID PreferencesCppEditorFontSelectionButtonID = PreferencesCppEditorSizeSelectionButtonID + 1;
const wxWindowID PreferencesCppEditorPreferencesApplyButtonID = PreferencesCppEditorFontSelectionButtonID + 1;

const wxWindowID PreferencesXMLEditorThemeChoiceID = PreferencesCppEditorPreferencesApplyButtonID + 1;
const wxWindowID PreferencesXMLEditorUseDefaultSettingsCheckBoxID = PreferencesXMLEditorThemeChoiceID + 1;
const wxWindowID PreferencesXMLEditorOverrideThemeCheckBoxID = PreferencesXMLEditorUseDefaultSettingsCheckBoxID + 1;
const wxWindowID PreferencesXMLEditorSizeSelectionButtonID = PreferencesXMLEditorOverrideThemeCheckBoxID + 1;
const wxWindowID PreferencesXMLEditorFontSelectionButtonID = PreferencesXMLEditorSizeSelectionButtonID + 1;
const wxWindowID PreferencesXMLEditorPreferencesApplyButtonID = PreferencesXMLEditorFontSelectionButtonID + 1;

const wxWindowID PreferencesStartupFixedSizeButtonID = PreferencesXMLEditorPreferencesApplyButtonID + 1;
const wxWindowID PreferencesStartupPreviousSizeButtonID = PreferencesStartupFixedSizeButtonID + 1;

const wxWindowID PreferencesFileTypeAssociationsApplyButtonID = PreferencesStartupPreviousSizeButtonID + 1;

}

#endif
