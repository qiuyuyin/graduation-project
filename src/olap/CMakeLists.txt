PROJECT(miniolap)
MESSAGE("Begin to build " ${PROJECT_NAME})
MESSAGE(STATUS "This is PROJECT_BINARY_DIR dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is PROJECT_SOURCE_DIR dir " ${PROJECT_SOURCE_DIR})


#INCLUDE_DIRECTORIES([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)
INCLUDE_DIRECTORIES(. ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../../deps ${PROJECT_SOURCE_DIR}/../observer /usr/local/include SYSTEM)
# 父cmake 设置的include_directories 和link_directories并不传导到子cmake里面
#INCLUDE_DIRECTORIES(BEFORE ${CMAKE_INSTALL_PREFIX}/include)
LINK_DIRECTORIES(/usr/local/lib ${PROJECT_BINARY_DIR}/../../lib)


FILE(GLOB_RECURSE ALL_SRC *.cpp *.c)
FILE(GLOB MAIN_SRC main.cpp)
MESSAGE("MAIN SRC: " ${MAIN_SRC})
FOREACH (F ${ALL_SRC})

    IF (NOT ${F} STREQUAL ${MAIN_SRC})
        SET(LIB_SRC ${LIB_SRC} ${F})
    ENDIF()

    MESSAGE("Use " ${F})

ENDFOREACH (F)

SET(LIBRARIES common pthread dl observer_static zstd)

# 指定目标文件位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin)
MESSAGE("Binary directory:" ${EXECUTABLE_OUTPUT_PATH})
ADD_EXECUTABLE(${PROJECT_NAME} ${ALL_SRC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)
MESSAGE("Archive directory:" ${LIBRARY_OUTPUT_PATH})
ADD_LIBRARY(${PROJECT_NAME}_static STATIC ${LIB_SRC})
SET_TARGET_PROPERTIES(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_static ${LIBRARIES})


# Target 必须在定义 ADD_EXECUTABLE 之后， programs 不受这个限制
# TARGETS和PROGRAMS 的默认权限是OWNER_EXECUTE, GROUP_EXECUTE, 和WORLD_EXECUTE，即755权限， programs 都是处理脚本类
# 类型分为RUNTIME／LIBRARY／ARCHIVE, prog
INSTALL(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static 
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib)


# ADD_EXECUTABLE(miniolap)
# MESSAGE("Begin to build " miniolap)

# INCLUDE(CheckIncludeFiles)

# #INCLUDE_DIRECTORIES([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)
# TARGET_INCLUDE_DIRECTORIES(miniolap PRIVATE . ${PROJECT_SOURCE_DIR}/../deps ${PROJECT_SOURCE_DIR}/../src/observer /usr/local/include /usr/include)
# # 父cmake 设置的include_directories 和link_directories并不传导到子cmake里面
# #INCLUDE_DIRECTORIES(BEFORE ${CMAKE_INSTALL_PREFIX}/include)

# TARGET_LINK_DIRECTORIES(miniolap PRIVATE /usr/local/lib ${PROJECT_BINARY_DIR}/../../lib)

# # stdio.h 必须放在readline/readline.h 前面，因为readline头文件不能直接单独编译
# CHECK_INCLUDE_FILES("stdio.h;readline/readline.h" HAVE_READLINE_HEADER)

# FIND_LIBRARY(READLINE_LIBRARY readline)
# IF (HAVE_READLINE_HEADER AND READLINE_LIBRARY)
#     TARGET_LINK_LIBRARIES(miniolap ${READLINE_LIBRARY})
#     ADD_DEFINITIONS(-DUSE_READLINE)
# ELSE ()
#     MESSAGE ("readline is not found")
# ENDIF()

# FILE(GLOB_RECURSE ALL_SRC *.cpp)
# FOREACH (F ${ALL_SRC})

#     SET(PRJ_SRC ${PRJ_SRC} ${F})
#     MESSAGE("Use " ${F})

# ENDFOREACH (F)


# FILE(GLOB_RECURSE ALL_SRC *.cpp *.c)
# FILE(GLOB MAIN_SRC main.cpp)
# MESSAGE("MAIN SRC: " ${MAIN_SRC})
# FOREACH (F ${ALL_SRC})

#     IF (NOT ${F} STREQUAL ${MAIN_SRC})
#         SET(LIB_SRC ${LIB_SRC} ${F})
#     ENDIF()

#     MESSAGE("Use " ${F})

# ENDFOREACH (F)

# # 指定目标文件位置
# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
# MESSAGE("Binary directory:" ${EXECUTABLE_OUTPUT_PATH})
# TARGET_SOURCES(miniolap PRIVATE ${PRJ_SRC})
# TARGET_LINK_LIBRARIES(miniolap common pthread dl observer_static zstd)

# SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)
# MESSAGE("Archive directory:" ${LIBRARY_OUTPUT_PATH})
# ADD_LIBRARY(miniolap_static STATIC ${LIB_SRC})
# SET_TARGET_PROPERTIES(miniolap_static PROPERTIES OUTPUT_NAME miniolap)
# TARGET_LINK_LIBRARIES(miniolap_static common pthread dl observer_static zstd)


# # Target 必须在定义 ADD_EXECUTABLE 之后， programs 不受这个限制
# # TARGETS和PROGRAMS 的默认权限是OWNER_EXECUTE, GROUP_EXECUTE, 和WORLD_EXECUTE，即755权限， programs 都是处理脚步类
# # 类型分为RUNTIME／LIBRARY／ARCHIVE, prog
# INSTALL(TARGETS miniolap miniolap_static 
#     RUNTIME DESTINATION bin
#     ARCHIVE DESTINATION lib)
