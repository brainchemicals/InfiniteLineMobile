cmake_minimum_required(VERSION 3.6.0)

project(ILProj)

include_directories(

	"${PROJECT_SOURCE_DIR}/include"	"${PROJECT_SOURCE_DIR}/src")

file(GLOB SRCS

	"${PROJECT_SOURCE_DIR}/include/*"

	"${PROJECT_SOURCE_DIR}/src/*"

)

find_package(SDL2 REQUIRED)

find_package(SDL2_ttf REQUIRED)

find_package(SDL2_image REQUIRED)

add_executable(ILProj ${SRCS})

include_directories(ILProj ${SDL2_INCLUDE_DIRS})

target_include_directories(ILProj PUBLIC ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(ILProj ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
