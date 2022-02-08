cmake_minimum_required(VERSION 3.16)
project(SistemaSolar)

# os arquivos devem estar na pasta do compilador
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_C_STANDARD 99)

add_executable(SistemaSolar main.c main.h utils.c utils.h planeta.c planeta.h textura.c textura.h musica.cpp)
target_link_libraries(SistemaSolar ${OPENGL_LIBRARIES})
target_link_libraries(SistemaSolar ${GLUT_LIBRARIES})
target_link_libraries(SistemaSolar -lSOIL -lfreeglut -lopengl32 -g)
target_link_libraries(SistemaSolar irrKlang.a)