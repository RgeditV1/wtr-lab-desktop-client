#pragma once
#include <vector>
#include "window.hpp"

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