/*
 * @File :  MagicMatrix.cpp
 * @Time :  2024/02/13 10:32:36
 * @Vers :  1.0
 * @Desc :  MagicMatrix魔法矩阵,主程序
 */

#include "MMDebug.hpp"
#include "MMDefine.hpp"
#include "MMFill.hpp"
#include "MMGrap.hpp"
#include "MMRamBmp.hpp"
#include "MMSD.hpp"

#include "MMFPSetup.hpp"


void setup()
{

    matrix.begin();
    // // matrix.setTextWrap(false);
    matrix.setBrightness(M_BRIGHT); // 设置矩阵屏幕亮度0~255

    mmfill.MatrixTest(); // 测试矩阵

    Serial.begin(9600); // 打开串口通信
    for (uint8_t i = 0; i < 100; ++i) { // 等待串口连接成功，防止RTOS崩溃
        if (Serial)
            break;
        delay(10);
    }
    // while(!Serial) delay(10); // 等待串口通信成功

    // matrix.setTextColor(colors[0]);
    irrecv.enableIRIn(); // 打开红外遥控接收器
    dht.begin(); // 打开dht温湿度传感器

    // 调用功能池初始化
    MMFPSetup();
    FPool.Exec(MMF_ID_MATRIXTEST);
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
