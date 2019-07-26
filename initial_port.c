//ポート初期設定

void initial_port(void);

void initial_port(void)
{
	//IOポート初期設定
	//P0~
	R_PG_IO_PORT_Set_P00();//SW4_2 pull-up
	R_PG_IO_PORT_Set_P01();//RDn 未使用 入力 pull-up
	R_PG_IO_PORT_Set_P02();//TXD2 未使用 出力L
	R_PG_IO_PORT_SetOpenDrain_P02();//ロードセル2,DZ出力 オープンドレイン
	R_PG_IO_PORT_Write_P02(0x01);//イニシャルOpen
	R_PG_IO_PORT_Set_P03();//RXD2 未使用 出力L
	R_PG_IO_PORT_SetOpenDrain_P03();//ロードセル2,HOLD出力 オープンドレイン
	R_PG_IO_PORT_Write_P03(0x01);//イニシャル Open
	R_PG_IO_PORT_Set_P04();//IO4 未使用 出力L //インバータ回転 CCW運転・停止
	R_PG_IO_PORT_Write_P04(0X00);//イニシャル停止
	R_PG_IO_PORT_Set_P05();//CS2n_WAITn 未使用 入力 pull-up
	
	//P1~
	R_PG_IO_PORT_Set_P10();//SW1 割り込みで使用 pull-up
	R_PG_IO_PORT_Set_P11();//SW2 割り込みで使用 pull-up
	R_PG_IO_PORT_Set_P12();//CANSTB 100kΩ pull-down
	R_PG_IO_PORT_Set_P13();//USB0VBUSENN 4.7kΩ pull-down
	R_PG_IO_PORT_Set_P14();//SCK2 未使用 出力L
	R_PG_IO_PORT_Write_P14(0x00);
	
	//P2~
	R_PG_IO_PORT_Set_P20();//MTCLKB 未使用 出力L
	R_PG_IO_PORT_Write_P20(0x00);
	R_PG_IO_PORT_Set_P21();//MTCLKA 未使用 出力L
	R_PG_IO_PORT_Write_P21(0x00);
	R_PG_IO_PORT_Set_P22();//CRX1 CANトランシーバ出力と接続 入力ポート
	R_PG_IO_PORT_Set_P23();//CTX1 CANトランシーバ入力と接続 出力L
	R_PG_IO_PORT_Write_P23(0x00);
	R_PG_IO_PORT_Set_P24();//D11 未使用 出力L
	R_PG_IO_PORT_Write_P24(0x00);
	R_PG_IO_PORT_Set_P25();//SCL1 ソレノイド2駆動 
	R_PG_IO_PORT_Write_P25(0x00);//イニシャルL(OFF)
	R_PG_IO_PORT_Set_P26();//SDA1 未使用 pull-up
	R_PG_IO_PORT_SetOpenDrain_P26();//ロードセル DZ出力 オープンドレイン
	R_PG_IO_PORT_Write_P26(0x01);//イニシャル open
	
	//P3~
	R_PG_IO_PORT_Set_P30();//MTCLKD 未使用 出力L
	R_PG_IO_PORT_Write_P30(0x00);
	R_PG_IO_PORT_Set_P31();//MTCLKC 未使用 出力L
	R_PG_IO_PORT_Write_P31(0x00);
	R_PG_IO_PORT_Set_P32();//MTIO3C 未使用 出力L
	R_PG_IO_PORT_Write_P32(0x00);
	R_PG_IO_PORT_Set_P33();//MTIO3A LED3 Lで発光
	R_PG_IO_PORT_Write_P33(0x01);
	R_PG_IO_PORT_Set_P34();//IO7 未使用 出力L
	R_PG_IO_PORT_SetOpenDrain_P34();//DCブラシレス2 CW/CCW制御出力
	R_PG_IO_PORT_Write_P34(0x01);//イニシャルCCW方向
	R_PG_IO_PORT_Set_P35();//CANEN CAN未使用 pull-up 出力L
	R_PG_IO_PORT_Write_P35(0x00);
	
	//P4~
	//R_PG_IO_PORT_Set_P40();//AN000 可変抵抗に接続
	//R_PG_IO_PORT_Set_P41();//AN001 サーボモータのフィードバックに接続
	//R_PG_IO_PORT_Set_P42();//AN002 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P43();//AN003 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P44();//AN100 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P45();//AN101 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P46();//AN102 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P47();//AN103 未使用 出力ポートに設定不可
	
	//P5~
	//R_PG_IO_PORT_Set_P50();//P50 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P51();//P51 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P52();//A7 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P53();//A6 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P54();//DA0 DA変換ポートで使用
	//R_PG_IO_PORT_Set_P55();//DA1 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P56();//P56 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P57();//P57 未使用 出力ポートに設定不可
	
	//P6~
	//R_PG_IO_PORT_Set_P60();//A5 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P61();//A4 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P62();//A3 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P63();//A2 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P64();//A1 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_P65();//A0 未使用 出力ポートに設定不可
	
	//P7~
	R_PG_IO_PORT_Set_P70();//POE0n 未使用 100kΩ pull-up
	R_PG_IO_PORT_Set_P71();//LED0 出力Lで発光
	R_PG_IO_PORT_Write_P71(0x01);
	R_PG_IO_PORT_Set_P72();//MTIOC4Aで使用 LED1出力 Lで発光
	R_PG_IO_PORT_Write_P72(0x01);
	R_PG_IO_PORT_Set_P73();//LED2出力 Lで発光
	R_PG_IO_PORT_Write_P73(0x01);
	R_PG_IO_PORT_Set_P74();//D2_MTIOC3D 未使用 出力L
	R_PG_IO_PORT_Write_P74(0x00);
	R_PG_IO_PORT_Set_P75();//D1_MTIOC4C 未使用 出力L
	R_PG_IO_PORT_Write_P75(0x00);
	R_PG_IO_PORT_Set_P76();//D0_MTIOC4D 未使用 出力L
	R_PG_IO_PORT_Write_P76(0x00);
	
	//P8~
	R_PG_IO_PORT_Set_P80();//A9_MTIC5W 未使用 出力L
	R_PG_IO_PORT_Write_P80(0x00);
	R_PG_IO_PORT_Set_P81();//A8_MTIC5V 未使用 出力L
	R_PG_IO_PORT_Write_P81(0x00);
	R_PG_IO_PORT_Set_P82();//MTIC5U 未使用 出力L
	R_PG_IO_PORT_Write_P82(0x00);
	
	//P9~
	R_PG_IO_PORT_Set_P90();//MTIOC7D 未使用 出力L
	R_PG_IO_PORT_Write_P90(0x00);
	R_PG_IO_PORT_Set_P91();//MTIOC7C 未使用 出力L
	R_PG_IO_PORT_Write_P91(0x00);
	R_PG_IO_PORT_Set_P92();//MTIOC6D 未使用 出力L
	R_PG_IO_PORT_Write_P92(0x00);
	R_PG_IO_PORT_Set_P93();//MTIOC7B 未使用 出力L
	R_PG_IO_PORT_Write_P93(0x00);
	R_PG_IO_PORT_Set_P94();//MTIOC7A 未使用 出力L
	R_PG_IO_PORT_Write_P94(0x00);
	R_PG_IO_PORT_Set_P95();//MTIOC6B 未使用 出力L
	R_PG_IO_PORT_Write_P95(0x00);
	R_PG_IO_PORT_Set_P96();//POE4n 100kΩ pull-up
	
	//PA~
	R_PG_IO_PORT_Set_PA0();//MTIOC6C 未使用 出力L
	R_PG_IO_PORT_Write_PA0(0x00);
	R_PG_IO_PORT_Set_PA1();//MTIOC6A 未使用 出力L
	R_PG_IO_PORT_Write_PA1(0x00);
	R_PG_IO_PORT_Set_PA2();//IO5
	R_PG_IO_PORT_SetOpenDrain_PA2();//DCブラシレス CW/CCW切り替え
	R_PG_IO_PORT_Write_PA2(0x01);//イニシャル Lo(CCW方向)
	R_PG_IO_PORT_Set_PA3();//MTIOC2A 未使用 出力L
	R_PG_IO_PORT_Write_PA3(0x00);
	R_PG_IO_PORT_Set_PA4();//ADTRG0n 100kΩ pull-up
	R_PG_IO_PORT_SetOpenDrain_PA4();//ロードセル HOLD出力 オープンドレイン
	R_PG_IO_PORT_Write_PA4(0x01);//イニシャル open
	R_PG_IO_PORT_Set_PA5();//ADTRG1n 100kΩ pull-up
	R_PG_IO_PORT_Set_PA6();//IO6 未使用 出力L
	R_PG_IO_PORT_Write_PA6(0x00);
	
	//PB~
	R_PG_IO_PORT_Set_PB0();//A14 未使用 出力L
	R_PG_IO_PORT_Write_PB0(0x00);
	//R_PG_IO_PORT_Set_PB1();//RXD0 RS-485 ロードセル通信
	//R_PG_IO_PORT_Write_PB1(0x00);
	//R_PG_IO_PORT_Set_PB2();//TXD0 RS-485 ロードセル通信
	//R_PG_IO_PORT_Write_PB2(0x00);
	R_PG_IO_PORT_Set_PB3();//MTIOC0A 未使用 出力L
	R_PG_IO_PORT_Write_PB3(0x00);
	R_PG_IO_PORT_Set_PB4();//未使用 出力L
	R_PG_IO_PORT_Write_PB4(0x00);
	R_PG_IO_PORT_Set_PB5();//LINTXD 未使用 出力L
	R_PG_IO_PORT_Write_PB5(0x00);	
	R_PG_IO_PORT_Set_PB6();//LINRXD 4.7kΩ pull-up
	R_PG_IO_PORT_Set_PB7();//A19 未使用 出力L
	R_PG_IO_PORT_Write_PB7(0x00);	
	
	//PC~
	//R_PG_IO_PORT_Set_PC0();//PC0 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_PC1();//PC1 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_PC2();//PC2 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_PC3();//PC3 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_PC4();//PC4 未使用 出力ポートに設定不可
	//R_PG_IO_PORT_Set_PC5();//CANENRRn 未使用 出力ポートに設定不可
	
	//PD~
	R_PG_IO_PORT_Set_PD0();//GTIOC3B 未使用 出力L
	R_PG_IO_PORT_Write_PD0(0x00);
	R_PG_IO_PORT_Set_PD1();//GTIOC3A 未使用 出力L
	R_PG_IO_PORT_Write_PD1(0x00);
	R_PG_IO_PORT_Set_PD2();//インバータ回転 CW運転・停止
	R_PG_IO_PORT_Write_PD2(0x00);//イニシャル 停止
	//R_PG_IO_PORT_Set_PD3();//TXD1 RS232C TX
	R_PG_IO_PORT_Set_PD4();//SCK1 未使用 出力L
	R_PG_IO_PORT_Write_PD4(0x00);
	//R_PG_IO_PORT_Set_PD5();//RXD1 RS232C RX
	R_PG_IO_PORT_Set_PD6();//GTIOC0B 未使用 出力L
	R_PG_IO_PORT_Write_PD6(0x00);
	//R_PG_IO_PORT_Set_PD7();//CTS0RTS0 未使用 出力L
	//R_PG_IO_PORT_Write_PD7(0x00);
	//GTIOC0Aとして使用
	
	//PE~
	R_PG_IO_PORT_Set_PE0();//WR1n 4.7kΩ pull-up
	R_PG_IO_PORT_Set_PE1();//USB0OVRCURA 100kΩ pull-up
	//R_PG_IO_PORT_Set_PE2();//NMI 4.7kΩ pull-up 出力設定不可
	R_PG_IO_PORT_Set_PE3();//IRQ2-DS SW3 SW-ONでL
	R_PG_IO_PORT_Set_PE4();//A10 未使用 出力L
	R_PG_IO_PORT_Write_PE4(0x00);
	R_PG_IO_PORT_Set_PE5();//USB0VBUS
	
	//PF~
	//R_PG_IO_PORT_Set_PF0();//TMS E1用
	//R_PG_IO_PORT_Set_PF1();//TRST# E1用
	R_PG_IO_PORT_Set_PF2();//IRQ5 100kΩ pull-up
	R_PG_IO_PORT_SetOpenDrain_PF2();//DCブラシレス2 START/STOP制御用(オープンドレイン)
	R_PG_IO_PORT_Write_PF2(0x01);//イニシャル STOP設定
	R_PG_IO_PORT_Set_PF3();//IO1 未使用 出力L 
	R_PG_IO_PORT_SetOpenDrain_PF3();//DCブラシレス START/STOP制御用(オープンドレイン)
	R_PG_IO_PORT_Write_PF3(0x01);//イニシャル STOP設定
	R_PG_IO_PORT_Set_PF4();//IO0 ソレノイド1駆動
	R_PG_IO_PORT_Write_PF4(0x00);//イニシャルL(OFF)
	
	
	//PG~
	R_PG_IO_PORT_Set_PG0();//DLCDD4 LCD用
	R_PG_IO_PORT_Set_PG1();//DLCDD5 LCD用
	R_PG_IO_PORT_Set_PG2();//DLCDD6 LCD用
	R_PG_IO_PORT_Set_PG3();//DLCDD7 LCD用
	R_PG_IO_PORT_Set_PG4();//DLCDRS LCD用
	R_PG_IO_PORT_Set_PG5();//DLCDE LCD用
	R_PG_IO_PORT_Set_PG6();//LINNSLP 出力L(LINスリープ)
	R_PG_IO_PORT_Write_PG6(0x00);
}

//シリアルインターフェース初期設定

void initial_SCI(void);

void initial_SCI(void)
{
	//SCI0 ロードセル通信 RS-485
	R_PG_SCI_Set_C0();
	//SCI1
	R_PG_SCI_Set_C1();//TRXD1, RS232通信用
}
	

//割り込み初期設定
/*
void initial_IRQ(void);

void initial_IRQ(void)
{
	//IRQ0 初期設定
	R_PG_ExtInterrupt_Set_IRQ0();//pull-up 立下り検出 優先：10
	
	//IRQ1 初期設定
	R_PG_ExtInterrupt_Set_IRQ1();//pull-up 立下り検出 優先：8
	
	//IRQ3 初期設定
	R_PG_ExtInterrupt_Set_IRQ3();//pull-up Low検出 優先：2 スパイラルのアラーム検出用
	
}
*/

//MTU初期設定
/*
void initial_MTU(void);

void initial_MTU(void)
{
	
	R_PG_Timer_Set_MTU_U0_C3();//MTIO3の設定
	R_PG_Timer_Set_MTU_U0_C4();//MTIO4の設定
	
}
*/

	
//12bit A/D変換初期設定
void initial_S12AD(void);

void initial_S12AD(void)
{
	R_PG_ADC_12_Set_S12AD0();//12bit ADコンバータ設定
	//AD設定
	//連続スキャンモード
	//AN000,AN001,AN002 有効
	//AD変換終了割り込み有効
	
}

//DA変換ポート初期設定
void initial_DA(void);

void initial_DA(void)
{
	R_PG_DAC_Set_C0();//ステージ回転数指令出力
	R_PG_DAC_Set_C1();//スパイラル回転数指令出力
	
	R_PG_DAC_SetWithInitialValue_C0(0x0000);
	R_PG_DAC_SetWithInitialValue_C1(0x0000);
}


//CMT初期設定
void initial_CMT(void);

void initial_CMT(void)
{
	R_PG_Timer_Set_CMT_U0_C0();
	R_PG_Timer_Set_CMT_U0_C1();
}


