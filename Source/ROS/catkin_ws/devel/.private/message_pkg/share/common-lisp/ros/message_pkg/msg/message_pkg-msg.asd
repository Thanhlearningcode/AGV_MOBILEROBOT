
(cl:in-package :asdf)

(defsystem "message_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "App_request" :depends-on ("_package_App_request"))
    (:file "_package_App_request" :depends-on ("_package"))
    (:file "Keyboard_command" :depends-on ("_package_Keyboard_command"))
    (:file "_package_Keyboard_command" :depends-on ("_package"))
    (:file "Reconnect_sts" :depends-on ("_package_Reconnect_sts"))
    (:file "_package_Reconnect_sts" :depends-on ("_package"))
    (:file "Status_launch" :depends-on ("_package_Status_launch"))
    (:file "_package_Status_launch" :depends-on ("_package"))
    (:file "Status_port" :depends-on ("_package_Status_port"))
    (:file "_package_Status_port" :depends-on ("_package"))
    (:file "Vel_msg" :depends-on ("_package_Vel_msg"))
    (:file "_package_Vel_msg" :depends-on ("_package"))
  ))