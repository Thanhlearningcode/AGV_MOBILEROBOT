; Auto-generated. Do not edit!


(cl:in-package message_pkg-msg)


;//! \htmlinclude App_request.msg.html

(cl:defclass <App_request> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (action
    :reader action
    :initarg :action
    :type cl:fixnum
    :initform 0)
   (vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0))
)

(cl:defclass App_request (<App_request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <App_request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'App_request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name message_pkg-msg:<App_request> is deprecated: use message_pkg-msg:App_request instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <App_request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:mode-val is deprecated.  Use message_pkg-msg:mode instead.")
  (mode m))

(cl:ensure-generic-function 'action-val :lambda-list '(m))
(cl:defmethod action-val ((m <App_request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:action-val is deprecated.  Use message_pkg-msg:action instead.")
  (action m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <App_request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader message_pkg-msg:vel-val is deprecated.  Use message_pkg-msg:vel instead.")
  (vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <App_request>) ostream)
  "Serializes a message object of type '<App_request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'action)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <App_request>) istream)
  "Deserializes a message object of type '<App_request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<App_request>)))
  "Returns string type for a message object of type '<App_request>"
  "message_pkg/App_request")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'App_request)))
  "Returns string type for a message object of type 'App_request"
  "message_pkg/App_request")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<App_request>)))
  "Returns md5sum for a message object of type '<App_request>"
  "f6fb3554f499951649fc2f38c3f0f6fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'App_request)))
  "Returns md5sum for a message object of type 'App_request"
  "f6fb3554f499951649fc2f38c3f0f6fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<App_request>)))
  "Returns full string definition for message of type '<App_request>"
  (cl:format cl:nil "uint8 mode~%uint8 action~%float32 vel~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'App_request)))
  "Returns full string definition for message of type 'App_request"
  (cl:format cl:nil "uint8 mode~%uint8 action~%float32 vel~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <App_request>))
  (cl:+ 0
     1
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <App_request>))
  "Converts a ROS message object to a list"
  (cl:list 'App_request
    (cl:cons ':mode (mode msg))
    (cl:cons ':action (action msg))
    (cl:cons ':vel (vel msg))
))
