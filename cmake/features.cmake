# detect available compiler features and libraries
include(CheckCXXSourceCompiles)
include(CheckPrototypeDefinition)
include(CheckCCompilerFlag)
include(CheckTypeSize)
include(CheckFunctionExists)

# check for SSE etc.
if(NOT MSVC)
  check_c_compiler_flag(-faltivec HAVE_ALTIVEC)
  check_c_compiler_flag(-mavx HAVE_AVX)
  check_c_compiler_flag(-mmmx HAVE_MMX)
  option(OSMSCOUT_ENABLE_SSE "Enable SSE support (not working on all platforms!)" OFF)
  if(OSMSCOUT_ENABLE_SSE)
    check_c_compiler_flag(-msse HAVE_SSE)
    check_c_compiler_flag(-msse2 HAVE_SSE2)
    check_c_compiler_flag(-msse3 HAVE_SSE3)
    check_c_compiler_flag(-msse4.1 HAVE_SSE4_1)
    check_c_compiler_flag(-msse4.2 HAVE_SSE4_2)
    check_c_compiler_flag(-mssse3 HAVE_SSSE3)
  endif()
  if(HAVE_SSE2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
  endif()
else()
  set(HAVE_ALTIVEC OFF)
  set(HAVE_AVX ON)
  set(HAVE_MMX ON)
  set(HAVE_SSE ON)
  set(HAVE_SSE2 ON)
  set(HAVE_SSE3 OFF)
  set(HAVE_SSE4_1 OFF)
  set(HAVE_SSE4_2 OFF)
  set(HAVE_SSSE3 OFF)
  if (NOT OSMSCOUT_PLATFORM_X64)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
  endif()
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
  check_cxx_compiler_flag(-fvisibility=hidden HAVE_VISIBILITY)
  if(HAVE_VISIBILITY)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
  endif()
else()
  set(HAVE_VISIBILITY OFF)
endif()

# check headers exists
include(CheckIncludeFileCXX)
check_include_file(dlfcn.h HAVE_DLFCN_H)
check_include_file(fcntl.h HAVE_FCNTL_H)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file_cxx(codecvt HAVE_CODECVT)
if(${HAVE_STDINT_H} AND ${HAVE_STDLIB_H} AND ${HAVE_INTTYPES_H} AND ${HAVE_STRING_H} AND ${HAVE_MEMORY_H})
  set(STDC_HEADERS ON)
else()
  set(STDC_HEADERS OFF)
endif()

# check data types exists
set(CMAKE_EXTRA_INCLUDE_FILES inttypes.h)
check_type_size(int16_t HAVE_INT16_T)
check_type_size(int32_t HAVE_INT32_T)
check_type_size(int64_t HAVE_INT64_T)
check_type_size(int8_t HAVE_INT8_T)
check_type_size("long long" HAVE_LONG_LONG)
check_type_size(uint16_t HAVE_UINT16_T)
check_type_size(uint32_t HAVE_UINT32_T)
check_type_size(uint64_t HAVE_UINT64_T)
check_type_size(uint8_t HAVE_UINT8_T)
check_type_size("unsigned long long" HAVE_UNSIGNED_LONG_LONG)
set(CMAKE_EXTRA_INCLUDE_FILES wchar.h)
check_type_size(wchar_t SIZEOF_WCHAR_T)
set(CMAKE_EXTRA_INCLUDE_FILES)

# check functions exists
check_function_exists(fseeko HAVE_FSEEKO)
check_function_exists(mmap HAVE_MMAP)
check_function_exists(posix_fadvise HAVE_POSIX_FADVISE)
check_function_exists(posix_madvise HAVE_POSIX_MADVISE)
check_function_exists(mallinfo HAVE_MALLINFO)

# check libraries and tools
find_package(Marisa)
find_package(LibXml2)
find_package(MyProtobuf) # Modified FindProtobuf
find_package(ZLIB)
find_package(iconv)
find_package(LibLZMA)
find_package(PNG QUIET)
find_package(Cairo)
find_package(Agg)
find_package(Freetype)
find_package(PANGO)
find_package(OpenGL QUIET)
find_package(GLUT QUIET)
find_package(GLEW QUIET)
find_package(GLM QUIET)
find_package(Qt5Core 5.0 QUIET)
find_package(Qt5Gui 5.0 QUIET)
find_package(Qt5Widgets 5.0 QUIET)
find_package(Qt5Qml 5.0 QUIET)
find_package(Qt5Quick 5.0 QUIET)
find_package(Qt5Svg 5.0 QUIET)
find_package(Qt5Positioning 5.0 QUIET)
if (BUILD_WITH_OPENMP)
  find_package(OpenMP QUIET)
  if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif()
find_package(Doxygen QUIET)
find_package(SWIG QUIET)
find_package(JNI QUIET)
set(Matlab_FIND_COMPONENTS MX_LIBRARY)
find_package(MATLAB QUIET)
find_package(Gperftools QUIET)
find_package(Direct2D QUIET)
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${THREADS_PTHREAD_ARG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${THREADS_PTHREAD_ARG}")
endif()

# prepare cmake variables for configuration files
set(OSMSCOUT_HAVE_INT16_T ${HAVE_INT16_T})
set(OSMSCOUT_HAVE_INT32_T ${HAVE_INT32_T})
set(OSMSCOUT_HAVE_INT64_T ${HAVE_INT64_T})
set(OSMSCOUT_HAVE_INT8_T ${HAVE_INT8_T})
set(HAVE_LIB_MARISA ${MARISA_FOUND})
set(HAVE_LIB_XML ${LIBXML2_FOUND})
set(HAVE_LIB_PROTOBUF ${PROTOBUF_FOUND})
set(HAVE_LIB_ZLIB ${ZLIB_FOUND})
set(HAVE_LIB_CAIRO ${CAIRO_FOUND})
set(HAVE_LIB_AGG ${LIBAGG_FOUND})
set(HAVE_LIB_FREETYPE ${FREETYPE_FOUND})
set(HAVE_LIB_PANGO ${PANGO_FOUND})
set(HAVE_LIB_PNG ${PNG_FOUND})
set(HAVE_LIB_OPENGL ${OPENGL_FOUND})
set(HAVE_LIB_GLUT ${GLUT_FOUND})
set(HAVE_LIB_GPERFTOOLS ${GPERFTOOLS_FOUND})
set(CMAKE_AUTOMOC OFF)
set(HAVE_LIB_QT5_GUI ${Qt5Gui_FOUND})
set(HAVE_LIB_QT5_WIDGETS ${Qt5Widgets_FOUND})
set(OSMSCOUT_HAVE_LIB_MARISA ${HAVE_LIB_MARISA})
set(OSMSCOUT_HAVE_LONG_LONG ${HAVE_LONG_LONG})
set(OSMSCOUT_HAVE_SSE2 ${HAVE_SSE2})
set(OSMSCOUT_HAVE_STDINT_H ${HAVE_STDINT_H})
set(OSMSCOUT_HAVE_STD_WSTRING ${HAVE_STD__WSTRING})
set(OSMSCOUT_HAVE_UINT16_T ${HAVE_UINT16_T})
set(OSMSCOUT_HAVE_UINT32_T ${HAVE_UINT32_T})
set(OSMSCOUT_HAVE_UINT64_T ${HAVE_UINT64_T})
set(OSMSCOUT_HAVE_UINT8_T ${HAVE_UINT8_T})
set(OSMSCOUT_HAVE_ULONG_LONG ${HAVE_UNSIGNED_LONG_LONG})
set(OSMSCOUT_IMPORT_HAVE_LIB_MARISA ${MARISA_FOUND})
set(OSMSCOUT_MAP_CAIRO_HAVE_LIB_PANGO ${PANGOCAIRO_FOUND})
set(OSMSCOUT_MAP_OPENGL_HAVE_GL_GLUT_H ${HAVE_LIB_GLUT})
set(OSMSCOUT_MAP_OPENGL_HAVE_GLUT_GLUT_H OFF)
set(OSMSCOUT_MAP_SVG_HAVE_LIB_PANGO ${PANGOFT2_FOUND})
set(OSMSCOUT_HAVE_OPENMP ${OPENMP_FOUND})
if(ICONV_FOUND)
    set(HAVE_ICONV TRUE)
    if(${ICONV_SECOND_ARGUMENT_IS_CONST})
        set(ICONV_CONST "const")
    endif()
else()
    message(WARNING "No iconv support")
endif()

function(create_private_config output name)
  string(REPLACE "-" "_" OSMSCOUT_PRIVATE_CONFIG_HEADER_NAME ${name})
  string(TOUPPER ${OSMSCOUT_PRIVATE_CONFIG_HEADER_NAME} OSMSCOUT_PRIVATE_CONFIG_HEADER_NAME)
  configure_file("${OSMSCOUT_BASE_DIR_SOURCE}/cmake/Config.h.cmake" ${output})
endfunction()
