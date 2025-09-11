# Robot Tự Hành Sử Dụng Raspberry Pi và STM32F411

## 1. Giới thiệu
Trong thời đại công nghệ phát triển, **robot tự hành** đang trở thành một lĩnh vực nghiên cứu và ứng dụng quan trọng trong nhiều ngành công nghiệp, từ **vận chuyển hàng hóa** trong kho bãi đến **thám hiểm môi trường phức tạp**. Dự án này tập trung vào việc phát triển một hệ thống **robot tự hành** sử dụng **cảm biến Lidar** kết hợp với **Raspberry Pi** để thực hiện thuật toán **Hector SLAM** (Simultaneous Localization and Mapping). 

Hệ thống giúp robot xác định vị trí của mình trong môi trường và xây dựng bản đồ theo **thời gian thực**, mở ra nhiều tiềm năng trong điều hướng tự động, robot di động AGV (Automated Guided Vehicle) và nghiên cứu về robot.

---

## 2. Mục tiêu dự án
Mục tiêu chính của dự án là xây dựng một hệ thống **robot tự hành thông minh**, có khả năng:
- **Di chuyển tự động trong môi trường 2D**, tránh vật cản và điều hướng theo bản đồ.
- **Sử dụng Lidar để thu thập dữ liệu môi trường**, xử lý bằng thuật toán **Hector SLAM** trên Raspberry Pi để lập bản đồ và định vị chính xác.
- **Tích hợp STM32F411 để điều khiển động cơ chính xác**, đảm bảo robot di chuyển mượt mà và phản ứng nhanh chóng.
- **Thiết lập giao tiếp giữa Raspberry Pi và STM32F411**, giúp truyền dữ liệu điều khiển và phản hồi vị trí một cách nhanh chóng và hiệu quả.

---

## 3. Thành phần phần cứng
Hệ thống robot này bao gồm các thành phần chính sau:

### 3.1 Raspberry Pi
- **Vai trò:** Bộ xử lý trung tâm, chịu trách nhiệm xử lý dữ liệu từ cảm biến, thực hiện thuật toán Hector SLAM và điều khiển toàn bộ hệ thống.
- **Chức năng chính:**
  - Tiếp nhận dữ liệu từ cảm biến Lidar.
  - Xử lý dữ liệu bản đồ và vị trí thông qua Hector SLAM.
  - Gửi lệnh điều khiển đến STM32F411 để kiểm soát động cơ.
  - Hiển thị và phân tích dữ liệu bản đồ qua giao diện đồ họa.

### 3.2 Lidar 
- **Vai trò:** Cảm biến chính giúp robot nhận diện môi trường xung quanh và xây dựng bản đồ.
- **Chức năng:**
  - Phát ra tia laser để đo khoảng cách đến các vật thể.
  - Cung cấp dữ liệu đám mây điểm (point cloud) để xử lý bản đồ và định vị.
  - Hỗ trợ tốc độ quét nhanh, giúp cập nhật bản đồ liên tục theo thời gian thực.

### 3.3 STM32F411
- **Vai trò:** Điều khiển động cơ bánh xe, đảm bảo robot di chuyển chính xác.
- **Chức năng:**
  - Nhận lệnh từ Raspberry Pi và điều khiển động cơ theo thuật toán SLAM.
  - Đọc dữ liệu từ encoder để phản hồi tốc độ và vị trí của robot.
  - Điều khiển xung PWM để kiểm soát tốc độ động cơ một cách linh hoạt.

### 3.4 Động cơ & Encoder
- **Vai trò:** Cung cấp lực đẩy và đo lường vị trí của robot.
- **Chức năng:**
  - Hỗ trợ di chuyển chính xác theo lệnh điều khiển từ STM32F411.
  - Encoder giúp cập nhật vị trí của bánh xe, đảm bảo độ chính xác trong di chuyển.

---

## 4. Các tính năng chính của hệ thống

### 4.1 Xác định vị trí và lập bản đồ
- Robot sử dụng **Lidar** để thu thập dữ liệu khoảng cách và nhận diện môi trường xung quanh.
- Thuật toán **Hector SLAM** xử lý dữ liệu này để tạo bản đồ thời gian thực và định vị chính xác trong không gian 2D.

### 4.2 Điều khiển động cơ thông minh
- **STM32F411** nhận tín hiệu từ Raspberry Pi và điều khiển động cơ bánh xe để robot di chuyển chính xác.
- **Encoder** đo lường sự di chuyển của bánh xe, giúp điều chỉnh đường đi của robot một cách tối ưu.

### 4.3 Giao tiếp giữa Raspberry Pi và STM32F411
- **Giao thức SPI, CAN hoặc UART** được sử dụng để truyền dữ liệu giữa hai bộ xử lý.
- Đảm bảo hiệu suất cao, độ trễ thấp, giúp robot hoạt động ổn định và mượt mà.

---

## 5. Ứng dụng thực tế
Hệ thống này có thể ứng dụng vào nhiều lĩnh vực khác nhau như:
- **Xe tự hành trong nhà máy, kho bãi**: Hỗ trợ vận chuyển hàng hóa tự động.
- **Robot thám hiểm trong môi trường phức tạp**: Giúp điều hướng trong các khu vực khó tiếp cận.
- **Nghiên cứu và phát triển hệ thống điều hướng thông minh**: Cung cấp nền tảng cho các dự án robot tự hành hiện đại.

---

## 6. Kết luận
Dự án này không chỉ giúp nâng cao kỹ năng **lập trình nhúng, xử lý dữ liệu và thiết kế hệ thống** mà còn cung cấp cái nhìn sâu sắc về **công nghệ robot tự hành**. Với sự kết hợp giữa **Lidar, Raspberry Pi và STM32F411**, robot có thể hoạt động **tự động, chính xác và hiệu quả**, mở ra nhiều tiềm năng ứng dụng thực tế.

---

## 7. Video minh họa dự án
🎥 **Xem video demo về dự án tại:**
🔗 [Video 1](https://youtu.be/lSaE2lDuPe4)  
🔗 [Video 2](https://www.youtube.com/watch?v=16xksGicoLY)
🔗 [Video All]([https://www.youtube.com/watch?v=16xksGicoLY](https://www.youtube.com/playlist?list=PLuLSa6UJU-JVPB2FamfjqBzRCuvz32bf4))
