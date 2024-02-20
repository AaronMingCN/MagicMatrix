/*
 * @File :  MagicMatrix.cpp
 * @Time :  2024/02/13 10:32:36
 * @Vers :  1.0
 * @Desc :  MagicMatrix魔法矩阵,主程序
 */

#include "MMDebug.hpp"

#include "MMHardware.hpp"
#include "MMMain.hpp"

#include "MMFunc/MMFuncPool.hpp"


void setup()
{
    delay(1000); // 等待一秒bootloader
    // 系统初始化
    mmmain.Init();
    // mmhardware.Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop()
{
    // 执行主循环
    mmmain.MainLoop();
    if (mmhardware.GetPIRR())
        mmhardware.matrix.setBrightness(50);
    else
        mmhardware.matrix.setBrightness(20);
#ifdef MMDEBUG
    mmdebug.TestRTC();
    mmdebug.TestDHT();
    // mmdebug.TestSD();    // mmdebug.TestMMRamBmp();
#endif

    if (mmhardware.irrecv.decode()) { // 如果红外线读取到数据
        Serial.println(mmhardware.irrecv.decodedIRData.command); // 向串口打印
        switch (mmhardware.irrecv.decodedIRData.command) {
        case IRK_0:
            mmfill.PixTestLogicalOrder();
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
        case IRK_7:
            mmfuncpool.ExecFunc(MMF_ID_DISPTIME_1);
            break;
            // case K_7: Rain(); break;
        }
        mmhardware.irrecv.resume(); // 恢复读取
    }

    digitalWrite(PIN_LED_BUILTIN, HIGH);
    mmsd.DrawBitmap("pixil1.bmp");
    digitalWrite(PIN_LED_BUILTIN, LOW);
    mmscr.Update();
    delay(1000);

    digitalWrite(PIN_LED_BUILTIN, HIGH);
    mmsd.DrawBitmap("pixil2.bmp");
    digitalWrite(PIN_LED_BUILTIN, LOW);
    mmscr.Update();
    delay(1000);    

    digitalWrite(PIN_LED_BUILTIN, HIGH);
    mmsd.DrawBitmap("pixil3.bmp");
    digitalWrite(PIN_LED_BUILTIN, LOW);
    mmscr.Update();
    delay(1000);

    digitalWrite(PIN_LED_BUILTIN, HIGH);
    mmsd.DrawBitmap("pixil4.bmp");
    digitalWrite(PIN_LED_BUILTIN, LOW);
    mmscr.Update();
    delay(1000);
}
