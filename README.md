# Game_Project_Introduction

INT2215 22 - Lê Thị Minh Hồng - 19021288
Chủ đề game: Cross the road



Lấy ý tưởng từ game Crossy Road trên Android và Frogger.
Có tham khảo thuật toán và logic của 1 số tutorial trên internet.



LƯU Ý: Code game nằm ở folder "Source code"
  + File "demo_game.cpp" chạy trên Console, dùng để mô tả phần lõi game (có thể chạy nhưng chưa đầy đủ).
  + Các file còn lại thuộc về phần game chính sử dụng SDL, hiện tại đã hoàn thiện được phần lớn và có thể chạy.



Cách thức hoạt động của game:

- Người chơi sẽ là 1 nhân vật cần qua đường.

- Những chướng ngại vật sẽ là con đường, đường ray cùng với dòng sông.
    + Tại con đường: người chơi cần tránh những bụi cây + ô tô tiến tới từ cả 2 phía (sinh ngẫu nhiên theo làn)
    + Tại đường ray: người chơi cần tránh được khi tàu hỏa tiến tới (sinh ngẫu nhiên và có căn thời gian kkhi người chơi đến gần)
    + Dòng sông: Người chơi cần ở trên những khúc gỗ để vượt sông.

- Cách thức di chuyển: Sử dụng phím 4 phím "up", "down", "left", "right" tại bàn phím
  + Phiên bản hiện tại đã sử dụng SDL và có thể sử dụng 4 phím chức năng trên
  + Người chơi có thể tiến, lùi, sang trái/phải tùy ý miễn là không ra khỏi giới hạn 2 phía trái/phải của màn hình

- Cách thức tính điểm:
  + Mỗi lần người chơi vượt qua 1 làn (đường/sông) sẽ được cộng 1 điểm.
  + Người chơi có thể ăn xu trong quá trình chơi.

- Trò chơi sẽ tiếp diễn cho đến khi người chơi thua (bị đâm hoặc rơi xuống sông hoặc ra khỏi màn hình chơi)



CÁC CHỨC NĂNG ĐÃ HOÀN THIỆN:

- Logic game:
  + Game hoạt động bình thường, không có bug
  + Game không có lỗi logic
- Thao tác trong game:
  + Tương tác bàn phím không có vấn đề
  + Tương tác bằng chuột đôi khi gặp khó khăn vì nhiều lúc hệ thống nhận diện thành nháy đúp (double click)
      (Đặc biệt đối với khi nhấn nút "tạm dừng" (pause)
      
- Hình ảnh:
  + Render rõ ràng, đúng với ý tưởng
  + Đôi lúc xử lý va chạm của người chơi sẽ có chút vấn đề (không phải lỗi logic, sẽ giải thích khi vấn đáp)
  
- Âm thanh: đã có đầy đủ hiệu ứng âm thanh cần thiết (bỏ nhạc nền game)



CÁC CHỨC NĂNG HIỆN ĐANG CẢI TIẾN: không có


NHỮNG PHẦN KHÁC ĐANG HOÀN THIỆN:

- Xử lý code gọn gàng, dễ nhìn
- Xử lý những biến, hàm thừa không dùng đến
- Comment những giải thích sơ bộ cho các biến, hàm
