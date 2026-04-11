#	project-dir
#		/ src
#		/ CMakeLists.txt
#		/ build
#
#		/ uts
#			/ src
#			/ CMakeLists.txt
#			/ build-uts

cmake_minimum_required(VERSION 3.5)

project(polimorfizm-ptr-move-proj)

add_library(mylib SHARED)
target_sources(mylib
	PRIVATE
		src/CChildren.cpp

		src/CConfigChild.cpp

#		src/CMap.cpp
#		src/CMapIf.cpp

		src/CSelectorConfigurator.cpp

		src/CSimpleSelector.cpp
		src/CSelector.cpp

		src/CSelectorIf.cpp


		src/CInput.cpp
		src/CInputIf.cpp

		src/CFramework.cpp
		src/CFrameworkIf.cpp

	PUBLIC
		FILE_SET mylibHeaders
		TYPE HEADERS
		BASE_DIRS
			src/include
		FILES
			src/include/CFrameworkIf.hpp
			src/include/CInputIf.hpp
			src/include/CParent.hpp
			src/include/child-creators.hpp
)

add_executable(polimorfizm-ptr-move)
target_sources(polimorfizm-ptr-move
	PRIVATE
		src/main.cpp

)

target_link_libraries(polimorfizm-ptr-move mylib)
