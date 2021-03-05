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
  :slots (_data ))

(defmethod iaocr_teleop::Angle
  (:init
   (&key
    ((:data __data) 0)
    )
   (send-super :init)
   (setq _data (round __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint16 _data
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _data
       (write-word _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _data
     (setq _data (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get iaocr_teleop::Angle :md5sum-) "1df79edf208b629fe6b81923a544552d")
(setf (get iaocr_teleop::Angle :datatype-) "iaocr_teleop/Angle")
(setf (get iaocr_teleop::Angle :definition-)
      "uint16  data
")



(provide :iaocr_teleop/Angle "1df79edf208b629fe6b81923a544552d")


