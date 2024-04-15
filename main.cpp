#include <SDL.h>
#include <stdio.h>
#include "BaseObject.h"
#include "Common_Function.h"
#include "MainObject.h"
#include "AmoObject.h"
#include "ThreatObject.h"

TTF_Font *font =NULL;
int game_score=0;//Điểm khi bắt đầu game


void RenderScore();// Render điểm
void RenderTime();
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
    bool ret1 = background.LoadImg("picture/bg4800.png", gRenderer);
    if (!ret1) return 0;

    // Tạo đối tượng nhân vật
    MainObject plane_object;
    bool ret2 = plane_object.LoadImg("picture/airplane2.png", gRenderer);
    if (!ret2) return 0;
    plane_object.SetRect(100, 200); // Thiết lập vị trí ban đầu của nhân vật
    plane_object.SetRectSize(80,46);// Thiết lập kích thước ban đầu của nhân vật

    //Tạo đối tượng đệ tử
    MainObject plane2_object;
    bool ret =plane2_object.LoadImg("picture/plane_fly1.png",gRenderer);
    if(!ret)return 0;
    plane2_object.SetRect(100,230);//Thiết lập vị trí ban đầu của đệ tử
    plane2_object.SetRectSize(40,23);//Thiết lập kích thước ban đầu của đệ tử


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
    // Main loop
    bool quit = false;
    SDL_Event e;

    unsigned int mark_value=0;

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

        // Xử lý di chuyển của các đạn( bắt buộc phải để sau background và plane_object)
        plane_object.HandleAmo(gRenderer);

        //Render đệ tử
        plane2_object.SetRect(plane_object.GetRect().x+10,plane_object.GetRect().y+60);//Set đệ tử đi theo sư huynh
        plane2_object.Render(gRenderer);


        //Render Threat
        for(int tt=0;tt<NUM_THREAT;tt++)
       {
            ThreatObject *p_threat = (p_threats+tt);
            if(p_threat!=NULL)
           {
                p_threat -> HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);// Xử lí di chuyển ThreatObject
                p_threat -> Render(gRenderer);//Render ThreatObject
                p_threat->FireAmo(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);//Bắn đạn

                //Check va chạm MainObject và Threat
                bool is_col=CheckCollisision(plane_object.GetRect(),p_threat->GetRect());
                if(is_col==true)
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
        SDL_Color text_color1 ={255,0,0};// Màu chữ đỏ
         std::string SCORE ="Score :" +std::to_string(game_score);

         SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, SCORE.c_str(), text_color1);
            if (scoreSurface == nullptr) {
            // Xử lý lỗi khi không thể tạo bề mặt văn bản
            printf("Failed to create score surface! SDL_ttf Error: %s\n", TTF_GetError());
            return ;
        }
                // Tạo texture từ surface
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer, scoreSurface);
            if (scoreTexture == nullptr) {
            // Xử lý lỗi khi không thể tạo texture từ surface
            printf("Failed to create score texture! SDL Error: %s\n", SDL_GetError());
            return ;
        }

            // Lấy kích thước của surface văn bản
            const int text_x =500;
            const int text_y =20;
            int textWidth = scoreSurface->w;
            int textHeight = scoreSurface->h;

            // Giải phóng surface văn bản không cần dùng nữa
            SDL_FreeSurface(scoreSurface);

            // Thiết lập vị trí hiển thị văn bản
            SDL_Rect textRect = {text_x, text_y, textWidth, textHeight};

            // Vẽ texture văn bản lên màn hình
            SDL_RenderCopy(gRenderer, scoreTexture, NULL, &textRect);

            // Giải phóng texture văn bản không cần dùng nữa
            SDL_DestroyTexture(scoreTexture);


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
        // Xử lý lỗi khi không thể tạo texture từ surface
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



