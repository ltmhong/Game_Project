# Game_Project Introduction

INT2215 22 - Lê Thị Minh Hồng - 19021288
Chủ đề game: Cross the road

- Lấy ý tưởng từ game Crossy Road trên android.
- Có tham khảo 1 số tutorial trên internet.

LƯU Ý: Code game nằm ở file "game.cpp"

Cách thức hoạt động của game:
- Người chơi sẽ là 1 nhân vật cần qua đường.

- Những chướng ngại vật sẽ là con đường cùng với dòng sông.
  +Tại con đường: người chơi cần tránh tất cả những chiếc ô tô tiến tới từ cả 2 phía (sinh ngẫu nhiên theo làn)
  + Dòng sông: Người chơi cần ở trên những khúc gỗ để vượt sông.
  
- Cách thức di chuyển: Sử dụng phím 4 phím "up", "down", "left", "right" tại bàn phím
  + Phiên bản hiện tại vì chưa sử dụng thư viện SDL nên thay 4 phím trên lần lượt bằng 'w', 's', 'a' và 'd'.
  + Người chơi có thể tiến, lùi, sang trái/phải tùy ý miễn là không ra khỏi giới hạn 2 phía trái/phải của màn hình
  
- Cách thức tính điểm: Mỗi lần người chơi vượt qua 1 làn (đường/sông) sẽ được cộng 1 điểm
- Trò chơi sẽ tiếp diễn cho đến khi người chơi thua (bị đâm hoặc rơi xuống sông)
