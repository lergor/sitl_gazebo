cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set (CMAKE_AUTOMOC ON)

if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

find_package (Qt5Widgets REQUIRED)
find_package (Qt5Core REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gazebo REQUIRED)

include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

#add_subdirectory(msgs)
set (control_msgs ControlPanelMessage.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${control_msgs})
add_library(control_panel_msgs SHARED ${PROTO_SRCS})
target_link_libraries(control_panel_msgs ${PROTOBUF_LIBRARY})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(gui_control_panel  SHARED ${headers_MOC}
        GUIControlPanel.cc)
target_link_libraries(gui_control_panel
        control_panel_msgs
        ${GAZEBO_LIBRARIES}
        ${Qt5Core_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${PROTOBUF_LIBRARIES})



#find_package(Protobuf REQUIRED)
#
#if(POLICY CMP0071)
#    cmake_policy(SET CMP0071 NEW)
#endif()
#
#set (msgs ../ControlPanelMessage.proto)
#PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${msgs})
#add_library(my_msgs SHARED ${PROTO_SRCS})
#target_link_libraries(my_msgs ${PROTOBUF_LIBRARY})