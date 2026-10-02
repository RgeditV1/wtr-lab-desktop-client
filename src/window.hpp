#pragma once
#include <wx/wx.h>
#include <wx/srchctrl.h>
#include <string>

namespace Widget {
    class Frame;
    class Panel;
}

// ids
enum ID {
    /*
    * PARA FINES DE ANIMACION DE SIDEBAR
    */
    ID_SIDEBAR_BTN_CLOSE = 1001,
    ID_ANIM_TIMER = 1002,
    //--------------------------
    ID_MENU_BUTTON = 2000,
    ID_HOME_BUTTON = 2001,
    ID_SEARCH_BAR = 2002,
    ID_LIBRARY_BUTTON = 2003,
    ID_NOVELS_BUTTON = 2004,
    ID_RANKING_BUTTON = 2005,
    ID_LADERBOARD_BUTTON = 2006,
    ID_PROFILE_BUTTON = 2007,
};

// tipo de item
enum class ToolType {
    Button,
    Separator,
    StretchSpace,
    SearchCtrl
};

// toolbar items
struct ToolItem {
    ToolType type = ToolType::Button;
    ID id;
    std::string label = "";
    std::string imagePath ="";
    std::string tooltip = "";
};

namespace App {
    class Window : public wxApp {
    public:
        virtual bool OnInit() override;
    private:
        Widget::Frame* m_frame = nullptr;
    };
}

namespace Widget {
    class Frame : public wxFrame {
    public:
        Frame(const wxString& title);
    private:
        void buildToolBar();
        void buildSideBar(bool show = false);
        void CollapseSideBar();

        void is_sideBarVisible(wxCommandEvent& event);
        void OnTimer(wxTimerEvent& event);
        void OnSize(wxSizeEvent& event);
        void searchBar(wxCommandEvent& event);
        void homeButton(wxCommandEvent& event);
        void menuButton(wxCommandEvent& event);

        wxSearchCtrl* m_searchBar = nullptr;

        wxPanel* m_sideBar = nullptr;
        wxButton* m_btnClose = nullptr;
        wxTimer m_animTimer;

        bool m_isExpanded = false;
        int m_currentWidth = 0;

        const int SIDEBAR_MAX_WIDTH = 250;
        const int ANIM_SPEED = 15;
    };
}