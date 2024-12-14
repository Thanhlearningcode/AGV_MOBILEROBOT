;; Auto-generated. Do not edit!


(when (boundp 'message_pkg::Keyboard_command)
  (if (not (find-package "MESSAGE_PKG"))
    (make-package "MESSAGE_PKG"))
  (shadow 'Keyboard_command (find-package "MESSAGE_PKG")))
(unless (find-package "MESSAGE_PKG::KEYBOARD_COMMAND")
  (make-package "MESSAGE_PKG::KEYBOARD_COMMAND"))

(in-package "ROS")
;;//! \htmlinclude Keyboard_command.msg.html


(defclass message_pkg::Keyboard_command
  :super ros::object
  :slots (_value ))

(defmethod message_pkg::Keyboard_command
  (:init
   (&key
    ((:value __value) "")
    )
   (send-super :init)
   (setq _value (string __value))
   self)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; string _value
    4 (length _value)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _value
       (write-long (length _value) s) (princ _value s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _value
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _value (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get message_pkg::Keyboard_command :md5sum-) "64e58419496c7248b4ef25731f88b8c3")
(setf (get message_pkg::Keyboard_command :datatype-) "message_pkg/Keyboard_command")
(setf (get message_pkg::Keyboard_command :definition-)
      "string value
")



(provide :message_pkg/Keyboard_command "64e58419496c7248b4ef25731f88b8c3")


