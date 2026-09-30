> [!IMPORTANT]
>  This is an unofficial Project, this is just because i want to experiment with
>  Linux Desktop apps and i'nt a wtr Developer

# What is?

is a `wtr-lab` desktop client for novel readers (currently  only support spanish) for `Gnu/Linux` Distro

## deps

> [!NOTE]
>qt6 is needed, but isnt include with vcpkg, cause it take a long time to install
>so make sure to install it with your package manager

1. **vcpkg** - lib manager
2. **cpr** - wrapper of libcurl
3. **libcurl** - for request
4. **fmt** - formater
5. **spdlog** - for logs
5. **QT6/qtbase** - GUI

## Build

first of all, make sure youre using Microsoft [vcpkg](https://github.com/microsoft/vcpkg)

### prepare the vcpkg submodule

```bash
git submodule update --init --recursive
./vcpkg/bootstrap-vcpkg.sh && ./vcpkg/vcpkg integrate install
```

### Cmake Preset
```bash
cmake --preset wtr-release

cmake --build --preset release
```