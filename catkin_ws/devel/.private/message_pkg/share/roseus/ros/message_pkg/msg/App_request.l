;; Auto-generated. Do not edit!


(when (boundp 'message_pkg::App_request)
  (if (not (find-package "MESSAGE_PKG"))
    (make-package "MESSAGE_PKG"))
  (shadow 'App_request (find-package "MESSAGE_PKG")))
(unless (find-package "MESSAGE_PKG::APP_REQUEST")
  (make-package "MESSAGE_PKG::APP_REQUEST"))

(in-package "ROS")
;;//! \htmlinclude App_request.msg.html


(defclass message_pkg::App_request
  :super ros::object
  :slots (_mode _action _vel ))

(defmethod message_pkg::App_request
  (:init
   (&key
    ((:mode __mode) 0)
    ((:action __action) 0)
    ((:vel __vel) 0.0)
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _action (round __action))
   (setq _vel (float __vel))
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:action
   (&optional __action)
   (if __action (setq _action __action)) _action)
  (:vel
   (&optional __vel)
   (if __vel (setq _vel __vel)) _vel)
  (:serialization-length
   ()
   (+
    ;; uint8 _mode
    1
    ;; uint8 _action
    1
    ;; float32 _vel
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _mode
       (write-byte _mode s)
     ;; uint8 _action
       (write-byte _action s)
     ;; float32 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _action
     (setq _action (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get message_pkg::App_request :md5sum-) "f6fb3554f499951649fc2f38c3f0f6fa")
(setf (get message_pkg::App_request :datatype-) "message_pkg/App_request")
(setf (get message_pkg::App_request :definition-)
      "uint8 mode
uint8 action
float32 vel
")



(provide :message_pkg/App_request "f6fb3554f499951649fc2f38c3f0f6fa")


