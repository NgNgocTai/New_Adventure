#include <SDL.h>
#include <stdio.h>
#include "BaseObject.h"
#include "Common_Function.h"
#include "MainObject.h"
#include "AmoObject.h"
#include "ThreatObject.h"
#include "BossObject.h"
TTF_Font *font =NULL;
int game_score=0;//Điểm khi bắt đầu game
bool change=false;


void RenderScore();// Render điểm
void RenderTime();
int ShowMenu(SDL_Renderer *des);
// Hàm khởi tạo SDL và cửa sổ
bool init() {
    // Khởi tạo SDL_VIDEO để sử dụng video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL không thể khởi tạo! Lỗi SDL: %s\n", SDL_GetError());
        return false;
    }

    // Thiết lập chất lượng phóng to và thu nhỏ của renderer
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Tạo cửa sổ SDL với tên "SDL game", kích thước mặc định, và hiển thị
    gWindow = SDL_CreateWindow("SDL game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Không thể tạo cửa sổ! Lỗi SDL: %s\n", SDL_GetError());
        return false;
    }

    // Tạo renderer với phần cứng hỗ trợ và thiết lập màu nền là màu trắng
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Không thể tạo renderer! Lỗi SDL: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Khởi tạo SDL_image để sử dụng PNG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image không thể khởi tạo! Lỗi SDL_image: %s\n", IMG_GetError());
        return false;
    }
    //Khởi tạo mixer
      Mix_Init(MIX_INIT_MP3);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)==-1)
        return false;

    //Đọc file âm thanh
    gGun1=Mix_LoadWAV("sound/Gun1.wav");
    gGun2=Mix_LoadWAV("sound/Gun2.wav");
    gEx1=Mix_LoadWAV("sound/Explosion1.wav");
    gEx2=Mix_LoadWAV("sound/Explosion2.wav");
    gWin=Mix_LoadWAV("sound/Congratulation.wav");
    gBoss=Mix_LoadWAV("sound/Explosion+5.wav");
    //Init text
    if(TTF_Init()==-1){return false;}

    font = TTF_OpenFont("picture/SSWB.ttf",20);
    if(font==NULL){return false;}
     return true;

}

int main(int argc, char* argv[]) {

    // Khởi tạo SDL
    if (!init()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    // Tải media cần thiết
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        return -1;
    }


    // Tạo đối tượng background
    BaseObject background;
    bool ret1 = background.LoadImg("picture/background.png", gRenderer);
    if (!ret1) return 0;
    background.SetRectSize(WIDTH_BACKGROUND,HEIGHT_BACKGROUND);

    // Tạo đối tượng nhân vật
    MainObject plane_object;
    if(!boss_render){
        bool ret2 = plane_object.LoadImg("picture/airplane2.png", gRenderer);
        if (!ret2) return 0;
    }

    plane_object.SetRect(100, 200); // Thiết lập vị trí ban đầu của nhân vật
    plane_object.SetRectSize(80,46);// Thiết lập kích thước ban đầu của nhân vật

    //Tạo đối tượng đệ tử
    MainObject plane2_object;
    bool ret =plane2_object.LoadImg("picture/plane_fly1.png",gRenderer);
    if(!ret)return 0;
    plane2_object.SetRect(100,230);//Thiết lập vị trí ban đầu của đệ tử
    plane2_object.SetRectSize(40,23);//Thiết lập kích thước ban đầu của đệ tử

    //Tạo mảng các thiên thạch
    MainObject theorites[THEORITE_NUM];

    for(int tr = 0; tr < THEORITE_NUM; tr++)
    {
        bool render = theorites[tr].LoadImg("picture/thienthach.png", gRenderer);
        if (!render) return 0;
        theorites[tr].SetRectSize(100, 100);
        // Thiết lập vị trí của từng đối tượng theorite
        theorites[tr].SetRect(SCREEN_WIDTH / 2 + 100 *tr, 0+tr*100);
    }


    //Tạo mảng các đối tượng hiểm họa
    ThreatObject *p_threats = new ThreatObject [NUM_THREAT];
    for(int i=0;i<NUM_THREAT;i++)
    {
        ThreatObject *p_threat =(p_threats +i);//gán
        if(p_threat!=NULL)
    {
        bool ret3 = p_threat->LoadImg("picture/Threat2.png",gRenderer);
        if(!ret3)return 0;
        p_threat->SetRect(SCREEN_WIDTH+ i*320, rand()%300);// Set vị trí ngẫu nhiên khác nhau cho từng Object
        p_threat->SetRectSize( WIDTH_MAIN_OBJECT,HEIGHT_MAIN_OBJECT);
        p_threat->set_x_val(3);
        p_threat ->CreateAmo();// Tạo Amo
    }
      }


     // Tạo boss
    BossObject *p_boss =new BossObject();
    bool rett=p_boss ->LoadImg("picture/boss.png",gRenderer);
    if(!rett)return 0;
    p_boss->SetRect(SCREEN_WIDTH-300,SCREEN_HEIGHT/2-50);//Set vị trí cuối màn hình và cuối game
    p_boss->SetRectSize(WIDTH_MAIN_OBJECT*2,HEIGHT_MAIN_OBJECT*2);
    p_boss ->set_x_val(5);
    p_boss->set_y_val(4);
    p_boss ->CreateAmo();// Tao đạn cho boss


    // Main loop
    bool quit = false;
    SDL_Event e;

    unsigned int mark_value=0;

    int ret_menu= ShowMenu(gRenderer);
    if(ret_menu==1)
        quit=true;

    while (!quit) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
            //Check neu bam trai phai
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    Mix_PlayChannel(-1,gGun1,0);// Chạy âm thanh khi ấn chuột
                }
                else if(e.button.button==SDL_BUTTON_RIGHT)
                {
                    Mix_PlayChannel(-1,gGun2,0);// Chạy âm thanh khi ấn chuột
                }
            }

            // Gọi hàm HandleInputAction() của đối tượng plane_object
            plane_object.HandleInputAction(e);
        }




        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);


        // Render background
        background.Render(gRenderer);

        // Xử lí background di chuyển
        background.Move();

        // Xử lý di chuyển của nhân vật
        plane_object.HandleMove();
        // Render character
        plane_object.Render(gRenderer);

       for(int tr=0;tr<THEORITE_NUM;tr++)
       {
           theorites[tr].HandleMove_Thienthach();
           if(boss_render)
            {
                    theorites[tr].Render(gRenderer);
                    bool is_theorite=CheckCollisision(theorites[tr].GetRect(),plane_object.GetRect());
                        if(is_theorite)
                        {

                            Mix_PlayChannel(-1,gEx2,0);// Hiện âm thanh khi va chạm
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose!", NULL);// Hien ra message khi thua

                            //Xóa nốt dữ liệu khi kết thúc
                            close();
                            return 0;
                        }

       }}


        // Xử lý di chuyển của các đạn( bắt buộc phải để sau background và plane_object)
        plane_object.HandleAmo(gRenderer);

        //Render đệ tử
        plane2_object.SetRect(plane_object.GetRect().x+10,plane_object.GetRect().y+60);//Set đệ tử đi theo sư huynh
        plane2_object.Render(gRenderer);


        //Render boss
            if(game_score >=BOSS_RENDER)
        {
            p_boss -> Render(gRenderer);//Render ThreatObject
            p_boss->FireAmo(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);//Bắn đạn
            p_boss->HandleMove();
            boss_render=true;

        }
        //Gặp boss và chưa đánh dấu thì update outfit mới cho nhân vật
            if (boss_render && !change) {
                change=true;
                bool rett = plane_object.LoadImg("picture/airplane3.png", gRenderer);
                plane_object.SetRectSize(80,46);// Thiết lập kích thước ban đầu của nhân vật
                if (!rett) return 0;
                bool ret =plane2_object.LoadImg("picture/flappybird.png",gRenderer);
                plane2_object.SetRectSize(40,40);//Thiết lập kích thước ban đầu của đệ tử
                if(!ret)return 0;
                 bool re = background.LoadImg("picture/backgroundn.png", gRenderer);
                if (!re) return 0;
                background.SetRectSize(WIDTH_BACKGROUND,HEIGHT_BACKGROUND);
            }

            if(boss_render && BOSS_LIFE==1)
            {
                bool rett=p_boss ->LoadImg("picture/boss2.png",gRenderer);
                if(!rett)return 0;
                p_boss->SetRectSize(WIDTH_MAIN_OBJECT*3,HEIGHT_MAIN_OBJECT*3);
            }

        //Render Threat
        for(int tt=0;tt<NUM_THREAT;tt++)
       {
            ThreatObject *p_threat = (p_threats+tt);
            if(p_threat!=NULL)
           {
                p_threat -> HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);// Xử lí di chuyển ThreatObject
                p_threat -> Render(gRenderer);//Render ThreatObject
                p_threat->FireAmo(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);//Bắn đạn

                //Check va chạm MainObject và Threat, Boss
                    bool is_col=CheckCollisision(plane_object.GetRect(),p_threat->GetRect());
                    bool is_col2=CheckCollisision(plane_object.GetRect(),p_boss->GetRect());
                    if(is_col==true || is_col2)
                    {
                        Mix_PlayChannel(-1,gEx2,0);// Hiện âm thanh khi va chạm
                        //Hiện ra thông báo GameOver khi va chạm
                       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose! You are stupid!", NULL);


                            //Xóa nốt dữ liệu khi kết thúc
                           delete [] p_threats;
                           close();
                           return 0;


                }
                // Check va chạm đạn MainObject với Threat
                std::vector<AmoObject*> amo_list =plane_object.GetAmoList();// Lấy list đạn của MainObject
                for(int im=0;im<amo_list.size();im++)
                {
                    AmoObject* p_amo = amo_list.at(im);
                    if(p_amo!=NULL)
                    {
                        bool is_col2 = CheckCollisision(p_amo->GetRect(),p_threat->GetRect());// bool check va chạm

                        if(is_col2==true)// Khi đạn bắn trúng địch
                        {
                           game_score++;// Cập nhật điểm khi va chạm
                            //Reset vi tri
                            p_threat->Reset(SCREEN_WIDTH+ tt*400, rand()%300);
                            plane_object.RemoveAmo(im);
                            //Render âm thanh khi va chạm
                            Mix_PlayChannel(-1,gEx1,0);
                        }
                        if(game_score>=BOSS_RENDER){
                        bool is_col_boss = CheckCollisision(p_amo->GetRect(), p_boss->GetRect());
                            if (is_col_boss) {

                               BOSS_LIFE--;
                                if (BOSS_LIFE <= 0) {
                                    boss_render=false;
                                    // Thực hiện các hành động khác khi chiến thắng
                                     Mix_PlayChannel(-1,gWin,0);
                                    // In ra màn hình "You Win" khi boss_life = 0
                                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You Win", "Congratulations! You defeated the boss!", NULL);
                                    return 0;
                                }
                                // Reset vị trí của đạn
                                plane_object.RemoveAmo(im);
                                Mix_PlayChannel(-1, gBoss, 0); // Phát âm thanh khi va chạm
                            }
                        }
                    }
                }



                //Check va chạm đạn Boss với MainObject
                std::vector<AmoObject*>boss_amo = p_boss->GetAmoList();
                for (int j=0;j<boss_amo.size();j++)
                {
                    AmoObject* p_amo=boss_amo.at(j);
                    if(p_amo)
                    {
                        bool is_colBoss=CheckCollisision(p_amo->GetRect(),plane_object.GetRect());
                        if(is_colBoss)
                        {
                             //Reset vi trí đạn( Có thể viết hàm ResetAmo)
                            Mix_PlayChannel(-1,gEx2,0);// Hiện âm thanh khi va chạm
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose!", NULL);// Hien ra message khi thua

                            //Xóa nốt dữ liệu khi kết thúc
                            delete [] p_threats;
                            close();
                            return 0;
                        }
                    }

                }


                //Check va chạm đạn Threat với MainObject
                std::vector<AmoObject*> bullet_list =p_threat->GetAmoList();// Lấy list đạn của MainObject
                for(int am=0;am<bullet_list.size();am++)
                {
                    AmoObject* p_amo = bullet_list.at(am);
                    if(p_amo!=NULL)
                    {
                        bool is_col1 = CheckCollisision(p_amo->GetRect(),plane_object.GetRect());// bool check va chạm
                        if(is_col1==true)// Khi đạn bắn trúng MainObject
                        {
                            //Reset vi trí đạn( Có thể viết hàm ResetAmo)
                            Mix_PlayChannel(-1,gEx2,0);// Hiện âm thanh khi va chạm
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose!", NULL);// Hien ra message khi thua

                            //Xóa nốt dữ liệu khi kết thúc
                            delete [] p_threats;
                            close();
                            return 0;


                        }
                    }
                }



           }

       }

        RenderScore(); // In điểm ra màn hình
        RenderTime(); // Hiện thời gian ra màn hình



        // Update screen
        SDL_RenderPresent(gRenderer);
        SDL_Delay(12);

        }

    delete [] p_threats;

    // Giải phóng các resource và đóng SDL
    close();

    return 0;
}

void RenderScore(){
    //Render text
    SDL_Color text_color1 ={255,0,0}; // Màu chữ đỏ
    SDL_Color text_color2 ={0,0,255}; // Màu chữ xanh lam

    std::string SCORE ="Score: " + std::to_string(game_score);
    std::string BOSS = "Boss Life: " + std::to_string(BOSS_LIFE);

    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, SCORE.c_str(), text_color1);
    if (scoreSurface == nullptr) {
        // Xử lý lỗi khi không thể tạo bề mặt văn bản
        printf("Failed to create score surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* bossLifeSurface = TTF_RenderText_Solid(font, BOSS.c_str(), text_color2);
    if (bossLifeSurface == nullptr) {
        // Xử lý lỗi khi không thể tạo bề mặt văn bản
        printf("Failed to create boss life surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer, scoreSurface);
    if (scoreTexture == nullptr) {
        // Xử lý lỗi khi không thể tạo texture từ surface
        printf("Failed to create score texture! SDL Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture* bossLifeTexture = SDL_CreateTextureFromSurface(gRenderer, bossLifeSurface);
    if (bossLifeTexture == nullptr) {
        // Xử lý lỗi khi không thể tạo texture từ surface
        printf("Failed to create boss life texture! SDL Error: %s\n", SDL_GetError());
        return;
    }

    const int scoreTextX = 500;
    const int scoreTextY = 20;
    const int bossLifeTextX = 500;
    const int bossLifeTextY = 40;

    int scoreTextWidth = scoreSurface->w;
    int scoreTextHeight = scoreSurface->h;
    int bossLifeTextWidth = bossLifeSurface->w;
    int bossLifeTextHeight = bossLifeSurface->h;

    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(bossLifeSurface);

    SDL_Rect scoreTextRect = {scoreTextX, scoreTextY, scoreTextWidth, scoreTextHeight};
    SDL_Rect bossLifeTextRect = {bossLifeTextX, bossLifeTextY, bossLifeTextWidth, bossLifeTextHeight};

    SDL_RenderCopy(gRenderer, scoreTexture, NULL, &scoreTextRect);
    SDL_RenderCopy(gRenderer, bossLifeTexture, NULL, &bossLifeTextRect);

    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(bossLifeTexture);
}

void RenderTime()
{

    // Render text
    SDL_Color text_color2 = {0, 0, 0}; // Màu chữ

    // Lấy thời gian hiện tại tính từ khi SDL được khởi tạo (miligiây)
    Uint32 current_time = SDL_GetTicks();

    // Chuyển đổi thời gian thành giây và phút
    int seconds = (current_time / 1000) % 60;
    int minutes = (current_time / 1000) / 60;

    // Tạo chuỗi định dạng thời gian
    std::string time_string = "Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

    // Tạo bề mặt văn bản
    SDL_Surface* timeSurface = TTF_RenderText_Solid(font, time_string.c_str(), text_color2);
    if (timeSurface == nullptr) {
        // Xử lý lỗi khi không thể tạo bề mặt văn bản
        printf("Failed to create time surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Tạo texture từ surface
    SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(gRenderer, timeSurface);
    if (timeTexture == nullptr) {
        // Xử lý lỗi k
       // hi không thể tạo texture từ surface
        printf("Failed to create time texture! SDL Error: %s\n", SDL_GetError());
        return;
    }

    // Lấy kích thước của surface văn bản
    const int text_x = 800;
    const int text_y = 20;
    int textWidth = timeSurface->w;
    int textHeight = timeSurface->h;

    // Giải phóng surface văn bản không cần dùng nữa
    SDL_FreeSurface(timeSurface);

    // Thiết lập vị trí hiển thị văn bản
    SDL_Rect textRect = {text_x, text_y, textWidth, textHeight};

    // Vẽ texture văn bản lên màn hình
    SDL_RenderCopy(gRenderer, timeTexture, NULL, &textRect);

    // Giải phóng texture văn bản không cần dùng nữa
    SDL_DestroyTexture(timeTexture);
}

int ShowMenu(SDL_Renderer *des)
{
    int xm = 0, ym = 0;
    BaseObject menu;
    bool m = menu.LoadImg("picture/menu.png", gRenderer);
    if (!m) return 0;
    menu.SetRectSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                return 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    // Lấy tọa độ chuột
                    xm = event.motion.x;
                    ym = event.motion.y;

                    if (xm >= 530 && xm <= 691 && ym >= 337 && ym <= 375)
                    {
                        menu.free();
                        return 0; // Trả về 0 khi ấn play_game
                    }
                    else if (xm >= 534 && xm <= 688 && ym >= 411 && ym <= 449)
                    {
                        return 1; // Trả về 1 khi ấn Exit
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1; // Trả về 1 khi ấn Exit
                }
                break;
            default:
                break;
            }

        }
        menu.Render(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    return 1; // Trả về 1 để cho biết menu đã được đóng
}

