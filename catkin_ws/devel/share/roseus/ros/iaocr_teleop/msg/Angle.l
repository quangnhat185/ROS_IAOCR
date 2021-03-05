;; Auto-generated. Do not edit!


(when (boundp 'iaocr_teleop::Angle)
  (if (not (find-package "IAOCR_TELEOP"))
    (make-package "IAOCR_TELEOP"))
  (shadow 'Angle (find-package "IAOCR_TELEOP")))
(unless (find-package "IAOCR_TELEOP::ANGLE")
  (make-package "IAOCR_TELEOP::ANGLE"))

(in-package "ROS")
;;//! \htmlinclude Angle.msg.html


(defclass iaocr_teleop::Angle
  :super ros::object
  :slots (_heading_angle ))

(defmethod iaocr_teleop::Angle
  (:init
   (&key
    ((:heading_angle __heading_angle) 0)
    )
   (send-super :init)
   (setq _heading_angle (round __heading_angle))
   self)
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:serialization-length
   ()
   (+
    ;; uint8 _heading_angle
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _heading_angle
       (write-byte _heading_angle s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get iaocr_teleop::Angle :md5sum-) "7c2f60eb16157d5125dbfd7e2509f483")
(setf (get iaocr_teleop::Angle :datatype-) "iaocr_teleop/Angle")
(setf (get iaocr_teleop::Angle :definition-)
      "uint8 heading_angle
")



(provide :iaocr_teleop/Angle "7c2f60eb16157d5125dbfd7e2509f483")


