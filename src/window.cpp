#include "window.hpp"
#include <vector>


Widget::Frame::Frame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1080, 720))
{
    wxInitAllImageHandlers(); // Load Img Files
    buildToolBar();
}

void Widget::Frame::buildToolBar()
{
    wxToolBar* toolBar = CreateToolBar(wxTB_HORIZONTAL | wxTB_HORZ_TEXT);

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
                    if(item.id > ID_HOME_BUTTON) {
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
}

bool App::Window::OnInit()
{
    m_frame = new Widget::Frame("WTR-LAB");
    m_frame->Show(true);
    return true;
}

