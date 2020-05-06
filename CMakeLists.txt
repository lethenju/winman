cmake_minimum_required (VERSION 3.9)
project (winman VERSION 1.0.0 DESCRIPTION "A simple Window-based text UI in C")

#[[ Building Library ]]

include(GNUInstallDirs)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(
	termlib/
)


set(INCLUDE_FILES
	inc/tasks_mgmt.h
	inc/widgets.h
	inc/winman_types.h
	inc/winman.h
)

set(LIBRARY_SOURCE_FILES
	src/tasks_mgmt.c
	src/widgets.c
	src/winman.c
)

add_library(winman STATIC
	${INCLUDE_FILES}
	${LIBRARY_SOURCE_FILES}
)

set (ALL_LIBS 
     resman
	 log_system
	 termlib
	 pthread
	 m
)

target_link_libraries(winman
	${ALL_LIBS}
	
)	

set_target_properties(winman PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(winman PROPERTIES PUBLIC_HEADER inc/winman.h)

target_include_directories(winman PRIVATE inc)
target_include_directories(winman PRIVATE src)

install(TARGETS winman
	  	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



#[[ Building Tests ]]

	#[[ Compiling Main ]]


add_executable(test_exe
	examples/test.c
	${INCLUDE_FILES}
)

target_include_directories(test_exe PRIVATE inc)

target_link_libraries(test_exe
	winman
	m
	pthread
)	
