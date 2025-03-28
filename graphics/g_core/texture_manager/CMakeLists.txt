add_library(TextureManager SHARED)

target_include_directories(TextureManager PUBLIC include)

target_sources(TextureManager PRIVATE source/texture_manager.cpp)