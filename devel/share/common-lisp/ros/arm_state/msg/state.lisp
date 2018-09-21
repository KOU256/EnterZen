; Auto-generated. Do not edit!


(cl:in-package arm_state-msg)


;//! \htmlinclude state.msg.html

(cl:defclass <state> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type cl:fixnum
    :initform 0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:fixnum
    :initform 0))
)

(cl:defclass state (<state>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <state>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'state)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arm_state-msg:<state> is deprecated: use arm_state-msg:state instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_state-msg:id-val is deprecated.  Use arm_state-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_state-msg:position-val is deprecated.  Use arm_state-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_state-msg:angle-val is deprecated.  Use arm_state-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <state>) ostream)
  "Serializes a message object of type '<state>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'position)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'angle)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'angle)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <state>) istream)
  "Deserializes a message object of type '<state>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'position)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'angle)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'angle)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<state>)))
  "Returns string type for a message object of type '<state>"
  "arm_state/state")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'state)))
  "Returns string type for a message object of type 'state"
  "arm_state/state")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<state>)))
  "Returns md5sum for a message object of type '<state>"
  "402d479cdb26ccff42ea9316f4bc75ef")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'state)))
  "Returns md5sum for a message object of type 'state"
  "402d479cdb26ccff42ea9316f4bc75ef")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<state>)))
  "Returns full string definition for message of type '<state>"
  (cl:format cl:nil "uint8 id~%uint16 position~%uint16 angle~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'state)))
  "Returns full string definition for message of type 'state"
  (cl:format cl:nil "uint8 id~%uint16 position~%uint16 angle~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <state>))
  (cl:+ 0
     1
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <state>))
  "Converts a ROS message object to a list"
  (cl:list 'state
    (cl:cons ':id (id msg))
    (cl:cons ':position (position msg))
    (cl:cons ':angle (angle msg))
))
