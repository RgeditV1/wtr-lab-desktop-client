> [!IMPORTANT]
>  This is an unofficial Project, this is just because i want to experiment with
>  Linux Desktop apps and i'nt a wtr Developer

# What is?

is a `wtr-lab` desktop client for novel readers (currently  only support spanish) for `Gnu/Linux` Distro

## deps

> [!NOTE]
>qt6 is needed, but isnt include with vcpkg, cause it take a long time to install
>so make sure to install it with your package manager

1. **cpr** - wrapper of libcurl
2. **libcurl** - for request
3. **fmt** - formater
4. **spdlog** - for logs
5. **wxwidgets** - GUI
6. **WebView** - html5 UI

## Build

```bash
git submodule update --init --recursive
```

### Cmake Preset
```bash
cmake --preset wtr-release

cmake --build --preset release
```