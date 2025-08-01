#include"sh1106.h"
#include"Image_BMP.h"
#include"font5x7.h"
#include"font7x10.h"


// Global variables
int SOC_Var = 65 ;
int STOP_W_Var = 1.5;         //stopwatch_screen : 00:00:00          LC update every 1 sec.
                              //                   hr:M :sec


void main()
{

    HAL_Init();
    SystemClock_Config(); // your clock configuration
    MX_GPIO_Init();
    MX_SPI2_Init();       // Assuming SH1106_SPI_PORT is SPI2

    // Initialize OLED displaya
    SH1106_Init();

    // Set normal orientation
    SH1106_Orientation(LCD_ORIENT_NORMAL);

    // 1?? Draw fullscreen bitmap
    LCD_DrawBitmapFullscreen(gImage_Image_BMP);
    SH1106_Flush();

    HAL_Delay(2000); // 2 seconds

    // 2?? Clear display
    SH1106_Fill(0x00);
    SH1106_Flush();

    // 3?? Display text lines
    uint8_t y = 0;

    LCD_PutStr(0, y, "SOC:",  fnt7x10 );
    y += Font_7x10.font_Height + 2;

    LCD_PutStr(0, y, "STOP_W:",  fnt7x10 );
    y += Font_7x10.font_Height + 2;

    LCD_PutStr(0, y, "T_Voltage:",  fnt7x10 );

     flush to update display
    SH1106_Flush();

    while (1)
    {
        // Clear SOC value area (x=40, y=0)
        LCD_FillRect(40, 0, 127, Font_7x10.font_Height);
        // Draw updated SOC value
        LCD_PutIntU(40, 0, SOC_Var, &Font_7x10);

        // Clear STOP_W value area (x=70, y=Font_7x10.font_Height + 2)
        LCD_FillRect(70, Font_7x10.font_Height + 2, 127, (2 * Font_7x10.font_Height + 2));
        // Draw updated STOP_W value
        LCD_PutIntU(70, Font_7x10.font_Height + 2, STOP_W_Var, &Font_7x10);

        // Flush only updated areas to display
        SH1106_Flush();

        HAL_Delay(5000); // 5 seconds
    }
}