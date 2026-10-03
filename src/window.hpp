#pragma once
#include <wx/wx.h>
#include <wx/srchctrl.h>

namespace Widget {
    class Frame;
    class Panel;
}

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
       explicit Frame(const wxString& title);
    private:
        void buildToolBar();
        void buildSideBar(bool show = false);
        // Métodos para construir elementos individualmente
        void BuildToolBarItems(wxToolBar* toolBar);
        void BuildSideBarItems(wxBoxSizer* sidebarSizer);

        // Helpers
        wxBitmap LoadRescaledBitmap(const wxString& path, int width, int height);
        void CollapseSideBar();
        void SetupSearchBarEvents();
        void BindGlobalEvents();
        void toggleSideBar(wxCommandEvent& event);
        void OnTimer(wxTimerEvent& event);
        void OnSize(wxSizeEvent& event);

        // Acciones
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