**AIR WAR**

**Giới thiệu**

- Họ và tên : Nguyễn Ngọc Tài
- MSSV : 23020701
- Lớp k68J, Trường Đại học Công nghệ, Đại học Quốc gia Hà Nội (UET-VNU)

Air WAR là một trò chơi bắn nhau trên không nhằm tiêu diệt hết tất cả quái vật để bảo vệ hòa bình cho thế giới. Bạn sẽ vào vai một người lính lái máy bay và đi tiêu diệt kẻ thù trên quãng đường của mình, bạn sẽ dành chiến thắng nếu có thể tiêu diệt quái vật trên đường đi và đánh bại được Boss cuối. Nên nhớ là bạn chỉ có 1 mạng khi tham gia trò chơi nên là hãy thận trọng.

**Hướng dẫn tải và chạy game**

- Bước 1: Bấm vào phần "Code" màu xanh lá ở trên rồi bấm "Download ZIP" ở dưới cùng để tải game, hoặc có thể kéo code về từ trên github.
- Bước 2: Extract file zip vừa tải về
- Bước 3: Sử dụng CodeBlocks để mở file project Game.cbp( nhớ là cài đầy đủ các file SDL thì mới chơi được nhé)
- Bước 4: Vào menu và bấm Play để chơi nào

**Mô tả về game**

**Gameplay :** xem gameplay của game tại đây

### **Control**

- Game chỉ có tác vụ cơ bản là di chuyển và bắn ra đạn
  
  <img src="image(ReadMe)/Move.png" alt="GitHub" width="50" height="50">  Là các nút di chuyển nhân vật lên , xuống , trái , phải cho game
  
  <img src="image(ReadMe)/Mouse.png" alt="GitHub" width="50" height="50">Click chuột trái phải để có thể bắn ra được các loại đạn khác nhau
- Khi gặp boss trong game thì background + nhân vật bạn sẽ tự động được thay đổi giao diện cho ngầu ( hehe)

### **CÁC THÀNH PHẦN TRONG GAME**

- MainObject : Chính là bạn , 1 hình ảnh là bạn khi chưa gặp Boss và hình còn lại là khi bạn đã gặp Boss
  
  <img src="picture/airplane2.png " alt="GitHub" width="100" height="75"> <img src="picture/airplane3.png" alt="Airplane 3" width="100" height="75">
- Đệ tử :Chính là trợ thủ của bạn , 1 hình ảnh là khi chưa gặp Boss và hình còn lại là khi bạn đã gặp Boss
  
    <img src="picture/plane_fly1.png " alt="GitHub" width="100" height="75"> <img src="picture/flappybird.png" width="100" height="75">
- Threat (Đối tượng hiểm họa) : là các kẻ thù mà bạn phải tiêu diệt trên đường đi
  
    <img src="picture/Threat2.png " alt="GitHub" width="100" height="75"> 
- Boss (Trùm cuối) : là kẻ địch cuối cùng mà bạn phải đánh bại để dành chiến thắng . Bên trái là Boss khi còn nhiều mạng, bên phải là Boss khi chỉ còn có 1 mạng thôi
  
    <img src="picture/boss.png " alt="GitHub" width="100" height="75">       <img src="picture/boss2.png" width="100" height="75">

- Các loại đạn :
  +) Khi ấn Space thì đạn của đệ sẽ bay ra :
  
    <img src="picture/sphere.png" alt="GitHub" width="50" height="50"> 
    
  +) Khi bạn ấn chuột trái thì đạn sẽ trông như này :
  
    <img src="picture/rocket1.png" alt="GitHub" width="100" height="75"> 

  +) Khi bạn ấn chuột phải thì đạn sẽ trông như này :
  
    <img src="picture/rocket2.png" alt="GitHub" width="100" height="75"> 
    
  +)Đạn của Threat thì trông như này :
  
    <img src="picture/sphere2.png" alt="GitHub" width="50" height="50"> 

  +)Đạn của Boss cuối với quỹ đạo ảo diệu thì trông như này :

    <img src="picture/boss_amo.png" alt="GitHub" width="100" height="75"> 
   

\-Background :Đây là hình ảnh của 2 background trước khi bạn gặp Boss và sau khi bạn gặp Boss

   <img src="picture/background.png " alt="GitHub" width="600" height="73">  
  
   <img src="picture/backgroundn.png" alt="GitHub" width="600" height="73">


\-Thiên thạch :Là vật cản sẽ xuất hiện khi mà bạn gặp Boss, rất khó chịu bởi chị cần lại gần thôi là bạn đã die rồi.

   <img src="picture/thienthach.png" alt="GitHub" width="100" height="75"> 

\- Score : lưu lại số lượng địch bạn đã tiêu diệt

\- BOSS_LIFE : ghi lại số mạng của trùm cuối

\-Time : Lưu thời gian mà bạn đã chơi

**Nội dung game + một vài hình ảnh của game:**

- Mở đầu game là một cái menu hiện lên , bạn có thể vào chơi bằng cách ấn START FLY, và out khỏi game thì bấm EXIT.
  <img src="image(ReadMe)/background.png" alt="GitHub" width="350" height="200">
  
- Tiếp đến khi vào game là bạn sẽ tham gia vào cuộc chiến bắn địch trên bầu trời, khi bắn trúng thì sẽ có âm thanh phát ra và địch bị biến mất đi.
  Bên cạnh đó đồng hành cùng bạn là 1 con đệ tử gíup bạn tiêu diệt những con quái mà nhân vật chính thấy hơi khó bắn. Bấm Space để nhả đạn nhé!

  <img src="image(ReadMe)/game1.png" alt="GitHub" width="350" height="200">

- Khi bạn bắn đến 1 số điểm nhất định thì Boss sẽ xuất hiện và đồng thời nó cũng triệu hồi thiên thạch rơi xuống để tấn công bạn, lưu ý rằng đạn của Boss cuối bay với 1 quỹ đạo khá là dị nên sẽ đem lại đôi chút khó khăn cho bạn đấy .
- Bên cạnh đó khi boss xuất hiện thì bạn cũng sẽ có được diện mạo mới cho nhân vật + đệ tử đó .

    <img src="image(ReadMe)/game2.png" alt="GitHub" width="350" height="200">

- Khi Boss cuối còn 1 mạng thì nó cũng sẽ biến hình để tiêu diệt bạn với size khủng hơn + đạn to hơn
- 
     <img src="image(ReadMe)/game3.png" alt="GitHub" width="350" height="200">

- Nếu như bạn không may va vào địch , boss, hay thiên thạch hay bị trúng đạn thì bạn sẽ thua ngay lập tức(do bạn chỉ có 1 mạng) và nó sẽ hiện lên 1 dòng thông báo + âm thanh :
\->Bấm ok và run lại game để chơi lại

  <img src="image(ReadMe)/gameover.png" alt="GitHub" width="200" height="150">

- Còn nếu như bạn thành công tiêu diệt boss cuối thì sẽ hiện dòng thông báo + âm thanh sau :
\->Bấm ok và run lại game để chơi lại

  <img src="image(ReadMe)/gamewin.png" alt="GitHub" width="200" height="150">

## Các kỹ thuật lập trình đã sử dụng

- Vector, con trỏ
- Xử lý va chạm (Còn chưa được chuẩn lắm)
- SDL2 (SLD2_image, SDL2_mixer, SLD2_ttf)
- Kỹ thuật Texture font, Mouse event, Key event
- Sound Effects and Music
- Vòng lặp
- Mảng tĩnh
- Xâu
- Chia file cho dễ quản lý
- Kế thừa trong Class

## Kết luận

- Ý tưởng của game được tham khảo ở <https://phattrienphanmem123az.com/> (phiên bản SDL cũ) + tự học trên Lazyfoo + tự code lại bằng SDL2 + phát triển thêm 1 số tính năng ( menu + âm thanh + boss ,….)
- Học được cách sử dụng C++ và SDL2 để tự tạo được một game cơ bản cho bản thân
- Biết cách chia nhỏ file + class để dễ quản lý dự án hơn
