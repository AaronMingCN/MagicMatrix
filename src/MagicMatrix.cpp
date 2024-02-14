/*
 * @File :  MagicMatrix.cpp
 * @Time :  2024/02/13 10:32:36
 * @Vers :  1.0
 * @Desc :  MagicMatrix魔法矩阵,主程序
 */

#include "MMDebug.hpp"

#include "MMInit.hpp"


void setup()
{
    MMInit(); // 初始化系统
}

void loop()
{

    pinMode(PIN_SR, INPUT);
    if (digitalRead(PIN_SR))
        matrix.setBrightness(100);
    else
        matrix.setBrightness(30);
#ifdef MMDEBUG
    mmdebug.TestRTC();
    mmdebug.TestDHT();
    // mmdebug.TestSD();
    // mmdebug.TestMMRamBmp();
#endif

    if (irrecv.decode()) { // 如果红外线读取到数据
        Serial.println(irrecv.decodedIRData.command); // 向串口打印
        switch (irrecv.decodedIRData.command) {
        case IRK_0:
            mmfill.PixTest();
            break;
        case IRK_1:
            mmfill.RowFill();
            break;
        case IRK_2:
            mmfill.ColFill();
            break;
        case IRK_3:
            mmfill.DiagFill_1();
            break;
        case IRK_4:
            mmfill.SnakeFill();
            break;
        case IRK_5:
            mmfill.RectFill();
            break;
        case IRK_6:
            mmfill.AlarmLamp();
            break;
            // case IRK_6: RectSnakeFill(); break;
            // case K_7: Rain(); break;
        }
        irrecv.resume(); // 恢复读取
    }

    digitalWrite(PIN_LED_BUILTIN, HIGH);
    mmsd.DrawBitmap("pixil1.bmp");
    digitalWrite(PIN_LED_BUILTIN, LOW);
    mmscr.Update();
    delay(1000);
    digitalWrite(PIN_LED_BUILTIN, HIGH);
    mmsd.DrawBitmap("pixil3.bmp");
    digitalWrite(PIN_LED_BUILTIN, LOW);
    mmscr.Update();
    delay(1000);
}
