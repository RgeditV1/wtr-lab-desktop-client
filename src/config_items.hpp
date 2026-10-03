#pragma once
#include <vector>
#include <string>
#include <cstddef>



namespace Config {

        // ids
    enum ID : size_t {
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

    /*
    * ALGUNAS PROPIEDADES EXCLUSIVAS DE LA SIDEBAR
    */
    enum SIDEBAR : size_t {
        SIDEBAR_MAX_WIDTH = 250,
        SIDEBAR_MIN_WIDTH = 48,
        SIDEBAR_ANIM_SPEED = 15
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
        ID id = static_cast<ID>(0);
        size_t iconSize;
        std::string label = "";
        std::string imagePath ="";
        std::string tooltip = "";
    };
    inline const std::vector<ToolItem> TOOLBAR_ITEMS = {
        { .type = ToolType::Button, .id = ID_MENU_BUTTON, .iconSize = 32, .imagePath = "assets/menu.png", .tooltip = "Menú lateral" },
        { .type = ToolType::Button, .id = ID_HOME_BUTTON, .iconSize = 32, .label = "WTR-LAB", .imagePath = "assets/wtr-lab.png", .tooltip = "Ir a inicio" },
        { .type = ToolType::Separator },
        { .type = ToolType::SearchCtrl },
        { .type = ToolType::StretchSpace },
        { .type = ToolType::Button, .id = ID_LIBRARY_BUTTON, .iconSize = 24, .label = "Biblioteca", .imagePath = "assets/book-mark.png", .tooltip = "" },
        { .type = ToolType::Button, .id = ID_NOVELS_BUTTON, .iconSize = 24, .label = "Novelas", .imagePath = "assets/bookshelf.png", .tooltip = "" },
        { .type = ToolType::Button, .id = ID_RANKING_BUTTON, .iconSize = 24, .label = "Clasificacion", .imagePath = "assets/ranking.png", .tooltip = "" },
        { .type = ToolType::Button, .id = ID_LADERBOARD_BUTTON, .iconSize = 24, .label = "Tabla de Clasificacion", .imagePath = "assets/laderboard.png", .tooltip = "" },
        { .type = ToolType::Button, .id = ID_PROFILE_BUTTON, .iconSize = 24, .label = "", .imagePath = "assets/login.png", .tooltip = "Mi perfil" }
    };

    inline const std::vector<ToolItem> SIDEBAR_ITEMS = {
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_HOME_BUTTON, .iconSize = 24, .label = "Inicio", .imagePath = "assets/home.png", .tooltip = "Ir a inicio" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_LIBRARY_BUTTON, .iconSize = 24, .label = "Biblioteca", .imagePath = "assets/book-mark.png", .tooltip = "" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_NOVELS_BUTTON, .iconSize = 24, .label = "Novelas", .imagePath = "assets/bookshelf.png", .tooltip = "" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_NOVEL_FINDER_BUTTON, .iconSize = 24, .label = "Buscador de Novelas", .imagePath = "assets/magnify.png", .tooltip = "" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_RANKING_BUTTON, .iconSize = 24, .label = "Clasificacion", .imagePath = "assets/ranking.png", .tooltip = "" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_LADERBOARD_BUTTON, .iconSize = 24, .label = "Tabla de Clasificacion", .imagePath = "assets/laderboard.png", .tooltip = "" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_TIER_LIST_BUTTON, .iconSize = 24, .label = "Tier List", .imagePath = "assets/chart-box-outline.png", .tooltip = "" },
        { .type = ToolType::Separator },
        { .type = ToolType::Button, .id = ID_FAQ_BUTTON, .iconSize = 24, .label = "Preguntas Frecuentes", .imagePath = "assets/faq.png", .tooltip = "" }
    };
}