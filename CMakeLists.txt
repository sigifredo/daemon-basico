project( daemon-basico )
cmake_minimum_required(VERSION 2.8.3)

include_directories( include )

set(HDRS
include/Daemon.hpp
)

set(SRCS
src/Daemon.cpp
)

set(CODIGO
${HDRS}
${SRCS}
)

add_executable(daemon ${CODIGO} src/main.cpp)
