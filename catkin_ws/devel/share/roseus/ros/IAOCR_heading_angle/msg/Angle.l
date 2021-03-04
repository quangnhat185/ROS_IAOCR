;; Auto-generated. Do not edit!


(when (boundp 'IAOCR_heading_angle::Angle)
  (if (not (find-package "IAOCR_HEADING_ANGLE"))
    (make-package "IAOCR_HEADING_ANGLE"))
  (shadow 'Angle (find-package "IAOCR_HEADING_ANGLE")))
(unless (find-package "IAOCR_HEADING_ANGLE::ANGLE")
  (make-package "IAOCR_HEADING_ANGLE::ANGLE"))

(in-package "ROS")
;;//! \htmlinclude Angle.msg.html


(defclass IAOCR_heading_angle::Angle
  :super ros::object
  :slots (_angle ))

(defmethod IAOCR_heading_angle::Angle
  (:init
   (&key
    ((:angle __angle) 0)
    )
   (send-super :init)
   (setq _angle (round __angle))
   self)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; uint8 _angle
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _angle
       (write-byte _angle s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _angle
     (setq _angle (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get IAOCR_heading_angle::Angle :md5sum-) "70f18cf7713067edf3d007a4504b0aad")
(setf (get IAOCR_heading_angle::Angle :datatype-) "IAOCR_heading_angle/Angle")
(setf (get IAOCR_heading_angle::Angle :definition-)
      "uint8 angle
")



(provide :IAOCR_heading_angle/Angle "70f18cf7713067edf3d007a4504b0aad")


