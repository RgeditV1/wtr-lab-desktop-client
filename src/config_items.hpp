#pragma once
#include <vector>
#include <string>

// ids
enum ID {
    /*
    * PARA FINES DE ANIMACION DE SIDEBAR
    */
    ID_SIDEBAR_BTN_CLOSE = 1001,
    ID_ANIM_TIMER = 1002,
    /*
    * BOTONES DE LA TOOLBAR
    */
    ID_MENU_BUTTON = 2000,
    ID_HOME_BUTTON = 2001,
    ID_SEARCH_BAR = 2002,
    ID_LIBRARY_BUTTON = 2003,
    ID_NOVELS_BUTTON = 2004,
    ID_RANKING_BUTTON = 2005,
    ID_LADERBOARD_BUTTON = 2006,
    ID_PROFILE_BUTTON = 2007,
    /*
    * BOTONES PROPIOS DE LA SIDEBAR
    */
    ID_NOVEL_FINDER_BUTTON = 2008,
    ID_TIER_LIST_BUTTON = 2009,
    ID_FAQ_BUTTON = 2010,
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

namespace Config {
    inline const std::vector<ToolItem> TOOLBAR_ITEMS = {
        { ToolType::Button, ID_MENU_BUTTON, "", "assets/menu.png", "Menú lateral" },
        { ToolType::Button, ID_HOME_BUTTON, "WTR-LAB", "assets/wtr-lab.png", "Ir a inicio" },
        { ToolType::Separator },
        { ToolType::SearchCtrl },
        { ToolType::StretchSpace },
        { ToolType::Button, ID_LIBRARY_BUTTON, "Biblioteca", "assets/book-mark.png", "" },
        { ToolType::Button, ID_NOVELS_BUTTON, "Novelas", "assets/bookshelf.png", "" },
        { ToolType::Button, ID_RANKING_BUTTON, "Clasificacion", "assets/ranking.png", "" },
        { ToolType::Button, ID_LADERBOARD_BUTTON, "Tabla de Clasificacion", "assets/laderboard.png", "" },
        { ToolType::Button, ID_PROFILE_BUTTON, "", "assets/login.png", "Mi perfil" }
    };

    inline const std::vector<ToolItem> SIDEBAR_ITEMS = {
        { ToolType::Separator },
        { ToolType::Button, ID_HOME_BUTTON, "Inicio", "assets/home.png", "Ir a inicio" },
        { ToolType::Separator },
        { ToolType::Button, ID_LIBRARY_BUTTON, "Biblioteca", "assets/book-mark.png", "" },
        { ToolType::Separator },
        { ToolType::Button, ID_NOVELS_BUTTON, "Novelas", "assets/bookshelf.png", "" },
        { ToolType::Separator },
        { ToolType::Button, ID_NOVEL_FINDER_BUTTON, "Buscador de Novelas", "assets/magnify.png", "" },
        { ToolType::Separator },
        { ToolType::Button, ID_RANKING_BUTTON, "Clasificacion", "assets/ranking.png", "" },
        { ToolType::Separator },
        { ToolType::Button, ID_LADERBOARD_BUTTON, "Tabla de Clasificacion", "assets/laderboard.png", "" },
        { ToolType::Separator },
        { ToolType::Button, ID_TIER_LIST_BUTTON, "Tier List", "assets/chart-box-outline.png", "" },
        { ToolType::Separator },
        { ToolType::Button, ID_FAQ_BUTTON, "Preguntas Frecuentes", "assets/faq.png", "" }
    };
}