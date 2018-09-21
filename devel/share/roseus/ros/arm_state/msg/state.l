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
    ((:id __id) (make-array 0 :initial-element 0 :element-type :char))
    ((:position __position) (make-array 0 :initial-element 0 :element-type :integer))
    ((:angle __angle) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _id __id)
   (setq _position __position)
   (setq _angle __angle)
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
    ;; uint8[] _id
    (* 1    (length _id)) 4
    ;; uint16[] _position
    (* 2    (length _position)) 4
    ;; uint16[] _angle
    (* 2    (length _angle)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8[] _id
     (write-long (length _id) s)
     (princ _id s)
     ;; uint16[] _position
     (write-long (length _position) s)
     (dotimes (i (length _position))
       (write-word (elt _position i) s)
       )
     ;; uint16[] _angle
     (write-long (length _angle) s)
     (dotimes (i (length _angle))
       (write-word (elt _angle i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8[] _id
   (let ((n (sys::peek buf ptr- :integer))) (incf ptr- 4)
     (setq _id (make-array n :element-type :char))
     (replace _id buf :start2 ptr-) (incf ptr- n))
   ;; uint16[] _position
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _position (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _position i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; uint16[] _angle
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angle (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _angle i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;;
   self)
  )

(setf (get arm_state::state :md5sum-) "cc5377a64d7ce3f6a03aaa672d3115bd")
(setf (get arm_state::state :datatype-) "arm_state/state")
(setf (get arm_state::state :definition-)
      "uint8[] id
uint16[] position
uint16[] angle
")



(provide :arm_state/state "cc5377a64d7ce3f6a03aaa672d3115bd")


