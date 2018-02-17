cmake_minimum_required(VERSION 2.6)

# Project webservices bench CPP
project(webservices-bench-cpp)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include(WebServicesBenchClientCPP.cmake.in)

# Check GCC version +
execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)
if (GCC_VERSION VERSION_LESS 4.5)
  message(FATAL_ERROR "Version < 4.5. This library is based on C++11 standard. Exit.")
#elseif(GCC_VERSION VERSION_GREATER 7.0 OR GCC_VERSION VERSION_EQUAL 7.0)
#  message(STATUS "Version >= 7.0 use -std=c++17")
#  add_definitions("-std=c++17")
elseif(GCC_VERSION VERSION_GREATER 6.0 OR GCC_VERSION VERSION_EQUAL 6.0)
  message(STATUS "Version >= 6.0 use -std=c++14")
  add_definitions("-std=c++14")
elseif(GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
  message(STATUS "Version >= 4.7 use -std=c++11")
  add_definitions("-std=c++11")
elseif(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
  message(STATUS "Version >= 4.7 use -std=c++11")
  add_definitions("-std=c++11")
else()
  message(STATUS "4.5 <= Version < 4.7 use -std=c++0x")
  add_definitions("-std=c++0x")
endif()
# Check GCC version -

# Add GCC definitions
#add_definitions("-Wall -Wextra -Werror -Wuninitialized -Wconversion -Wsign-conversion -Wformat-security -fstack-protector-all -Wstack-protector --param ssp-buffer-size=4 -ftrapv  -z relro,now -fPIC -D_FORTIFY_SOURCE=2")
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_definitions("-D ANCH_WINDOWS")
else()
  add_definitions("-D ANCH_POSIX")
endif()
add_definitions(${APPLICATION_COMPILE_FLAGS})

find_package (Threads)

# Includes location
include_directories(
  inc
  thrift.generated
  ${ANCH_INCLUDES_DIR}
  ${THRIFT_INCLUDES_DIR}
)

# Retrieve every files in project
file(
  GLOB_RECURSE
  source_files
  thrift.generated/*
  src/*
)

# Executable
add_executable(
  webservices-bench-cpp
  ${source_files}
  )

set(CMAKE_MODULE_PATH "$ENV{HOME}/projects/webservices-bench-cpp/;${CMAKE_MODULE_PATH}")
target_link_libraries(
  webservices-bench-cpp
  anch-logger
  anch-date
  anch-resource
  thrift
  ${CMAKE_THREAD_LIBS_INIT}
  )

# Configuration files +
configure_file(conf/application.conf application.conf COPYONLY)
configure_file(conf/dataset.json dataset.json COPYONLY)
configure_file(conf/anch-logger.conf anch-logger.conf COPYONLY)
# Configuration files -

if(UNIT_TESTS)
  include_directories(
    inc
    ${ANCH_INCLUDES_DIR}
    )

  file(
    GLOB_RECURSE
    test_customer_call
    src/thriftClientTestSuite.cpp
    src/dataset.cpp
    thrift.generated/*.cpp
    test/testCustomerCall.cpp
    )

  add_executable(
    customer-call-test
    ${test_customer_call}
    )

  target_link_libraries(
    customer-call-test
    anch-logger
    anch-date
    anch-resource
    thrift
    ${CMAKE_THREAD_LIBS_INIT}
    )
endif()
