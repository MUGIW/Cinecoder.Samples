project (Daniel2_SimplePlayerGL)

find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT   REQUIRED)
find_package(GLEW   REQUIRED)
find_package(OpenCL REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	stdafx.cpp
	AudioSource.cpp
	Block.cpp
	DecodeDaniel2.cpp
	ReadFileDN2.cpp
	Daniel2.SimplePlayerGL.cpp
)

set(HEADERS
	stdafx.h
	AudioSource.h
	Block.h
	CinecoderErrorHandler.h
	cudaDefines.h
	DecodeDaniel2.h
	ReadFileDN2.h
)

include_directories("../common")
include_directories("${Cinecoder_INCLUDE_DIRS}")
link_directories("${Cinecoder_LIBRARY_DIRS}")

if(CUDAConvertLib_FOUND)
include_directories("${CUDAConvertLib_INCLUDE_DIRS}")
link_directories("${CUDAConvertLib_LIBRARY_DIRS}")
endif()

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

if (OpenCL_FOUND)
    include_directories(${OPENCL_INCLUDE_DIRS})
endif()

add_compile_options("-D__CINECODER_DISABLE_PRINT_VERSION__")

if(APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path")
else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Cinecoder_LIBRARIES} ${OPENGL_LIBRARY} ${OPENAL_LIBRARY} ${GLUT_LIBRARY} pthread dl)

if(CUDAConvertLib_FOUND)
target_link_libraries(${PROJECT_NAME} ${CUDAConvertLib_LIBRARIES})
endif()

if(UNIX AND NOT APPLE)
target_link_libraries(${PROJECT_NAME} X11)
endif()

if (OpenCL_FOUND)
    target_link_libraries(${PROJECT_NAME} OpenCL)
endif()
