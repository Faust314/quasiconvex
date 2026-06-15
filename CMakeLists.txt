#cmake_minimum_required(VERSION 3.16)
#cmake_policy(SET CMP0091 NEW)
#
#project(Quasiconvex)
#
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#        "src/*.cpp"
#)
#
#set(IS_MSVC_LIKE FALSE)
#
#if (MSVC)
#    set(IS_MSVC_LIKE TRUE)
#endif()
#
#if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
#    set(IS_MSVC_LIKE TRUE)
#endif()
#
#
## ============================================================
## Обычная быстрая версия
## ============================================================
#
#add_executable(quasiconvex
#        ${SOURCES}
#)
#
#if (IS_MSVC_LIKE)
#    target_compile_options(quasiconvex PRIVATE
#            /O2
#    )
#else()
#    target_compile_options(quasiconvex PRIVATE
#            -Ofast
#            -march=native
#    )
#
#    target_link_options(quasiconvex PRIVATE
#            -static
#    )
#endif()
#
#
## ============================================================
## Обычная debug-версия
## ============================================================
#
#add_executable(quasiconvex_debug
#        ${SOURCES}
#)
#
#if (IS_MSVC_LIKE)
#    target_compile_options(quasiconvex_debug PRIVATE
#            /Zi
#            /Od
#            /Ob0
#            /UNDEBUG
#    )
#
#    target_link_options(quasiconvex_debug PRIVATE
#            /DEBUG
#    )
#
#    target_compile_definitions(quasiconvex_debug PRIVATE
#            _DEBUG
#    )
#
#    set_property(TARGET quasiconvex_debug PROPERTY
#            MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL"
#    )
#else()
#    target_compile_options(quasiconvex_debug PRIVATE
#            -g3
#            -ggdb3
#            -O0
#            -fno-omit-frame-pointer
#            -fno-inline
#            -fno-inline-functions
#            -fno-optimize-sibling-calls
#            -fno-eliminate-unused-debug-types
#            -UNDEBUG
#    )
#
#    target_compile_definitions(quasiconvex_debug PRIVATE
#            _GLIBCXX_DEBUG
#    )
#endif()
#
#
## ============================================================
## AddressSanitizer-версия
## ============================================================
#
#add_executable(quasiconvex_asan
#        ${SOURCES}
#)
#
#if (IS_MSVC_LIKE)
#    set(LLVM_ASAN_DIR
#        "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/lib/clang/22/lib/windows"
#    )
#
#    target_compile_options(quasiconvex_asan PRIVATE
#        /MD
#        /Zi
#        /Od
#        /Ob0
#        /fsanitize=address
#        /U_DEBUG
#        /UNDEBUG
#    )
#
#    target_link_options(quasiconvex_asan PRIVATE
#        /DEBUG
#        /INCREMENTAL:NO
#
#        "/LIBPATH:${LLVM_ASAN_DIR}"
#        "/WHOLEARCHIVE:${LLVM_ASAN_DIR}/clang_rt.asan_dynamic-x86_64.lib"
#        "/WHOLEARCHIVE:${LLVM_ASAN_DIR}/clang_rt.asan_dynamic_runtime_thunk-x86_64.lib"
#    )
#
#    set_property(TARGET quasiconvex_asan PROPERTY
#        MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
#    )
#else()
#    target_compile_options(quasiconvex_asan PRIVATE
#            -g3
#            -O0
#            -fno-omit-frame-pointer
#            -fsanitize=address,undefined
#    )
#
#    target_link_options(quasiconvex_asan PRIVATE
#            -fsanitize=address,undefined
#    )
#
#    target_compile_definitions(quasiconvex_asan PRIVATE
#            _GLIBCXX_DEBUG
#    )
#endif()





cmake_minimum_required(VERSION 3.16)
project(Quasiconvex)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

#add_compile_options(-Wall -Wextra -Wconversion -Werror)
add_compile_options(-D_GLIBCXX -g)
#add_compile_options(-O3 -march=native)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*" )

add_executable(
        quasiconvex_debug
        src/main.cpp
        ${SOURCES}
)