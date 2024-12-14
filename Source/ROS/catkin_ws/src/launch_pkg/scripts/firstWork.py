###########################################################################
# @file    firstWork.py
# @brief   Quản lý và điều khiển các node ROS trong hệ thống robot.
# @details 
# @date    2024-12-03
# @author  Dang Danh, Van Thanh
###########################################################################

import os  # Thư viện  hệ điều hành
import rospy  # Thư viện ROS cho Python
from std_msgs.msg import Int16  # Import kiểu dữ liệu Int16 

class WorkFirst:
    """
    Lớp này thực hiện các công việc ban đầu trong hệ thống ROS.
    """

    def __init__(self):
        """
        Khởi tạo lớp FirstWork. 
        """
        print("ROS Initial!")  # In ra thông báo
        rospy.init_node('first_work', anonymous=True)  # Khởi tạo node ROS tên 'first_work'
        self.rate = rospy.Rate(10)  # Thiết lập tần suất 10Hz

        # Khởi tạo publisher
        self.pub_run = rospy.Publisher('/first_work/run', Int16, queue_size=10)
        self.run = Int16()  # Tạo một đối tượng Int16
        self.count = 0  # Biến đếm

    def doIt(self):
        """
        Phương thức này thực hiện công việc dọn dẹp và gửi tín hiệu đến ROS.
        """
        os.system("yes | rosclean purge")  # Thực thi lệnh để xóa log ROS
        
        while not rospy.is_shutdown():  # Chạy cho đến khi ROS tắt
            self.pub_run.publish(self.run)  # Gửi tín hiệu tới topic '/first_work/run'
            self.count += 1  # Tăng biến đếm
            if (self.count > 100):  # Sau 100 lần gửi tín hiệu thì thoát vòng lặp
                break

            self.rate.sleep()

def main():
    """
    Hàm khởi tạo và chạy chương trình.
    """
    print('Program starting')  # In thông báo

    program = WorkFirst()  # Tạo đối tượng FirstWork
    program.doIt() 

    print('Program stopped')

if __name__ == '__main__':
    main()  
