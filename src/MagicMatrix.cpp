#include "MMDefine.h"
#include "MMFill.h"
#include "MMGrap.h"
#include "MMDebug.h"

void setup() {
  matrix.begin();
  // // matrix.setTextWrap(false);
  matrix.setBrightness(M_BRIGHT); // 设置矩阵屏幕亮度0~255
  
  mmfill.MatrixTest();

  Serial.begin(9600); // 打开串口通信
  for (uint8_t i = 0; i < 100; ++i) { // 等待串口连接成功，防止RTOS崩溃
    if (Serial) break;
    delay(10);
  }
  // while(!Serial) delay(10); // 等待串口通信成功

  // matrix.setTextColor(colors[0]);
  irrecv.enableIRIn();
  
  // // randomSeed(analogRead(0)); // 从端口0读取模拟量,由于端口0是浮空状态所以是随机数值  
  // //PixTest();
  // //SDTest();
}

void loop() {

  #ifdef MMDEBUG
    mmdebug.TestRTC();
    // mmdebug.TestSD();
  #endif
  
  if (irrecv.decode()) { // 如果红外线读取到数据
    Serial.println(irrecv.decodedIRData.command); // 向串口打印
    switch (irrecv.decodedIRData.command) {
      case IRK_0: mmfill.PixTest(); break;
      case IRK_1: mmfill.RowFill(); break;
      case IRK_2: mmfill.ColFill(); break;
      case IRK_3: mmfill.DiagFill_1(); break;
      case IRK_4: mmfill.SnakeFill(); break;
      case IRK_5: mmfill.RectFill(); break;
      case IRK_6: mmfill.AlarmLamp(); break;
      // case IRK_6: RectSnakeFill(); break;
      // case K_7: Rain(); break;
    }
    irrecv.resume(); // 恢复读取
  }
  delay(1000);
}
