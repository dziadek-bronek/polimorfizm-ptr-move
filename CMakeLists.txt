cmake_minimum_required(VERSION 3.5)

project(polimorfizm-ptr-move-proj)

add_library(mylib SHARED
#	PRIVATE
		src/CChildren.cpp

		src/selector-config.cpp
		src/CChildSelector.cpp

		src/CInput.cpp
		src/CFramework.cpp

#	PUBLIC
#		FILE_SET mylibHeaders
#		TYPE HEADERS
#		BASE_DIRS
#			src/include
#		FILES
#			src/include/CFrameworkIf.hpp
#			src/include/CInput.hpp
#			src/include/CParent.hpp
#			src/include/child-creators.hpp
)

add_executable(polimorfizm-ptr-move
#	PRIVATE
		src/main.cpp

)

target_link_libraries(polimorfizm-ptr-move mylib)
