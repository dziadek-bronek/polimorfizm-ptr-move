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



# ------------------------

add_library(CDemoSoChild SHARED
	src/CDemoSoChild/CDemoSoChild.cpp
)

target_compile_definitions( CDemoSoChild
	PRIVATE
	CDEMOSOCHILD_IMPLEMENTATION
)

# ------------------------

add_library(CConfigSoChild SHARED
	src/CConfigSoChild/CConfigSoChild.cpp

)

target_compile_definitions( CConfigSoChild
	PRIVATE
	CCONFIGSOCHILD_IMPLEMENTATION
)

# ------------------------



add_library(CChildren SHARED
	src/CChildren/CChildren.cpp

)

target_compile_definitions( CChildren
	PRIVATE
	CCHILDREN_IMPLEMENTATION
)

# ------------------------

add_library(CSelectorConfigurator SHARED
	src/CSelectorConfigurator/CSelectorConfigurator.cpp

		src/SoChildCreatorsProduction/CSoChildWrapperAndCreator.cpp
		src/SoChildCreatorsProduction/CSoChildCreatorsProducerChild.cpp

#[[
		src/CMap.cpp
		src/CMapIf.cpp
]]

		src/CSimpleSelector.cpp
		src/CSelector.cpp
)

target_compile_definitions( CSelectorConfigurator
	PRIVATE
		CSELECTORCONFIGURATORIF_IMPLEMENTATION
)

target_link_libraries(CSelectorConfigurator PUBLIC
	CChildren
)

# ------------------------


add_library(mylib)
target_sources(mylib
	PRIVATE

		src/CDlGlobalHandle.cpp

		src/CSoConfiguratorProducer.cpp

		src/CInput.cpp
		src/CInputIf.cpp

		src/CFramework.cpp

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

target_link_libraries(polimorfizm-ptr-move
	mylib
)
