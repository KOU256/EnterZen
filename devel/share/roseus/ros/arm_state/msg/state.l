;; Auto-generated. Do not edit!


(when (boundp 'arm_state::state)
  (if (not (find-package "ARM_STATE"))
    (make-package "ARM_STATE"))
  (shadow 'state (find-package "ARM_STATE")))
(unless (find-package "ARM_STATE::STATE")
  (make-package "ARM_STATE::STATE"))

(in-package "ROS")
;;//! \htmlinclude state.msg.html


(defclass arm_state::state
  :super ros::object
  :slots (_position _angle ))

(defmethod arm_state::state
  (:init
   (&key
    ((:position __position) 0)
    ((:angle __angle) 0)
    )
   (send-super :init)
   (setq _position (round __position))
   (setq _angle (round __angle))
   self)
  (:position
   (&optional __position)
   (if __position (setq _position __position)) _position)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; uint16 _position
    2
    ;; uint16 _angle
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _position
       (write-word _position s)
     ;; uint16 _angle
       (write-word _angle s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _position
     (setq _position (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _angle
     (setq _angle (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get arm_state::state :md5sum-) "9a885ace4264c2a68f0fa7a276cc0f3d")
(setf (get arm_state::state :datatype-) "arm_state/state")
(setf (get arm_state::state :definition-)
      "uint16 position
uint16 angle
")



(provide :arm_state/state "9a885ace4264c2a68f0fa7a276cc0f3d")


