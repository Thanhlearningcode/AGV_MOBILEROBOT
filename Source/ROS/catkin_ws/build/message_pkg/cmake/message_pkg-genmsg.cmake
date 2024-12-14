# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "message_pkg: 3 messages, 0 services")

set(MSG_I_FLAGS "-Imessage_pkg:/home/thanh/catkin_ws/src/message_pkg/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(message_pkg_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" NAME_WE)
add_custom_target(_message_pkg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_pkg" "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" ""
)

get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" NAME_WE)
add_custom_target(_message_pkg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_pkg" "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" "std_msgs/Float32:std_msgs/Int16:std_msgs/Int8"
)

get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" NAME_WE)
add_custom_target(_message_pkg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_pkg" "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_pkg
)
_generate_msg_cpp(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int16.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int8.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_pkg
)
_generate_msg_cpp(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_pkg
)

### Generating Services

### Generating Module File
_generate_module_cpp(message_pkg
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_pkg
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(message_pkg_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(message_pkg_generate_messages message_pkg_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_cpp _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_cpp _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_cpp _message_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_pkg_gencpp)
add_dependencies(message_pkg_gencpp message_pkg_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_pkg_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_pkg
)
_generate_msg_eus(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int16.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int8.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_pkg
)
_generate_msg_eus(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_pkg
)

### Generating Services

### Generating Module File
_generate_module_eus(message_pkg
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_pkg
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(message_pkg_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(message_pkg_generate_messages message_pkg_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_eus _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_eus _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_eus _message_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_pkg_geneus)
add_dependencies(message_pkg_geneus message_pkg_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_pkg_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_pkg
)
_generate_msg_lisp(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int16.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int8.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_pkg
)
_generate_msg_lisp(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_pkg
)

### Generating Services

### Generating Module File
_generate_module_lisp(message_pkg
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_pkg
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(message_pkg_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(message_pkg_generate_messages message_pkg_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_lisp _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_lisp _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_lisp _message_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_pkg_genlisp)
add_dependencies(message_pkg_genlisp message_pkg_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_pkg_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_pkg
)
_generate_msg_nodejs(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int16.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int8.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_pkg
)
_generate_msg_nodejs(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_pkg
)

### Generating Services

### Generating Module File
_generate_module_nodejs(message_pkg
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_pkg
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(message_pkg_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(message_pkg_generate_messages message_pkg_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_nodejs _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_nodejs _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_nodejs _message_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_pkg_gennodejs)
add_dependencies(message_pkg_gennodejs message_pkg_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_pkg_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg
)
_generate_msg_py(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int16.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Int8.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg
)
_generate_msg_py(message_pkg
  "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg
)

### Generating Services

### Generating Module File
_generate_module_py(message_pkg
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(message_pkg_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(message_pkg_generate_messages message_pkg_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/App_request.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_py _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Vel_msg.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_py _message_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/thanh/catkin_ws/src/message_pkg/msg/Keyboard_command.msg" NAME_WE)
add_dependencies(message_pkg_generate_messages_py _message_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_pkg_genpy)
add_dependencies(message_pkg_genpy message_pkg_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_pkg_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_pkg
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(message_pkg_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(message_pkg_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_pkg
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(message_pkg_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(message_pkg_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_pkg
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(message_pkg_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(message_pkg_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_pkg
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(message_pkg_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(message_pkg_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_pkg
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(message_pkg_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(message_pkg_generate_messages_py geometry_msgs_generate_messages_py)
endif()
