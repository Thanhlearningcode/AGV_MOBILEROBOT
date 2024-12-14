; Auto-generated. Do not edit!


(cl:in-package message_pkg-msg)


;//! \htmlinclude Vel_msg.msg.html

(cl:defclass <Vel_msg> (roslisp-msg-protocol:ros-message)
  ((pwm_left_motor
    :reader pwm_left_motor
    :initarg :pwm_left_motor
    :type std_msgs-msg:Int16
    :initform (cl:make-instance 'std_msgs-msg:Int16))
   (pwm_right_motor
    :reader pwm_right_motor
    :initarg :pwm_right_motor
    :type std_msgs-msg:Int16
    :initform (cl:make-instance 'std_msgs-msg:Int16))
   (vel_left_motor
    :reader vel_left_motor
    :initarg :vel_left_motor
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (vel_right_motor
    :reader vel_right_motor
    :initarg :vel_right_motor
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (dir
    :reader dir
    :initarg :dir
    :type std_msgs-msg:Int8
    :initform (cl:make-instance 'std_msgs-msg:Int8)))
)

(cl:defclass Vel_msg (<Vel_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Vel_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Vel_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name message_pkg-msg:<Vel_msg> is deprecated: use message_pkg-msg:Vel_msg instead.")))

(cl:ensure-generic-function 'pwm_left_motor-val :lambda-list '(m))
(cl:defmethod pwm_left_motor-val ((m <Vel_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:pwm_left_motor-val is deprecated.  Use message_pkg-msg:pwm_left_motor instead.")
  (pwm_left_motor m))

(cl:ensure-generic-function 'pwm_right_motor-val :lambda-list '(m))
(cl:defmethod pwm_right_motor-val ((m <Vel_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:pwm_right_motor-val is deprecated.  Use message_pkg-msg:pwm_right_motor instead.")
  (pwm_right_motor m))

(cl:ensure-generic-function 'vel_left_motor-val :lambda-list '(m))
(cl:defmethod vel_left_motor-val ((m <Vel_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:vel_left_motor-val is deprecated.  Use message_pkg-msg:vel_left_motor instead.")
  (vel_left_motor m))

(cl:ensure-generic-function 'vel_right_motor-val :lambda-list '(m))
(cl:defmethod vel_right_motor-val ((m <Vel_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:vel_right_motor-val is deprecated.  Use message_pkg-msg:vel_right_motor instead.")
  (vel_right_motor m))

(cl:ensure-generic-function 'dir-val :lambda-list '(m))
(cl:defmethod dir-val ((m <Vel_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:dir-val is deprecated.  Use message_pkg-msg:dir instead.")
  (dir m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Vel_msg>) ostream)
  "Serializes a message object of type '<Vel_msg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pwm_left_motor) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pwm_right_motor) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'vel_left_motor) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'vel_right_motor) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'dir) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Vel_msg>) istream)
  "Deserializes a message object of type '<Vel_msg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pwm_left_motor) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pwm_right_motor) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'vel_left_motor) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'vel_right_motor) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'dir) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Vel_msg>)))
  "Returns string type for a message object of type '<Vel_msg>"
  "message_pkg/Vel_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Vel_msg)))
  "Returns string type for a message object of type 'Vel_msg"
  "message_pkg/Vel_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Vel_msg>)))
  "Returns md5sum for a message object of type '<Vel_msg>"
  "8ce996bea8b23d23b9968c0c69988650")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Vel_msg)))
  "Returns md5sum for a message object of type 'Vel_msg"
  "8ce996bea8b23d23b9968c0c69988650")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Vel_msg>)))
  "Returns full string definition for message of type '<Vel_msg>"
  (cl:format cl:nil "std_msgs/Int16 pwm_left_motor~%std_msgs/Int16 pwm_right_motor~%std_msgs/Float32 vel_left_motor~%std_msgs/Float32 vel_right_motor~%std_msgs/Int8 dir~%================================================================================~%MSG: std_msgs/Int16~%int16 data~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%================================================================================~%MSG: std_msgs/Int8~%int8 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Vel_msg)))
  "Returns full string definition for message of type 'Vel_msg"
  (cl:format cl:nil "std_msgs/Int16 pwm_left_motor~%std_msgs/Int16 pwm_right_motor~%std_msgs/Float32 vel_left_motor~%std_msgs/Float32 vel_right_motor~%std_msgs/Int8 dir~%================================================================================~%MSG: std_msgs/Int16~%int16 data~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%================================================================================~%MSG: std_msgs/Int8~%int8 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Vel_msg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pwm_left_motor))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pwm_right_motor))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'vel_left_motor))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'vel_right_motor))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'dir))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Vel_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'Vel_msg
    (cl:cons ':pwm_left_motor (pwm_left_motor msg))
    (cl:cons ':pwm_right_motor (pwm_right_motor msg))
    (cl:cons ':vel_left_motor (vel_left_motor msg))
    (cl:cons ':vel_right_motor (vel_right_motor msg))
    (cl:cons ':dir (dir msg))
))
