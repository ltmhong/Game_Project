# Game_Project_Introduction

INT2215 22 - Lê Thị Minh Hồng - 19021288
Chủ đề game: Cross the road



Lấy ý tưởng từ game Crossy Road trên android.
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



CÁC CHỨC NĂNG ĐÃ HOÀN THIỆN: Logic game


CÁC CHỨC NĂNG HIỆN ĐANG CẢI TIẾN:

- Hình ảnh:
  + Sửa lại và căn chỉnh font chữ
  + Tile (nước) của dòng sông chưa chuẩn kích cỡ thiết kế so với setting trong game.
  + Chưa thiết kế xong nhân vật (người chơi)
  + Sửa lại 1 vài thiết kế khác
 
 - Âm thanh:
  + Thay 1 số âm để căn thời gian phù hợp
  + Thêm nhạc nền cho game thay vì chỉ có nhạc hiệu ứng
