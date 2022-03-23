cmake_minimum_required(VERSION 3.10)

project(wizard)

set(WIZARD_SRC
	wizard/ast/ast.cpp
)

add_library(wizard ${WIZARD_SRC})

target_include_directories(wizard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/wizard)

