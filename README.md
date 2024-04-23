AIR WORLD
Giới thiệu
•	Họ và tên : Nguyễn Ngọc Tài 
•	MSSV : 23020701
•	Lớp k68J, Trường Đại học Công nghệ, Đại học Quốc gia Hà Nội (UET-VNU)
Air World là một trò chơi bắn nhau trên không nhằm tiêu diệt hết tất cả quái vật để bảo vệ hòa bình cho thế giới. Bạn sẽ vào vai một người lính lái máy bay và đi tiêu diệt kẻ thù trên quãng đường của mình, bạn sẽ dành chiến thắng nếu có thể tiêu diệt quái vật trên đường đi và đánh bại được Boss cuối. Nên nhớ là bạn chỉ có 1 mạng khi tham gia trò chơi nên là hãy thận trọng.

Hướng dẫn tải và chạy game
•	Bước 1: Bấm vào phần "Code" màu xanh lá ở trên rồi bấm "Download ZIP" ở dưới cùng để tải game, hoặc có thể kéo code về từ trên github.
•	Bước 2: Extract file zip vừa tải về
•	Bước 3: Sử dụng CodeBlocks để mở file project Game.cbp( nhớ là cài đầy đủ các file SDL thì mới chơi được nhé)
•	Bước 4: Vào menu và bấm Play để chơi nào
Mô tả về game
Gameplay  : xem gameplay của game tại đây 
Control 
•	Game chỉ có tác vụ cơ bản là di chuyển và bắn ra đạn 
•	   :  Là các nút di chuyển nhân vật lên , xuống , trái , phải cho game
•	   : Click chuột trái phải để có thể bắn ra được các loại đạn khác nhau
•	Khi gặp boss trong game thì background + nhân vật bạn sẽ tự động được thay đổi giao diện cho ngầu ( hehe)	
Nội dung game + một vài hình ảnh của game:
•	Mở đầu game là một cái menu hiện lên , bạn có thể vào chơi bằng cách ấn START FLY, và out khỏi game thì bấm EXIT.
   

•	Tiếp đến khi vào game là bạn sẽ tham gia vào cuộc chiến bắn địch trên bầu trời, khi bắn trúng thì sẽ có âm thanh phát ra và địch bị biến mất đi.
Bên cạnh đó đồng hành cùng bạn là 1 con đệ tử gíup bạn tiêu diệt những con quái mà nhân vật chính thấy hơi khó bắn. Bấm Space để nhả đạn nhé!

 







•	Khi bạn bắn đến 1 số điểm nhất định thì Boss sẽ xuất hiện và đồng thời nó cũng triệu hồi thiên thạch rơi xuống để tấn công bạn, lưu ý rằng đạn của Boss cuối bay với 1 quỹ đạo khá là dị nên sẽ đem lại đôi chút khó khăn cho bạn đấy .
•	Bên cạnh đó khi boss xuất hiện thì bạn cũng sẽ có được diện mạo mới cho nhân vật + đệ tử đó .
 

•	Khi Boss cuối còn 1 mạng thì nó cũng sẽ biến hình để tiêu diệt bạn với size khủng hơn + đạn to hơn
 
•	Nếu như bạn không may va vào địch , boss, hay thiên thạch hay bị trúng đạn thì bạn sẽ thua ngay lập tức(do bạn chỉ có 1 mạng) và nó sẽ hiện lên 1 dòng thông báo + âm thanh :
 		
	Bấm ok và run lại game để chơi lại
•	Còn nếu như bạn thành công tiêu diệt boss cuối thì sẽ hiện dòng thông báo + âm thanh sau :
 
	Bấm ok và run lại game để chơi lại

Các kỹ thuật lập trình đã sử dụng
•	Vector, con trỏ
•	Xử lý va chạm (Còn chưa được chuẩn lắm)
•	SDL2 (SLD2_image, SDL2_mixer, SLD2_ttf)
•	Kỹ thuật Texture font, Mouse event, Key event
•	Sound Effects and Music
•	Vòng lặp
•	Mảng tĩnh
•	Xâu
•	Chia file cho dễ quản lý 
•	Kế thừa trong Class 

Kết luận
•	Ý tưởng của game được tham khảo ở https://phattrienphanmem123az.com/ (phiên bản SDL cũ) + tự học trên Lazyfoo + tự code lại bằng SDL2 + phát triển thêm 1 số tính năng ( menu + âm thanh + boss ,….)
•	Học được cách sử dụng C++ và SDL2 để tự tạo được một game cơ bản cho bản thân 
•	Biết cách chia nhỏ file + class để dễ quản lý dự án hơn


