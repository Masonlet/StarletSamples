cmake_minimum_required(VERSION 3.20)

# Config
set(SAMPLE_NAME starlet_samples)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")
set(ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

project(${SAMPLE_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_REGENERATION ON)

# Source files
file(GLOB_RECURSE SOURCES        CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS        CONFIGURE_DEPENDS ${INC_DIR}/starlet-samples/*.hpp)

# Asset files
file(GLOB_RECURSE ASSET_SHADERS  CONFIGURE_DEPENDS "${ASSET_DIR}/shaders/*")
file(GLOB_RECURSE ASSET_MODELS   CONFIGURE_DEPENDS "${ASSET_DIR}/models/*")
file(GLOB_RECURSE ASSET_SCENES   CONFIGURE_DEPENDS "${ASSET_DIR}/scenes/*")
file(GLOB_RECURSE ASSET_TEXTURES CONFIGURE_DEPENDS "${ASSET_DIR}/textures/*")

# Create executable
add_executable(${SAMPLE_NAME} ${SOURCES} ${HEADERS})

# Asset directory definition
file(TO_CMAKE_PATH "${ASSET_DIR}" ASSET_PATH)
target_compile_definitions(${SAMPLE_NAME} PRIVATE ASSET_DIR="${ASSET_PATH}")

target_include_directories(${SAMPLE_NAME} PUBLIC "${INC_DIR}")

# Fetch dependencies if not building locally
if(NOT BUILD_LOCAL)
    include(FetchContent)

    FetchContent_Declare(starlet_engine
      GIT_REPOSITORY https://github.com/starlet-libs/engine.git
      GIT_TAG main
    )
    FetchContent_Declare(starlet_math
      GIT_REPOSITORY https://github.com/starlet-libs/math.git
      GIT_TAG main
    )
    FetchContent_Declare(starlet_serializer 
      GIT_REPOSITORY https://github.com/starlet-libs/serializer.git
      GIT_TAG main
    )
    FetchContent_Declare(starlet_scene
      GIT_REPOSITORY https://github.com/starlet-libs/scene.git
      GIT_TAG main
    )
    FetchContent_Declare(starlet_graphics
      GIT_REPOSITORY https://github.com/starlet-libs/graphics.git
      GIT_TAG main
    )
    FetchContent_Declare(starlet_controls
      GIT_REPOSITORY https://github.com/starlet-libs/controls.git
      GIT_TAG main
    )

    FetchContent_MakeAvailable(
      starlet_engine
      starlet_math
      starlet_serializer
      starlet_scene
      starlet_graphics 
      starlet_controls
    )
endif()

target_link_libraries(${SAMPLE_NAME} 
  PRIVATE
    starlet_engine 
    starlet_math
    starlet_serializer 
    starlet_scene
    starlet_graphics 
    starlet_controls
)

# IDE organization
source_group(TREE ${SRC_DIR} PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE ${INC_DIR} PREFIX "Header Files" FILES ${HEADERS})

# IDE asset organization
add_custom_target(Assets SOURCES 
  ${ASSET_SHADERS} 
  ${ASSET_MODELS} 
  ${ASSET_SCENES} 
  ${ASSET_TEXTURES}
)
set_target_properties(Assets PROPERTIES FOLDER "Assets")
source_group("Assets\\Shaders"  FILES ${ASSET_SHADERS})
source_group("Assets\\Models"   FILES ${ASSET_MODELS})
source_group("Assets\\Scenes"   FILES ${ASSET_SCENES})
source_group("Assets\\Textures" FILES ${ASSET_TEXTURES})

# Output directories
set_target_properties(${SAMPLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${SAMPLE_NAME}>"
)

# IDE Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "External")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${SAMPLE_NAME})
