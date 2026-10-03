#include "window.hpp"
#include "toolbar_items.hpp"


Widget::Frame::Frame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1080, 720))
{
    SetBackgroundColour(wxColour(30, 30, 30)); // #1E1E1E

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);
    
    wxInitAllImageHandlers(); // Load Img Files
    buildToolBar();
}

void Widget::Frame::buildToolBar()
{
    wxToolBar* toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_HORZ_TEXT);
    toolBar->SetBackgroundColour(wxColour(37, 37, 38));

    for (const auto& item : Config::TOOLBAR_ITEMS) {
        switch (item.type) {
            case ToolType::Button: {
                wxImage img(item.imagePath, wxBITMAP_TYPE_PNG);
                if (img.IsOk()) {
                    if (item.id != ID_MENU_BUTTON) {
                        Bind(wxEVT_TOOL, [this](wxCommandEvent& event) {
                            CollapseSideBar();
                            this->SetFocus();
                            event.Skip();
                        }, item.id);
                    }
                    if (item.id > ID_HOME_BUTTON) {
                        img.Rescale(24, 24, wxIMAGE_QUALITY_HIGH);
                    } else {
                        img.Rescale(32, 32, wxIMAGE_QUALITY_HIGH);
                    }
                    toolBar->AddTool(item.id, item.label, wxBitmap(img), item.tooltip);
                }
                break;
            }
            case ToolType::Separator: {
                toolBar->AddSeparator();
                break;
            }
            case ToolType::StretchSpace: {
                toolBar->AddStretchableSpace();
                break;
            }
            case ToolType::SearchCtrl: {
                m_searchBar = new wxSearchCtrl(toolBar, ID_SEARCH_BAR, "", wxDefaultPosition, wxSize(200, -1));
                m_searchBar->SetDescriptiveText("Buscar...");
                toolBar->AddControl(m_searchBar);
                break;
            }
        }
    }

    toolBar->Realize();
    GetSizer()->Add(toolBar, 0, wxEXPAND);

    buildSideBar(false);

    if (m_searchBar != nullptr) {
        m_searchBar->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent& event) {
            CollapseSideBar();
            event.Skip();
        });

        m_searchBar->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event) {
            CollapseSideBar();
            this->SetFocus();
            event.Skip();
        });
    }

    Bind(wxEVT_MENU, &Widget::Frame::toggleSideBar, this, ID_MENU_BUTTON);
    Bind(wxEVT_BUTTON, &Widget::Frame::toggleSideBar, this, ID_SIDEBAR_BTN_CLOSE);
    Bind(wxEVT_TIMER, &Widget::Frame::OnTimer, this, ID_ANIM_TIMER);
    Bind(wxEVT_SIZE, &Widget::Frame::OnSize, this);

    m_animTimer.SetOwner(this, ID_ANIM_TIMER);
}

void Widget::Frame::buildSideBar(bool show) {
    if (!m_sideBar) {
        m_sideBar = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED | wxTAB_TRAVERSAL);
        m_sideBar->SetBackgroundColour(wxColour(45, 45, 48));
        wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer* sidebarSizer = new wxBoxSizer(wxVERTICAL);
        wxStaticText *label = new wxStaticText(m_sideBar, wxID_ANY, "WTR-LAB", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
        label->SetForegroundColour(*wxWHITE);
        wxFont font = label->GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        label->SetFont(font);
        headerSizer->Add(label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        wxImage imgClose("assets/close.png", wxBITMAP_TYPE_PNG);
        if (imgClose.IsOk()) {
            imgClose.Rescale(20, 20, wxIMAGE_QUALITY_HIGH);
            wxStaticBitmap* closeIcon = new wxStaticBitmap(m_sideBar, ID_SIDEBAR_BTN_CLOSE, wxBitmap(imgClose));
            closeIcon->SetCursor(wxCursor(wxCURSOR_HAND));
            closeIcon->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event) {
                CollapseSideBar();
                this->SetFocus();
            });
            headerSizer->Add(closeIcon, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT | wxTOP | wxBOTTOM, 5);
        }
        sidebarSizer->Add(headerSizer, 0, wxEXPAND);
        for (const auto& item : Config::SIDEBAR_ITEMS) {
            switch (item.type) {
                case ToolType::Button: {
                    wxImage img(item.imagePath, wxBITMAP_TYPE_PNG);
                    if (img.IsOk()) {
                        img.Rescale(24, 24, wxIMAGE_QUALITY_HIGH);
                        wxBitmap bitmap(img);
                        wxButton* button = new wxButton(m_sideBar, item.id, item.label, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBORDER_NONE);
                        button->SetBitmap(bitmap);
                        button->SetBackgroundColour(wxColour(45, 45, 48));
                        button->SetForegroundColour(*wxWHITE);
                        button->SetToolTip(item.tooltip);
                        sidebarSizer->Add(button, 0, wxEXPAND | wxALL, 5);
                        Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
                            CollapseSideBar();
                            this->SetFocus();
                            event.Skip();
                        }, item.id);
                    }
                    break;
                }
                case ToolType::Separator: {
                    sidebarSizer->AddSpacer(5);
                }
                default:
                    break;
            }
        }
        m_sideBar->SetSizer(sidebarSizer);
    }
    m_isExpanded = show;
    m_currentWidth = show ? SIDEBAR_MAX_WIDTH : 0;
    wxSize FrameSize = GetClientSize();
    m_sideBar->SetSize(0, 0, m_currentWidth, FrameSize.GetHeight());
    m_sideBar->Show(show);
    m_sideBar->Raise();
}

void Widget::Frame::toggleSideBar(wxCommandEvent& event) {
    if (!m_animTimer.IsRunning()) {
        m_sideBar->Show(true);
        m_sideBar->Raise();
        m_animTimer.Start(16); // ~60 FPS
    }
}

void Widget::Frame::OnTimer(wxTimerEvent& event) {
    if (m_isExpanded) {
        m_currentWidth -= ANIM_SPEED;
        if (m_currentWidth <= 0) {
            m_currentWidth = 0;
            m_isExpanded = false;
            m_sideBar->Show(false);
            m_animTimer.Stop();
        }
    } else {
        m_currentWidth += ANIM_SPEED;
        if (m_currentWidth >= SIDEBAR_MAX_WIDTH) {
            m_currentWidth = SIDEBAR_MAX_WIDTH;
            m_isExpanded = true;
            m_animTimer.Stop();

            m_sideBar->SetFocus();
        }
    }

    wxSize FrameSize = GetClientSize();
    m_sideBar->SetSize(0, 0, m_currentWidth, FrameSize.GetHeight());
    m_sideBar->Layout();
    m_sideBar->Refresh();
}

void Widget::Frame::OnSize(wxSizeEvent& event) {
    event.Skip(); // Permitir que el Frame procese el evento normalmente

    // Reajustar la altura y asegurar que el sidebar siga al frente al redimensionar
    if (m_sideBar && m_sideBar->IsShown()) {
        wxSize FrameSize = GetClientSize();
        m_sideBar->SetSize(0, 0, m_currentWidth, FrameSize.GetHeight());
        m_sideBar->Raise();
    }
}

void Widget::Frame::CollapseSideBar() {
    if (m_isExpanded && !m_animTimer.IsRunning()) {
        m_animTimer.Start(16);
    }
}

bool App::Window::OnInit()
{
    m_frame = new Widget::Frame("WTR-LAB");
    m_frame->Show(true);
    return true;
}