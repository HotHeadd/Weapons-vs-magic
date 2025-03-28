add_library(RenderManager)

target_include_directories(RenderManager PUBLIC include)

target_sources(RenderManager PRIVATE source/render_manager.cpp
                                     source/drawfuncs.cpp)

target_link_libraries(RenderManager PUBLIC Game 
Renderable GameState GTower GNodes TextureManager
TowerMenu TrapMenu InfoMenu
 sfml-graphics sfml-window sfml-system)