set(target ${MP2_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
set_target_properties(${target} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${target} ${LIBRARY_DEPS})
