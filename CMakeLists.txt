if(NOT DEFINED ADLINK_DDS_PRODUCT) 
    set(error
        "ADLINK_DDS_PRODUCT not defined. Please set -DADLINK_DDS_PRODUCT=Ospl/Cyclone")
    message(FATAL_ERROR ${error})
else()
	message(STATUS "-DADLINK_DDS_PRODUCT = ${ADLINK_DDS_PRODUCT}")

	add_definitions(-D"${ADLINK_DDS_PRODUCT}")

	if(${ADLINK_DDS_PRODUCT} MATCHES "Cyclone")
		if(NOT DEFINED CYCLONE_INSTALLED_DIR)
			set(error
        			"CYCLONE_INSTALLED_DIR not defined. Please set -DCYCLONE_INSTALLED_DIR= to "
				"your CYCLONE installation directory")
			message(FATAL_ERROR ${error})

		elseif(NOT IS_DIRECTORY ${CYCLONE_INSTALLED_DIR})
			set(error
        			"CYCLONE_INSTALLED_DIR is not a valid directory. Please set -DCYCLONE_INSTALLED_DIR= to "
				"your CYCLONE installation directory")
			message(FATAL_ERROR ${error})

		elseif(NOT EXISTS ${CYCLONE_INSTALLED_DIR})
			set(error
        			"CYCLONE_INSTALLED_DIR doesn't exits. Please set -DCYCLONE_INSTALLED_DIR= to "
				"your CYCLONE installation directory")
			message(FATAL_ERROR ${error})

		else()
			message(STATUS "-DCYCLONE_INSTALLED_DIR = ${CYCLONE_INSTALLED_DIR}")
			
		endif()

	elseif(${ADLINK_DDS_PRODUCT} MATCHES "Ospl")
		if(NOT DEFINED ENV{OSPL_HOME})
			set(error
        			"OSPL_HOME not specified. Please set the Opensplice environemt variables by"
				" source release.sh/release.bash file")
			message(FATAL_ERROR ${error})
		else()
			message(STATUS "OSPL_HOME = $ENV{OSPL_HOME}")
		endif()
	else()
		set(error
		"ADLINK_DDS_PRODUCT is wrong. Please pass the correct value. Expected value is Ospl/ Cyclone")
	   	message(FATAL_ERROR ${error})
	endif()	
		
endif()	


project(demo_ishape LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.5)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED Core Widgets Gui)


set(HEADERS *.h *.hpp)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

#set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

if(${ADLINK_DDS_PRODUCT} MATCHES "Ospl")

	include_directories($ENV{OSPL_HOME}/include/sys)
	include_directories($ENV{OSPL_HOME}/include/dcps/C++/isocpp2)
        include_directories("${CMAKE_CURRENT_BINARY_DIR}")

	LINK_DIRECTORIES($ENV{OSPL_HOME}/lib)

	set(PROJECT_LINK_LIBS PUBLIC ddskernel dcpsisocpp2)

# Convenience function, provided by the Idlpp that generates a CMake
# target for the given IDL file. The function calls Idlcpp to generate
# source files and compiles them into a library.


	execute_process(COMMAND $ENV{OSPL_HOME}/bin/idlpp -S -l isocpp2 ${PROJECT_SOURCE_DIR}/ishape.idl )


	file(GLOB idl_SRCS
		"${CMAKE_CURRENT_BINARY_DIR}/ishape.h"
		"${CMAKE_CURRENT_BINARY_DIR}/ishape.cpp"
		"${CMAKE_CURRENT_BINARY_DIR}/ishapeSplDcps.h"
		"${CMAKE_CURRENT_BINARY_DIR}/ishapeSplDcps.cpp"
		"${CMAKE_CURRENT_BINARY_DIR}/ishape_DCPS.hpp"
		)

	add_library(ospl_ishape_lib ${idl_SRCS})

	target_link_libraries(ospl_ishape_lib PUBLIC ${PROJECT_LINK_LIBS})

	add_executable(ospl_demo_ishapes  ${idl_SRCS} ${all_SRCS} ishape.qrc)

	# Link both executables to idl data type library and opensplice dds libraries (ddskernel & dcpsisocpp2).
	target_link_libraries(ospl_demo_ishapes PRIVATE ospl_ishape_lib ${PROJECT_LINK_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui)
	
	#set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
	#set_property(TARGET ospl_demo_ishapes PROPERTY ${CMAKE_CXX_FLAGS})
	set_property(TARGET ospl_demo_ishapes PROPERTY CXX_STANDARD 11)

        install(TARGETS ospl_demo_ishapes RUNTIME DESTINATION "$ENV{OSPL_HOME}/bin")
        install(TARGETS ospl_demo_ishapes RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")


elseif(${ADLINK_DDS_PRODUCT} MATCHES "Cyclone")

	set(CMAKE_PREFIX_PATH ${CYCLONE_INSTALLED_DIR})

	#find_package(Idlpp-cxx REQUIRED PATHS "${CMAKE_PREFIX_PATH}")

	if (NOT TARGET CycloneDDS-CXX::ddscxx)
	  find_package(CycloneDDS-CXX REQUIRED PATHS "${CMAKE_PREFIX_PATH}")
	endif()

	# Convenience function, provided by the Idlpp-cxx that generates a CMake
	# target for the given IDL file. The function calls Idlcpp-cxx to generate
	# source files and compiles them into a library.
	#idl_ddscxx_generate(ddscxxishape_lib "ishape.idl")
	idlcxx_generate(TARGET ddscxxishape_lib FILES "ishape.idl")

	add_executable(cyclone_demo_ishapes ${all_SRCS} ishape.qrc)

	# Link both executables to idl data type library and ddscxx.
	target_link_libraries(cyclone_demo_ishapes CycloneDDS-CXX::ddscxx ddscxxishape_lib Qt5::Widgets Qt5::Core Qt5::Gui)

	#set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
	#set_property(TARGET cyclone_demo_ishapes PROPERTY ${CMAKE_CXX_FLAGS})
	set_property(TARGET cyclone_demo_ishapes PROPERTY CXX_STANDARD 11)

	install(TARGETS cyclone_demo_ishapes RUNTIME DESTINATION "${CYCLONE_INSTALLED_DIR}/bin")
	install(TARGETS cyclone_demo_ishapes RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")
else()
	set(error
        "ADLINK_DDS_PRODUCT is wrong. Please pass the correct value. Expected value is Ospl/ Cyclone")
   	message(FATAL_ERROR ${error})
	
endif()
