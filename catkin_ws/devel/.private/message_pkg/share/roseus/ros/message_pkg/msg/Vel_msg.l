;; Auto-generated. Do not edit!


(when (boundp 'message_pkg::Vel_msg)
  (if (not (find-package "MESSAGE_PKG"))
    (make-package "MESSAGE_PKG"))
  (shadow 'Vel_msg (find-package "MESSAGE_PKG")))
(unless (find-package "MESSAGE_PKG::VEL_MSG")
  (make-package "MESSAGE_PKG::VEL_MSG"))

(in-package "ROS")
;;//! \htmlinclude Vel_msg.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass message_pkg::Vel_msg
  :super ros::object
  :slots (_pwm_left_motor _pwm_right_motor _vel_left_motor _vel_right_motor _dir ))

(defmethod message_pkg::Vel_msg
  (:init
   (&key
    ((:pwm_left_motor __pwm_left_motor) (instance std_msgs::Int16 :init))
    ((:pwm_right_motor __pwm_right_motor) (instance std_msgs::Int16 :init))
    ((:vel_left_motor __vel_left_motor) (instance std_msgs::Float32 :init))
    ((:vel_right_motor __vel_right_motor) (instance std_msgs::Float32 :init))
    ((:dir __dir) (instance std_msgs::Int8 :init))
    )
   (send-super :init)
   (setq _pwm_left_motor __pwm_left_motor)
   (setq _pwm_right_motor __pwm_right_motor)
   (setq _vel_left_motor __vel_left_motor)
   (setq _vel_right_motor __vel_right_motor)
   (setq _dir __dir)
   self)
  (:pwm_left_motor
   (&rest __pwm_left_motor)
   (if (keywordp (car __pwm_left_motor))
       (send* _pwm_left_motor __pwm_left_motor)
     (progn
       (if __pwm_left_motor (setq _pwm_left_motor (car __pwm_left_motor)))
       _pwm_left_motor)))
  (:pwm_right_motor
   (&rest __pwm_right_motor)
   (if (keywordp (car __pwm_right_motor))
       (send* _pwm_right_motor __pwm_right_motor)
     (progn
       (if __pwm_right_motor (setq _pwm_right_motor (car __pwm_right_motor)))
       _pwm_right_motor)))
  (:vel_left_motor
   (&rest __vel_left_motor)
   (if (keywordp (car __vel_left_motor))
       (send* _vel_left_motor __vel_left_motor)
     (progn
       (if __vel_left_motor (setq _vel_left_motor (car __vel_left_motor)))
       _vel_left_motor)))
  (:vel_right_motor
   (&rest __vel_right_motor)
   (if (keywordp (car __vel_right_motor))
       (send* _vel_right_motor __vel_right_motor)
     (progn
       (if __vel_right_motor (setq _vel_right_motor (car __vel_right_motor)))
       _vel_right_motor)))
  (:dir
   (&rest __dir)
   (if (keywordp (car __dir))
       (send* _dir __dir)
     (progn
       (if __dir (setq _dir (car __dir)))
       _dir)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Int16 _pwm_left_motor
    (send _pwm_left_motor :serialization-length)
    ;; std_msgs/Int16 _pwm_right_motor
    (send _pwm_right_motor :serialization-length)
    ;; std_msgs/Float32 _vel_left_motor
    (send _vel_left_motor :serialization-length)
    ;; std_msgs/Float32 _vel_right_motor
    (send _vel_right_motor :serialization-length)
    ;; std_msgs/Int8 _dir
    (send _dir :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Int16 _pwm_left_motor
       (send _pwm_left_motor :serialize s)
     ;; std_msgs/Int16 _pwm_right_motor
       (send _pwm_right_motor :serialize s)
     ;; std_msgs/Float32 _vel_left_motor
       (send _vel_left_motor :serialize s)
     ;; std_msgs/Float32 _vel_right_motor
       (send _vel_right_motor :serialize s)
     ;; std_msgs/Int8 _dir
       (send _dir :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Int16 _pwm_left_motor
     (send _pwm_left_motor :deserialize buf ptr-) (incf ptr- (send _pwm_left_motor :serialization-length))
   ;; std_msgs/Int16 _pwm_right_motor
     (send _pwm_right_motor :deserialize buf ptr-) (incf ptr- (send _pwm_right_motor :serialization-length))
   ;; std_msgs/Float32 _vel_left_motor
     (send _vel_left_motor :deserialize buf ptr-) (incf ptr- (send _vel_left_motor :serialization-length))
   ;; std_msgs/Float32 _vel_right_motor
     (send _vel_right_motor :deserialize buf ptr-) (incf ptr- (send _vel_right_motor :serialization-length))
   ;; std_msgs/Int8 _dir
     (send _dir :deserialize buf ptr-) (incf ptr- (send _dir :serialization-length))
   ;;
   self)
  )

(setf (get message_pkg::Vel_msg :md5sum-) "8ce996bea8b23d23b9968c0c69988650")
(setf (get message_pkg::Vel_msg :datatype-) "message_pkg/Vel_msg")
(setf (get message_pkg::Vel_msg :definition-)
      "std_msgs/Int16 pwm_left_motor
std_msgs/Int16 pwm_right_motor
std_msgs/Float32 vel_left_motor
std_msgs/Float32 vel_right_motor
std_msgs/Int8 dir
================================================================================
MSG: std_msgs/Int16
int16 data

================================================================================
MSG: std_msgs/Float32
float32 data
================================================================================
MSG: std_msgs/Int8
int8 data

")



(provide :message_pkg/Vel_msg "8ce996bea8b23d23b9968c0c69988650")


