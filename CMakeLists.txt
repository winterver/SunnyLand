cmake_minimum_required(VERSION 4.1)
project(SunnyLand)

if(WIN32)
    add_compile_options(/wd4819)
    set(SDL_VULKAN          OFF)
    set(SDL_OPENGL          OFF)
    set(SDL_OPENGLES        OFF)
    set(SDL_RENDER_D3D12    OFF)
endif()
set(BUILD_SHARED_LIBS       OFF)
set(SDL_GPU                 OFF)
set(SDL_CAMERA              OFF)
set(SDL_JOYSTICK            OFF)
set(SDL_HAPTIC              OFF)
set(SDL_HIDAPI              OFF)
set(SDL_POWER               OFF)
set(SDL_SENSOR              OFF)
set(SDL_DIALOG              OFF)
set(SDL_DISKAUDIO           OFF)
set(SDL_DUMMYAUDIO          OFF)
set(SDL_DUMMYCAMERA         OFF)
set(SDL_DUMMYVIDEO          OFF)
set(SDL_OFFSCREEN           OFF)
set(SDL_RENDER_GPU          OFF)
set(SDL_TRAY                OFF)
set(SDL_VIRTUAL_JOYSTICK    OFF)
set(SDLTTF_HARFBUZZ         OFF)
set(SDLMIXER_VENDORED       OFF)
set(SDLMIXER_VORBIS_STB     OFF)
set(SDLMIXER_FLAC           OFF)
set(SDLMIXER_MIDI           OFF)
set(SDLMIXER_AIFF           OFF)
set(SDLMIXER_VOC            OFF)
set(SDLMIXER_AU             OFF)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_ttf)
add_subdirectory(vendor/SDL_mixer)

add_executable(
    SunnyLand
    main.cpp
)
target_link_libraries(
    SunnyLand PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)