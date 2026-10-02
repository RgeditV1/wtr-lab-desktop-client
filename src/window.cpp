#include "window.hpp"
#include <vector>


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
    
    // Color oscuro para la Toolbar
    toolBar->SetBackgroundColour(wxColour(37, 37, 38));

    /*
    * ESTA FUE LA MANERA MAS FACIL QUE SE ME OCURRIO PARA BUILDEAR LA TOOLBAR
    * YA QUE ERA MUY CANSADO IR UNO POR UNO Y ASIGNARLES SU DEBIDO ESPACIO
    * SI ENCUENTRAS UNA MANERA MEJOR, AVISAME, YA QUE SI ESTOS BOTONES NO ENCUENTRAN SUS \
    * ASSETS, LOS BOTONES QUE INCLUYAN ASSETS NO SE MOSTRARAN ._.
    * PERO BUENO, INTUYO QUE NINGUNA PERSONA NORMAL BORRARIA LOS ASSETS DEL PROGRAMA, VERDAD?
    */
    std::vector<ToolItem> tools = {
        { ToolType::Button, ID_MENU_BUTTON, "", "assets/menu.png", "Menú lateral" },
        { ToolType::Button, ID_HOME_BUTTON, "WTR-LAB", "assets/wtr-lab.png", "Ir a inicio" },
        { ToolType::Separator },
        { ToolType::SearchCtrl },
        { ToolType::StretchSpace },
        { ToolType::Button, ID_LIBRARY_BUTTON, "Biblioteca", "assets/book-mark.png", "" },
        { ToolType::Button, ID_NOVELS_BUTTON, "Novelas", "assets/bookshelf.png", "" },
        { ToolType::Button, ID_RANKING_BUTTON, "Ranking", "assets/ranking.png", "" },
        { ToolType::Button, ID_LADERBOARD_BUTTON, "Tabla de Clasificacion", "assets/laderboard.png", "" },
        { ToolType::Button, ID_PROFILE_BUTTON, "", "assets/login.png", "Mi perfil" }
    };

    for (const auto& item : tools) {
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
                    if(item.id > ID_HOME_BUTTON) {
                        img.Rescale(24, 24, wxIMAGE_QUALITY_HIGH);
                        // the icon is very small, so rescale it to 32x32
                        // may not very useful
                    } else if (item.id == ID_NOVELS_BUTTON) {
                        img.Rescale(32, 32, wxIMAGE_QUALITY_HIGH);
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

    /*
    * ESPACIO PARA EL BINDING
    */
    m_searchBar->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent& event) {
        CollapseSideBar();
        event.Skip();
    });

    m_searchBar->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event) {
        CollapseSideBar();
        this->SetFocus();
        event.Skip();
    });

    Bind(wxEVT_MENU, &Widget::Frame::is_sideBarVisible, this, ID_MENU_BUTTON);
    Bind(wxEVT_BUTTON, &Widget::Frame::is_sideBarVisible, this, ID_SIDEBAR_BTN_CLOSE);
    Bind(wxEVT_TIMER, &Widget::Frame::OnTimer, this, ID_ANIM_TIMER);
    Bind(wxEVT_SIZE, &Widget::Frame::OnSize, this);

    m_animTimer.SetOwner(this, ID_ANIM_TIMER);

}

void Widget::Frame::buildSideBar(bool show) {
    if (!m_sideBar) {
        m_sideBar = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED | wxTAB_TRAVERSAL);
        m_sideBar->SetBackgroundColour(wxColour(45, 45, 48));

        m_btnClose = new wxButton(
            m_sideBar, 
            ID_SIDEBAR_BTN_CLOSE, 
            "X", 
            wxDefaultPosition, 
            wxDefaultSize, 
            wxBU_EXACTFIT | wxBORDER_NONE
        );
        m_btnClose->SetForegroundColour(*wxWHITE);

        wxStaticText *label = new wxStaticText(
            m_sideBar, wxID_ANY, "WTR-LAB", 
            wxDefaultPosition, wxDefaultSize, 
            wxALIGN_LEFT
        );
        label->SetForegroundColour(*wxWHITE);
        wxFont font = label->GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        label->SetFont(font);
        
        wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
        headerSizer->Add(label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
        headerSizer->Add(m_btnClose, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT | wxTOP | wxBOTTOM, 5);

        // Sizer Vertical Principal del Sidebar
        wxBoxSizer* sidebarSizer = new wxBoxSizer(wxVERTICAL);
        sidebarSizer->Add(headerSizer, 0, wxEXPAND);

        m_sideBar->SetSizer(sidebarSizer);
    }

    m_isExpanded = show;
    m_currentWidth = show ? SIDEBAR_MAX_WIDTH : 0;

    wxSize FrameSize = GetClientSize();
    m_sideBar->SetSize(0, 0, m_currentWidth, FrameSize.GetHeight());
    m_sideBar->Show(show);
    m_sideBar->Raise();
}

void Widget::Frame::is_sideBarVisible(wxCommandEvent& event) {
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

