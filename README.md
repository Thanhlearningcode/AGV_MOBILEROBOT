# Đề Tài: Robot Tự Hành Sử Dụng Raspberry Pi và STM32F411

## Giới thiệu
Đề tài này tập trung vào việc phát triển một hệ thống robot tự hành sử dụng công nghệ Lidar kết hợp với Raspberry Pi để thực hiện thuật toán **Hector SLAM** (Simultaneous Localization and Mapping). Hệ thống sẽ cho phép robot tự xác định vị trí của mình trong môi trường và xây dựng bản đồ theo thời gian thực.

### Mục tiêu
Mục tiêu chính của dự án là xây dựng một robot có khả năng tự động di chuyển trong không gian 2D bằng cách sử dụng cảm biến Lidar để thu thập dữ liệu về môi trường xung quanh. Dữ liệu này sẽ được xử lý trên Raspberry Pi, nơi thuật toán Hector SLAM sẽ được triển khai để tạo bản đồ và điều chỉnh vị trí của robot.

### Phần cứng
- **Raspberry Pi**: Sử dụng để xử lý dữ liệu Lidar và thực hiện thuật toán SLAM.
- **Lidar (ví dụ: RPLidar)**: Cảm biến để thu thập dữ liệu khoảng cách và hình ảnh môi trường.
- **STM32F411**: Vi điều khiển sẽ được sử dụng để điều khiển các động cơ bánh xe và đọc dữ liệu từ encoder, giúp robot có thể di chuyển chính xác theo bản đồ đã tạo.

### Tính năng
- **Xác định vị trí và lập bản đồ**: Robot sẽ sử dụng dữ liệu từ cảm biến Lidar để xác định vị trí của nó và tạo ra bản đồ môi trường.
- **Điều khiển động cơ**: STM32F411 sẽ nhận lệnh từ Raspberry Pi và điều khiển động cơ bánh xe dựa trên thông tin từ thuật toán SLAM và encoder để đạt được độ chính xác cao trong di chuyển.
- **Giao tiếp giữa Raspberry Pi và STM32F411**: Sử dụng giao thức SPI, CAN để truyền dữ liệu giữa hai thiết bị, đảm bảo hiệu suất và độ chính xác trong quá trình điều khiển.

### Kết luận
Dự án này không chỉ giúp phát triển kỹ năng lập trình và thiết kế hệ thống mà còn cung cấp cái nhìn sâu sắc về cách kết hợp các công nghệ khác nhau để tạo ra một robot tự hành hoàn chỉnh. Thông qua việc sử dụng Lidar và thuật toán Hector SLAM, robot sẽ có khả năng hoạt động một cách tự động trong môi trường thực tế.

## 🚀 Dự Án Robot Di Động AGV

Tôi đang làm việc trên một dự án **robot di động AGV (Automated Guided Vehicle)**! Dự án này bao gồm việc sử dụng cảm biến LIDAR kết nối với Raspberry Pi để thực hiện việc lập bản đồ và điều hướng, tất cả được hỗ trợ bởi ROS (Robot Operating System). 

### Mục tiêu dự án
Mục tiêu của dự án không chỉ là lập bản đồ mà còn là điều khiển động cơ chính xác. Để đạt được điều này, tôi đã tích hợp Raspberry Pi với vi điều khiển STM32F411 thông qua giao tiếp UART. Vi điều khiển STM32F411 chịu trách nhiệm điều khiển động cơ ở mức thấp, cho phép robot di chuyển chính xác và phản ứng nhanh chóng với các thay đổi trong môi trường được phát hiện bởi cảm biến LIDAR.

### Các thành phần chính
- **Cảm biến LIDAR**: Dùng để thu thập dữ liệu khoảng cách và hình ảnh môi trường, hỗ trợ cho việc lập bản đồ.
- **Raspberry Pi**: Xử lý dữ liệu từ cảm biến LIDAR và thực hiện thuật toán điều hướng thông qua ROS.
- **STM32F411**: Điều khiển động cơ bánh xe, đảm bảo chuyển động chính xác dựa trên dữ liệu từ Raspberry Pi.

### Kết luận
Dự án này không chỉ giúp tôi nâng cao kỹ năng lập trình và thiết kế hệ thống mà còn mang đến cái nhìn sâu sắc về cách tích hợp các công nghệ khác nhau để tạo ra một robot di động thông minh và hiệu quả.
