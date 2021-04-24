cmake_minimum_required(VERSION 3.17)

project(minishell)               # Create project "simple_example"

set(PATH ./srcs/)

include_directories(./includes/) 


AUX_SOURCE_DIRECTORY (${PATH} MY_SRCS)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES ${MY_SRCS} includes/minishell.h srcs/ft_redirect.c srcs/ft_export.c unnecessary_files/wwwwy.c srcs/mini_utils.c srcs/ft_redirect1.c)
set(CMAKE_C_FLAGS "-ltermcap")

LINK_DIRECTORIES(./)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(minishell ${SOURCE_FILES})
