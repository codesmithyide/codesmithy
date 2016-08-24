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

#include "Frame.h"
#include "Preferences/PreferencesDialog.h"
#include <wx/menu.h>

namespace CodeSmithy
{

Frame::Frame(const wxString& title,
             DocumentTypes& documentTypes)
    : wxFrame(NULL, wxID_ANY, title), m_appSettings(documentTypes)
{
    CreateMenuBar();
}

void Frame::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_PREFERENCES, "&Preferences...");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);
}

void Frame::OnPreferences(wxCommandEvent& evt)
{
    PreferencesDialog preferencesDialog(this, m_appSettings);
    preferencesDialog.ShowModal();
}

void Frame::OnExit(wxCommandEvent& evt)
{
    Close(true);
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_PREFERENCES, Frame::OnPreferences)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
wxEND_EVENT_TABLE()

}
