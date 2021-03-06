cmake_minimum_required(VERSION 3.1.0)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

project(ai_particle_swarm_optimization)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(
    include
    deps/muparser/include
)

# Headers
set(HEADERS_LIST
    include/parser.hpp
    include/particle_swarm_optimization_app.hpp
    include/particle_swarm_optimization_widget.hpp
)

# Sources
set(SOURCES_LIST
    src/main.cpp
    src/parser.cpp
    src/particle_swarm_optimization_app.cpp
    src/particle_swarm_optimization_widget.cpp
)

# Tell CMake to create the helloworld executable
add_executable(${PROJECT_NAME} ${SOURCES_LIST} ${HEADERS_LIST})

# Target for build muParser library
add_custom_target(
    muparser
    COMMAND ./configure --enable-shared=no
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/muparser
)
add_dependencies(${PROJECT_NAME} muparser)

# Link with muParser library
target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/muparser/lib/libmuparser.a
)

# Use the Widgets module from Qt 5
qt5_use_modules(${PROJECT_NAME} Widgets)
