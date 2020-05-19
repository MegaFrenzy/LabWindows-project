/**
 * @Description: 流量计自动校准部分
 * @Author: MegaFrenzy
 * @CreateTime: 2020-05-18 16:19
 * 
 * 结算区：当存在五组数据并其误差均在1.5%内，则中断并弹窗提示校准成功，给出相关数据
 * 验证区：对每次结果进行验证，每当数据误差＞1.5%，交由调整区重新配置参数
 * 调整区：根据最近一次脉冲流量和重量参数重新计算调整脉冲流量，使得误差进一步减少
 */

recd[pos] = Weight - offset_Weight;
//结算区
if (pos - recpos >= 4) {
    int t0 = 0;
    
    for (int p = recpos; p <= pos; p++) {
        t0 += abserror(recd, p);
    }
    char dscpt[ 50]={0} ;
    sprintf(dscpt, "校准成功！\n脉冲流量为%d\n请更换流量计继续测试", pulse_flow);
    if (t0 >= 5) {
        MessageBoxA(0, dscpt, "自动校准数据区即将清空,请记录相关数据", 0);
        memset(recd, 0, sizeof( double)*100);
        pos = 0;
        recpos = 0;
        token = 0;
        t0 = 0;
    } else {
        SetCtrlVal_Str(panelHandle, PANEL_TEXTMSG_TISI2, "近五次数据不符合要求，即将重新计算···");
        token = 1;
    }
}

//验证区
srvy = abserror(recd, pos);
if (srvy) {
    char dscription[50]={0} ;
    sprintf(dscription, "第%d组数据通过校验", pos + 1);
    SetCtrlVal_Str(panelHandle, PANEL_TEXTMSG_TISI2, dscription);
} else {
    SetCtrlVal_Str(panelHandle, PANEL_TEXTMSG_TISI2, "最新数据不符合要求，即将重新计算···");
    Sleep(1000);
    token = 1;
}

//调整区
if (1 == token) {
    pulse_flow = (int) 500 * pulse_flow / (recd[pos]);
    recpos = pos + 1;
    token = 0;
    //重新设定脉冲流量区
    {
        sendPulseFlow(pulse_flow);
    }
}

if (++pos > 100) {
    pos = 0;
    recpos = 0;
}

//辅助函数
int abserror(double *array, int n)
{
	double k = (array[n] - 500) > 0 ? array[n] - 500 : 500 - array[n];
	return  k - 1.50 > 0 ? 0 : 1;
}
void sendPulseFlow(int pulse_flow) {
	unsigned char buff[8];
    unsigned int val = pulse_flow;
    buff[0] = 0xBB;
    buff[1] = 0xA1;
    buff[2] = 0xC8;
    buff[3] = (val >> 24) & 0xff;
    buff[4] = (val >> 16) & 0xff;
    buff[5] = (val >> 8) & 0xff;
    buff[6] = val & 0xff;
    buff[7] = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5] + buff[6];
    ComWrtByte(COM_port, buff[0]);
    ComWrtByte(COM_port, buff[1]);
    ComWrtByte(COM_port, buff[2]);
    ComWrtByte(COM_port, buff[3]);
    ComWrtByte(COM_port, buff[4]);
    ComWrtByte(COM_port, buff[5]);
    ComWrtByte(COM_port, buff[6]);
    ComWrtByte(COM_port, buff[7]);
    Delay(0.5);
    char dscription[50]={0};
    sprintf(dscription, "已将脉冲流量设为%d", pulse_flow);
    SetCtrlVal(panelHandle, PANEL_NUM_PULS, pulse_flow);
    SetCtrlVal_Str(panelHandle, PANEL_TEXTMSG_TISI2, dscription);
}