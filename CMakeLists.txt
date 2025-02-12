cmake_minimum_required (VERSION 3.29)

project(LIE-ALG VERSION 0.1.0)

file(GLOB project_sources
 "*.cpp"
)

file(GLOB project_headers
 "*.h"
)

add_executable(${PROJECT_NAME} ${project_sources})

target_sources(${PROJECT_NAME} PRIVATE ${project_headers})