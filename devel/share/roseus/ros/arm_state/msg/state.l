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
  :slots (_id _position _angle ))

(defmethod arm_state::state
  (:init
   (&key
    ((:id __id) 0)
    ((:position __position) 0)
    ((:angle __angle) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _position (round __position))
   (setq _angle (round __angle))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:position
   (&optional __position)
   (if __position (setq _position __position)) _position)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; uint8 _id
    1
    ;; uint16 _position
    2
    ;; uint16 _angle
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _id
       (write-byte _id s)
     ;; uint16 _position
       (write-word _position s)
     ;; uint16 _angle
       (write-word _angle s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _position
     (setq _position (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _angle
     (setq _angle (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get arm_state::state :md5sum-) "402d479cdb26ccff42ea9316f4bc75ef")
(setf (get arm_state::state :datatype-) "arm_state/state")
(setf (get arm_state::state :definition-)
      "uint8 id
uint16 position
uint16 angle
")



(provide :arm_state/state "402d479cdb26ccff42ea9316f4bc75ef")


