# wtr-lab-desktop-client

> [!IMPORTANT]
>  This is an unofficial Project, this is just because i want to experiment with
>  Linux Desktop apps and i'nt a wtr Developer

is a `wtr-lab` desktop client for novel readers (currently  only support spanish) for `Gnu/Linux` Distro

## deps

1. **vcpkg** - lib manager
2. **cpr** - wrapper of libcurl
3. **libcurl** - for request
4. **fmt** - formater
5. **spdlog** - for logs
5. **QT6/qtbase** - GUI

## Build

first of all, make sure youre using Microsoft [vcpkg](https://github.com/microsoft/vcpkg)

`Github Cli`
```bash
cd $HOME
gh repo clone microsoft/vcpkg -- --depth 1 && cd ~/vcpkg &&
./bootstrap-vcpkg.sh && ./vcpkg integrate install
```

`git`
```bash
cd $HOME
git clone https://github.com/microsoft/vcpkg.git --depth 1 && cd ~/vcpkg &&
./bootstrap-vcpkg.sh && ./vcpkg integrate install
```

### Cmake Preset
```bash
cmake --preset wtr-release

cmake --build --preset release
```