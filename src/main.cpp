#include <fmt/base.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

int main(){
    fmt::print("Hola Mundo");
    spdlog::warn("Probando Warning");
    return 0;
}

