#include "splashkit.h"

#define MAX_ITERATION 1000.0

color iteration_color(int iteration)
{
    double hue;

    if(iteration >= MAX_ITERATION)
    {
        return COLOR_BLACK;
    }
    else
    {
        hue = 0.5  +  (iteration / MAX_ITERATION);
        if(hue > 1)
        {
            hue = hue - 1;
        }
        return hsb_color(hue, 0.8, 0.9);
    }
    
}

color mandelbrot_color(double mb_x , double mb_y)
{
    double xtemp;
    double x;
    double y;
    int iteration;
    x = mb_x;
    y = mb_y;
    iteration = 0;
    while(x*x - y*y <= 4 and iteration < MAX_ITERATION)
    {
        xtemp = x*x - y*y + mb_x;
        y = 2 *x*y + mb_y;
        x = xtemp;
        iteration++;
    }
    return iteration_color(iteration);

}

void draw_mandelbrot(double start_mb_x, double start_mb_y,double mb_width, double mb_height)
{
    double scale_width;
    double scale_height;
    int x;
    int y;
    double mx;
    double my;
    color mb_color;
    
    scale_width = mb_width / screen_width();
    scale_height = mb_height / screen_height();
    x = 0;
    while(x < screen_width())
    {  
        y = 0;
        while(y < screen_height())
        {    
        mx = start_mb_x + x*scale_width;
        my = start_mb_y + y*scale_height;
        mb_color = mandelbrot_color(mx,my);
        draw_pixel(mb_color , x , y);
        y = y+1;
        }
        x = x+1;
       
    }

}

int main()
{
    double start_mb_x;
    double start_mb_y;
    double mb_width;
    double mb_height;
    double new_mb_width;
    double new_mb_height;
    double user_click_x;
    double user_click_y;
    start_mb_x = -2.5;
    start_mb_y = -1.5;
    mb_width = 4;
    mb_height = 3;
    open_window("Mandelbrot" , 320 , 240);

    while(not quit_requested())
    {

        process_events();
      
        
        draw_mandelbrot(start_mb_x, start_mb_y,mb_width,mb_height);
        refresh_screen(60);
        if(mouse_clicked(LEFT_BUTTON))
        {
            new_mb_width = mb_width / 2;
            user_click_x = start_mb_x + mouse_x() / screen_width() * mb_width;
            start_mb_x = user_click_x - new_mb_width/2;
            mb_width = new_mb_width;
            new_mb_height = mb_height / 2;
            user_click_y = start_mb_y + mouse_y() / screen_height() * mb_height;
            start_mb_y = user_click_y - new_mb_height / 2;
            mb_height = new_mb_height;

        }    
        if(mouse_clicked(RIGHT_BUTTON))
        {
         new_mb_width = mb_width * 2;
         user_click_x = start_mb_x + mouse_x() / screen_width() * mb_width;
         start_mb_x =  user_click_x - new_mb_width/2;
         mb_width = new_mb_width;
         new_mb_height = mb_height * 2;
         user_click_y = start_mb_y + mouse_y() / screen_height() * mb_height;
         start_mb_y =  user_click_y - new_mb_height/2;
         mb_height = new_mb_height;    
        }
        refresh_screen(60);    
    }

    return 0;
}