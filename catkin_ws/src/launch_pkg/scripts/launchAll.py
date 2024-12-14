###########################################################################
# @file    launchAll.py
# @brief   Quản lý và điều khiển các node ROS trong hệ thống robot.
# @details Tập tin này khởi tạo và điều khiển các module ROS khác nhau như 
#          lidar, navigation, kinematic, pure, core và rviz. Các module này 
#          được khởi chạy lần lượt và trạng thái của chúng được theo dõi để 
#          đảm bảo hệ thống hoạt động đúng.
# @date    2024-12-03
# @author  Dang Danh, Van Thanh
###########################################################################

# Nhập các thư viện từ ROS và Python
from sensor_msgs.msg import LaserScan  # dữ liệu cảm biến
from geometry_msgs.msg import Twist  # Điều khiển chuyển động
from std_msgs.msg import Int16

import roslaunch
import rospy  # Thư viện client Python của ROS
import time

# Lớp Launch quản lý việc khởi tạo và khởi chạy ROS
class Launch:
    """
    Lớp khởi tạo và khởi chạy một node ROS từ tệp launch.
    Thuộc tính:
        fileLaunch (str): Đường dẫn đến tệp launch.
        uuid (str): ID của ROS.
        process (int): State của chương trình (0: Chưa bắt đầu, 1: Đang chạy, 2: Đã hoàn thành).
        time_pre (float): Thời gian bắt đầu chạy.
    """
    def __init__(self, file_launch):
        """
        Khởi tạo đối tượng Launch của tệp launch.
        Tham số:
            file_launch (str): Đường dẫn đến tệp launch.
        """        
        self.fileLaunch = file_launch  # Đường dẫn đến tệp launch
        self.uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)  # Tạo ID 
        roslaunch.configure_logging(self.uuid)  # Cấu hình logging cho ID
        self.process = 0 # Khởi tạo State
        self.time_pre = time.time()  # Lưu thời gian bắt đầu

    def start(self):
        """
        Khởi chạy Node.
        """
        if (self.process == 0): # If State = 0
            launch = roslaunch.parent.ROSLaunchParent(self.uuid, [self.fileLaunch]) # Tạo ID
            launch.start()
            self.process = 1  # Cập nhật State

    def start_and_wait(self, timeWait):
        """
        Bắt đầu node ROS và chờ đợi một khoảng thời gian nhất định trước khi kiểm tra xem node đã được khởi tạo chưa.

        Tham số:
            timeWait (float): Thời gian chờ.

        Return:
            int: 0 nếu đang chờ, 1 nếu node đã được khởi tạo.
        """
        if (self.process == 0): # If State = 0
            launch = roslaunch.parent.ROSLaunchParent(self.uuid, [self.fileLaunch])  # Tạo ID
            launch.start()  
            self.process = 1  # Cập nhật State
            self.time_pre = time.time()  # Lưu thời gian bắt đầu
            return 0 

        elif (self.process == 1): # If State = 1
            t = (time.time() - self.time_pre) % 60  # Tính toán thời gian đã trôi qua
            if (t > timeWait):  # if Run_Time > timeWait
                self.process = 2  # Cập nhật State
            return 0  

        elif (self.process == 2): # If State = 1
            return 1  

# Lớp điều khiển module
class launcher():
    def __init__(self):
        """
        Khởi tạo đối tượng launcher và thiết lập ROS node và các module.
        """
        print("ROS Initial!")
        rospy.init_node('launcher', anonymous=False)  # Khởi tạo ROS node
        self.rate = rospy.Rate(10)  # Thiết lập tần suất vòng lặp là 10 Hz

        self.count_node = 0  # Khởi tạo số lượng node = 0
        self.notification = ''  # Khởi tạo thông báo trạng thái
        self.step = 0  # Bộ đếm 
        self.timeWait = 0.4  # Thời gian chờ

        # -- module - firstWork.
        self.path_firstWork = rospy.get_param('path_firstWork', '')  # Lấy đường dẫn đến tệp launch của first_work
        self.launch_firstWork = Launch(self.path_firstWork)  # Tạo đối tượng Launch
        rospy.Subscriber('/first_work/run', Int16, self.callBack_firstWork)
        self.is_firstWork = 0  # Khởi tạo State của first_work = 0
        self.count_node += 1  # Tăng số lượng node lên 1

        # -- module - core.
        self.path_core = rospy.get_param('path_core', '')  # Lấy đường dẫn đến tệp launch của core
        self.launch_core = Launch(self.path_core)  # Tạo đối tượng Launch 
        rospy.Subscriber('/core_info', Twist, self.callBack_core)  # Đăng ký chủ đề /core_info
        self.is_core = 0  # Khởi tạo State của của core = 0
        self.count_node += 1  # Tăng số lượng node lên 1

        # -- module - rplidar.
        self.path_lidar = rospy.get_param('path_lidar', '')  # Lấy đường dẫn đến tệp launch của lidar
        self.launch_lidar = Launch(self.path_lidar)  # Tạo đối tượng Launch
        rospy.Subscriber('/scan', LaserScan, self.callBack_lidar) 
        self.is_lidar = 0  # Khởi tạo State của của lidar = 0
        self.count_node += 1  # Tăng số lượng node lên 1

        # -- module - navigation
        self.path_navigation = rospy.get_param('path_navigation', '') # Lấy đường dẫn đến tệp launch của navigation
        self.launch_navigation = Launch(self.path_navigation)# Tạo đối tượng Launch
        self.is_navigation = 0 # Khởi tạo State của của navigation = 0
        self.count_node += 1 # Tăng số lượng node lên 1

        # -- module - kinematic.
        self.path_kinematic = rospy.get_param('path_kinematic', '')  # Lấy đường dẫn đến tệp launch của kinematic
        self.launch_kinematic = Launch(self.path_kinematic)  # Tạo đối tượng Launch cho kinematic
        self.is_kinematic = 0   # Khởi tạo State của của kinematic = 0
        self.count_node += 1  # Tăng số lượng node lên 1

        # -- module - pure.
        self.path_pure = rospy.get_param('path_pure', '')  # Lấy đường dẫn đến tệp launch của pure
        self.launch_pure = Launch(self.path_pure)  # Tạo đối tượng Launch cho pure
        self.is_pure = 0  # Khởi tạo State của của pure = 0
        self.count_node += 1  # Tăng số lượng node lên 1

        # -- module - rviz.
        self.is_display = rospy.get_param('rviz', 1)  # Lấy cài đặt hiển thị RViz
        self.path_rviz = rospy.get_param('path_rviz', '')  # Lấy đường dẫn đến tệp launch của RViz
        self.launch_rviz = Launch(self.path_rviz)  # Tạo đối tượng Launch cho RViz
        self.is_rviz = 0  # Khởi tạo State của của rviz = 0
        self.count_node += 1  # Tăng số lượng node lên 1

    # Các hàm callback
    def callBack_firstWork(self, data):
        self.is_firstWork = 1  # Cập nhật State của firstWork

    def callBack_core(self, data):
        self.is_core = 1  # Cập nhật State của core

    def callBack_lidar(self, data):
        self.is_lidar = 1  # Cập nhật State của lidar

    def run(self):
        """
        Hàm chính điều khiển việc khởi chạy tuần tự tất cả các module.
        Nó lặp qua từng bước khởi chạy và đảm bảo mỗi module được khởi tạo trước khi chuyển sang bước tiếp theo.
        """
        while not rospy.is_shutdown(): # Chạy cho đến khi ROS tắt
            # -- firstWork
            if (self.step == 0):
                self.notification = 'launch_firstWork'
                self.launch_firstWork.start()  # launch first work
                if (self.is_firstWork == 1):  # Kiểm tra xem first work đã hoàn thành chưa
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- nav
            elif (self.step == 1):
                self.notification = 'launch_lidar'
                self.launch_lidar.start()  # launch module lidar
                if (self.is_lidar == 1):  # Kiểm tra xem lidar đã được khởi tạo chưa
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- navigation
            elif (self.step == 2):
                self.notification = 'launch_navigation'
                sts = self.launch_navigation.start_and_wait(3.)  # Chờ node navigation
                if (sts == 1):
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- kinematic
            elif (self.step == 3):
                self.notification = 'launch_kinematic'
                sts = self.launch_kinematic.start_and_wait(3.)  # Chờ node kinematic
                if (sts == 1):
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- pure
            elif (self.step == 4):
                self.notification = 'launch_pure'
                sts = self.launch_pure.start_and_wait(3.)  # Chờ node pure
                if (sts == 1):
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- main
            elif (self.step == 5):
                self.notification = 'launch_core'
                sts = self.launch_core.start_and_wait(3.)  # Chờ node core
                if (sts == 1):
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- rviz
            elif (self.step == 6):
                self.notification = 'launch_rviz'
                sts = self.launch_rviz.start_and_wait(3.)  # Chờ node RViz
                if (sts == 1):
                    self.step += 1  # Chuyển sang bước tiếp theo
                    time.sleep(self.timeWait)  # Chờ trước khi khởi chạy module tiếp theo

            # -- Hoàn thành
            elif (self.step == 7):
                self.notification = 'Hoàn thành!'  # Chỉ ra rằng tất cả các module đã được khởi chạy

            self.rate.sleep()

# Hàm chính 
def main():
    print('Chương trình bắt đầu') 
    try:
        program = launcher()  # Tạo đối tượng launcher
        program.run()
    except rospy.ROSInterruptException:
        pass  # Gián đoạn ROS
    print('Chương trình dừng lại')  

if __name__ == '__main__':
    main()
