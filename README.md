> [!IMPORTANT]
>  This is an unofficial Project, this is just because i want to experiment with
>  Linux Desktop apps and i'nt a wtr Developer

# What is?

is a `wtr-lab` desktop client for novel readers (currently  only support spanish) for `Gnu/Linux` Distro

## deps

1. **cpr** - wrapper of libcurl
2. **libcurl** - for request
3. **fmt** - formater
4. **spdlog** - for logs
5. **wxWidgets** - GUI
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