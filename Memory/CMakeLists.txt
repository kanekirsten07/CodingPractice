file(GLOB_RECURSE PUBLIC_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/**.h")
file(GLOB_RECURSE PRIVATE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/**.cpp")


# add the executable
add_executable(Memory MemoryMain.cpp)


target_compile_features(Memory PRIVATE cxx_std_17)