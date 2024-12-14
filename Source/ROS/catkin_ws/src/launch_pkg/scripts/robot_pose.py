###########################################################################
# @file    tf_echo.py
# @brief   Lắng nghe và in ra phép biến đổi giữa các frame trong hệ thống robot.
# @details Tập tin này sử dụng thư viện tf2_ros và PyKDL để lắng nghe các phép biến đổi (transforms)
#          giữa các frame 'map' và 'base_link'. Dữ liệu được in ra dưới dạng quaternion và góc Euler.
# @date    2024-12-03
# @author  Dang Danh, Van Thanh
###########################################################################

import rospy
import tf2_ros
import PyKDL
from math import pi

if __name__ == '__main__':
    rospy.init_node('tf_echo')  # Khởi tạo node ROS với tên 'tf_echo'

    tfbuffer = tf2_ros.Buffer()  # Khởi tạo bộ đệm

    listener = tf2_ros.TransformListener(tfbuffer)  # Khởi tạo listener
    rate = rospy.Rate(10.0)  # Tạo tần số cho vòng lặp (10 Hz)
    
    while not rospy.is_shutdown(): # Chạy cho đến khi ROS tắt
        try:
            # Lấy phép biến đổi giữa frame 'map' và 'base_link' tại thời điểm hiện tại
            trans = tfbuffer.lookup_transform('map', 'base_link', rospy.Time())
            print(trans)  # In ra phép biến đổi

            trans = trans.transform  # Lấy phần biến đổi từ thông tin phép biến đổi

            # Chuyển đổi quaternion sang góc Euler
            rot = PyKDL.Rotation.Quaternion(* [ eval('trans.rotation.'+c) for c in 'xyzw'] )
            print (' '.join( [ str(eval('trans.rotation.'+c)) for c in 'xyzw'] ))  # In các thành phần quaternion

            # Tính toán góc Euler từ quaternion, chuyển đổi từ radian sang độ
            ypr = [ i  / pi * 180 for i in rot.GetEulerZYX() ]  # Chuyển đổi Euler từ radian sang độ

        except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException) as e:
            # Xử lý ngoại lệ khi không thể lấy phép biến đổi
            print ("Fail", e)
        
        rate.sleep() 
