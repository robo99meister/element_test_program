/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

#include "string.h"
#include "iodefine.h"
#include "R_PG_const_supl.h"


void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void returncmd(uint8_t);
uint8_t valueascii(uint8_t);
double power_func(uint8_t, int);

int i;
int j=1;

double calPWM;

char cmd1[3];

//bool ADsendflg;
bool DCBstartflg = false;
//運転開始命令でTrue,停止命令でfalse
bool DCBintflg = false;
bool DCBrunflg = false;
//運転中のみTrue
bool DCB2startflg = false;
bool DCB2intflg = false;
bool DCB2runflg = false;
bool autoreverseflg = false;
bool ARstartflg = false;
bool ARwaitflg = false;
bool L1dzflg, L2dzflg;
bool SVmotorAutoStopflg, SVmotorRunflg;
bool DCBAutoStopflg, DCB2AutoStopflg;
bool DCBADcflg, DCB2ADcflg;
bool L1waitflg, L2waitflg;
bool L1fixflg, L2fixflg;
bool Bckt1startflg, Bckt2startflg;
bool Bckt1runflg, Bckt2runflg;
bool DCBseqflg;
bool DCB2Delayflg;
bool DCBloadstopflg, DCB2loadstopflg;
bool L1stablemonflg, L2stablemonflg;
bool L1resflg, L2resflg;
bool L1adstopflg, L2adstopflg, L1_485_receive_flag;

uint8_t Redata[4], Load_Cell_return_data[20], Load_Cell_data_request[10];
uint8_t delim;
uint8_t ShrCW, ShrCCW;
uint8_t Senddata[22];
uint8_t dataS[22];
uint8_t LED0 = 0x01;
uint8_t plsrcnt;
uint8_t k;
uint8_t Runtime = 10;
uint8_t Stoptime = 10;
uint8_t DCBruncnt = 0;
uint8_t Runtime2 = 10;
uint8_t Stoptime2 = 10;
uint8_t DCB2runcnt = 0;
uint8_t Areversetime = 30;
uint8_t ARtimecnt = 0;
uint8_t ARwaittime = 20;
uint8_t Bckt1runcnt, Bckt2runcnt;
uint8_t Bckt1ONtime, Bckt1OFFtime;
uint8_t Bckt2ONtime, Bckt2OFFtime;
uint8_t DCB2Delaytime;
uint8_t L1adstopcnt, L2adstopcnt;
uint8_t L1adstoptime = 3;
uint8_t L2adstoptime = 3;
uint8_t AD1_counter, AD2_counter;

uint16_t DAset;
uint16_t DAsetp;
uint16_t DAset2;
uint16_t CMTset;
uint16_t ADval[4], AD1_buf[5], AD2_buf[5],AD1_reg, AD2_reg;
uint16_t ADtval[2];
uint16_t pulcnt;
uint16_t PCTset;
uint16_t cntbuf;
uint16_t plssend;
uint16_t PWMvalue, PWMvalue2;
uint16_t Areverselimit = 0.8 * 4095;
uint16_t AreverseDA;
uint16_t SVruncnt = 1;
uint16_t SVstopcnt = 23;
uint16_t DCBruncnt16 = 1;
uint16_t DCBstopcnt = 20;
uint16_t DCB2runcnt16 = 1;
uint16_t DCB2stopcnt = 20;
uint16_t L1setvalue = 4096 / 2;
uint16_t L2setvalue = 4096 / 2;
uint16_t L1setvalue1 = 4096 / 2;
uint16_t L2setvalue1 = 4096 / 2;
uint16_t L1vartime, L2vartime;
uint16_t L1varcnt = 1;
uint16_t L2varcnt = 1;
uint16_t L1nval, L2nval;
uint16_t L1varval,L2varval;
uint16_t L1defval,L2defval;
uint16_t L1fixval,L2fixval;
uint16_t L1tcnt = 0;
uint16_t L2tcnt = 0;
uint16_t L1scnt = 9;
uint16_t L2scnt = 9;

double Load_Cell1_com_value, Load_Cell2_com_value;

void main(void)
{
	
	//クロック設定
	R_PG_Clock_WaitSet(0.01);
	
	//ポート設定
	initial_port();
	initial_SCI();
	initial_S12AD();
	initial_DA();
	initial_CMT();
	
	//GPT初期設定
	R_PG_Timer_Set_GPT_U0();
	R_PG_Timer_Set_GPT_U0_C0();
	
	PWMvalue = 0;
	
	R_PG_Timer_SetGTCCR_A_GPT_U0_C0(PWMvalue);
	
	//タイマカウント開始
	R_PG_Timer_StartCount_CMT_U0_C0();
	R_PG_Timer_StartCount_CMT_U0_C1();
	R_PG_Timer_StartCount_GPT_U0_C0();
	
	R_PG_SCI_StartReceiving_C1(Redata,4);
	
	Load_Cell_data_request[0] = '@';
	Load_Cell_data_request[1] = '0';
	Load_Cell_data_request[2] = '1';
	Load_Cell_data_request[3] = 'R';
	Load_Cell_data_request[4] = 0x0d;
	
	L1_485_receive_flag = false;
	
	while(1)
	{
		
	}

}



//RS232C送信割り込み
void Sci1TrFunc(void)
{
	
	
	for(i=0; i<=21; i++){
		dataS[i] = Senddata[i];
		Senddata[i] = 0x00;
	}

}


//RS232C受信割り込み
void Sci1ReFunc(void)
{
	
	R_PG_SCI_StartReceiving_C1(Redata,4);
	
	//デリミタ基準に受信文字列を整列
	for(i=0; i<=3; i++){
		if(Redata[i]==0x0d){
		//0x0d = "CR" CRの位置を検索
			delim=i;
		}
	}
	
	cmd1[0] = Redata[delim-3];
	cmd1[1] = Redata[delim-2];
	cmd1[2] = Redata[delim-1];
	
	
	//Cコマンド・・・サーボ/インバータの回転数指令
	if(!strncmp(cmd1,"C",1)){
		DAset = 0x0000;
		DAset = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		R_PG_DAC_ControlOutput_C0(DAset);//DAC出力設定変更
		returncmd(0);//コマンド受信通知 0=OK>
	}
	
	//給紙用コマンド
	/*
	
	//Bコマンド：シュレッダーモータオートリバース時の回転数変更
	else if(!strncmp(cmd1,"B",1)){
		AreverseDA = ((Redata[delim-2] - 0x30) << 5) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}

	
	
	//Dコマンド：インターバル運転の運転時間変更
	else if(!strncmp(cmd1,"D",1)){
		Runtime2 = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Eコマンド：インターバル運転の停止時間変更
	else if(!strncmp(cmd1,"E",1)){
		Stoptime2 = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Fコマンド：オートリバース時の逆回転時間設定
	else if(!strncmp(cmd1,"F",1)){
		Areversetime = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Gコマンド：オートリバース動作時のADリミットを設定
	else if(!strncmp(cmd1,"G",1)){
		Areverselimit = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	*/
	
	//Hコマンド：サーボモータ自動停止の時間変更
	else if(!strncmp(cmd1,"H",1)){
		SVstopcnt = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Jコマンド：DCB自動停止の時間変更
	else if(!strncmp(cmd1,"J",1)){
		DCBstopcnt = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Mコマンド：DCB2自動停止の時間変更
	else if(!strncmp(cmd1,"M",1)){
		DCB2stopcnt = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Nコマンド：ロードセル1の閾値変更
	else if(!strncmp(cmd1,"N",1)){
		L1setvalue = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Pコマンド：DCB1回転数変更
	else if(!strncmp(cmd1,"P",1)){
		DAsetp = 0x0000;
		//Pコマンド以降のデータをDAsetへ渡す
		DAsetp = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		R_PG_DAC_ControlOutput_C1(DAsetp);//DAC出力設定変更
		returncmd(0);//コマンド受信通知 0=OK>		
	}
	
	//Qコマンド：ロードセル2の閾値変更
	else if(!strncmp(cmd1,"Q",1)){
		L2setvalue = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Tコマンド：CMTトリガタイミング変更
	else if(!strncmp(cmd1,"T",1)){
		CMTset = ( ( ( Redata[delim-2] - 0x30 ) * 10 ) + ( Redata[delim-1] - 0x30 )  ) * 937 ;
		
		if(CMTset>=61000){
			returncmd(1);
			//設定可能範囲外 エラー通知
		}
		else{
			R_PG_Timer_SetConstantRegister_CMT_U0_C0(CMTset);
			returncmd(0);
			//CMTレジスタ設定変更
		}
	}
	
	//給紙用コマンド
	/*
	//Uコマンド：インターバル運転の運転時間変更
	else if(!strncmp(cmd1,"U",1)){
		Runtime = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Vコマンド：インターバル運転の停止時間変更
	else if(!strncmp(cmd1,"V",1)){
		Stoptime = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}

	//Xコマンド：パルス数取得周期の変更
	else if(!strncmp(cmd1,"X",1)){
		
		PCTset = ( ( ( Redata[delim-2] - 0x30 ) * 10 ) + ( Redata[delim-1] - 0x30 )  ) * 937 ;
		
		if(PCTset>=61000){
			returncmd(1);
			//設定可能範囲外 エラー通知
		}
		else{
			R_PG_Timer_SetTGR_C_MTU_U0_C4(PCTset);
			returncmd(0);
			//CMTレジスタ設定変更
		}
	}
	*/
	
	//Yコマンド：PWM出力を変更
	else if(!strncmp(cmd1,"Y",1)){
		
		PWMvalue = 0x0000;
		
		PWMvalue = ( ( Redata[delim-2] - 0x30 ) << 6 ) | (Redata[delim-1] - 0x30 ) ;
		//12bitデータをPWMvalueに格納
		//0～100%を12bitデータとして受信する。
		
		calPWM = 4799900/4095;
		
		calPWM = calPWM * PWMvalue;
		
		//calPWM = calPWM * ( 47999 / 4095 );
		//受信データ(比率)とカウント周期を掛け、Dutyを設定
		
		PWMvalue = calPWM/100;
		
		R_PG_Timer_SetGTCCR_A_GPT_U0_C0(PWMvalue);
		//Duty値をGPTレジスタに書き込み
		
		returncmd(0);
	}
	
	//aコマンド：ロードセル1の変動閾値変更
	else if(!strncmp(cmd1,"a",1)){
		L1varval = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//bコマンド：ロードセル2の変動閾値変更
	else if(!strncmp(cmd1,"b",1)){
		L2varval = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}

	//cコマンド：ロードセル1の変動監視時間変更
	else if(!strncmp(cmd1,"c",1)){
		L1vartime = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30) * 1;
		returncmd(0);
	}

	//dコマンド：ロードセル2の変動監視時間変更
	else if(!strncmp(cmd1,"d",1)){
		L2vartime = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30) * 1;
		returncmd(0);
	}
	
	//eコマンド：バケット1 ON時間設定
	else if(!strncmp(cmd1,"e",1)){
		Bckt1ONtime = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//fコマンド：バケット1 OFF時間設定
	else if(!strncmp(cmd1,"f",1)){
		Bckt1OFFtime = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//gコマンド：バケット2 ON時間設定
	else if(!strncmp(cmd1,"g",1)){
		Bckt2ONtime = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//hコマンド：バケット2 OFF時間設定
	else if(!strncmp(cmd1,"h",1)){
		Bckt2OFFtime = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//iコマンド：DCB2 遅延時間設定
	else if(!strncmp(cmd1,"i",1)){
		DCB2Delaytime = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}

	//jコマンド：バケット1後遅延時間設定
	else if(!strncmp(cmd1,"j",1)){
		L1scnt = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//kコマンド：バケット2後遅延時間設定
	else if(!strncmp(cmd1,"k",1)){
		L2scnt = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//lコマンド：バケット後、AD変換中止時間設定
	else if(!strncmp(cmd1,"l",1)){
		L1adstoptime = (Redata[delim-2] - 0x30) * 10 + (Redata[delim-1] - 0x30);
		L2adstoptime = L1adstoptime;
		returncmd(0);
	}
	
	//mコマンド・・・L1の閾値2変更
	else if(!strncmp(cmd1,"m",1)){
		L1setvalue1 = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//nコマンド・・・L2の閾値2変更
	else if(!strncmp(cmd1,"n",1)){
		L2setvalue1 = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//oコマンド・・・DCB1 回転数2設定
	else if(!strncmp(cmd1,"o",1)){
		DAset2 = 0x0000;
		DAset2 = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		returncmd(0);
	}
	
	//pコマンド・・・DCB2 回転数2設定
	else if(!strncmp(cmd1,"p",1)){
		
		PWMvalue2 = 0x0000;
		
		PWMvalue2 = ( ( Redata[delim-2] - 0x30 ) << 6 ) | (Redata[delim-1] - 0x30 ) ;
		
		calPWM = 4799900/4095;
		
		calPWM = calPWM * PWMvalue2;
		
		PWMvalue2 = calPWM/100;
		
		returncmd(0);
	}
	
	//STAコマンド：サーボモータ回転開始
	else if(!strncmp(cmd1,"STA",3)){
		SVmotorRunflg = true;
		SVruncnt = 1;
		
		returncmd(0);
	}
	
	//STPコマンド：サーボモータ停止
	else if(!strncmp(cmd1,"STP",3)){
		R_PG_IO_PORT_Write_PD2(0x00);
		R_PG_IO_PORT_Write_P04(0x00);
		SVmotorRunflg = false;
		
		returncmd(0);
	}
	
	//STSコマンド：サーボモータCW方向回転
	else if(!strncmp(cmd1,"STS",3)){
		ShrCW = 0x01;
		ShrCCW = 0x00;
		returncmd(0);
	}
	
	//STRコマンド：サーボモータCCW方向回転
	else if(!strncmp(cmd1,"STR",3)){
		ShrCW = 0x00;
		ShrCCW = 0x01;
		returncmd(0);
	}
	
	//給紙用コマンド
	/*
	//STBコマンド：オートリバース機能を有効化
	else if(!strncmp(cmd1,"STB",3)){
		autoreverseflg = true;
		returncmd(0);
	}
	
	//STCコマンド：オートリバース機能を無効化
	else if(!strncmp(cmd1,"STC",3)){
		autoreverseflg = false;
		returncmd(0);
	}
	*/
	
	//STTコマンド：サーボモータ自動停止設定
	else if(!strncmp(cmd1,"STT",3)){
		SVmotorAutoStopflg = true;
		returncmd(0);
	}
	
	//STUコマンド：サーボモータ自動停止解除
	else if(!strncmp(cmd1,"STU",3)){
		SVmotorAutoStopflg = false;
		returncmd(0);
	}
	
	//SPAコマンド：DCB1運転開始
	else if(!strncmp(cmd1,"SPA",3)){
		DCBstartflg = true;
		DCBrunflg = true;
		DCBloadstopflg = false;
		DCBruncnt16 = 1;
		returncmd(0);
	}
	
	//SPPコマンド：DCB1停止
	else if(!strncmp(cmd1,"SPP",3)){
		R_PG_IO_PORT_Write_PF3(0x01);
		//R_PG_IO_PORT_Write_PA6(0x01);
		DCBstartflg = false;
		DCBrunflg = false;
		returncmd(0);
	}
	
	//SPSコマンド：DCB1CW回転方向設定
	else if(!strncmp(cmd1,"SPS",3)){
		R_PG_IO_PORT_Write_PA2(0x00);
		returncmd(0);
	}
	
	//SPRコマンド：DCB1CCW回転方向設定
	else if(!strncmp(cmd1,"SPR",3)){
		R_PG_IO_PORT_Write_PA2(0x01);
		returncmd(0);
	}

	//給紙用コマンド
	/*
	//SPIコマンド：DCBモータインターバル運転指令
	else if(!strncmp(cmd1,"SPI",3)){
		DCBintflg = true;
		returncmd(0);
	}
	
	//SPJコマンド：DCBモータインターバル運転停止指令
	else if (!strncmp(cmd1,"SPJ",3)){
		DCBintflg = false;
		returncmd(0);
	}
	*/
	
	//SPTコマンド：DCB1 自動停止設定
	else if(!strncmp(cmd1,"SPT",3)){
		DCBAutoStopflg = true;
		returncmd(0);
	}
	
	//SPUコマンド：DCB1 自動停止解除
	else if(!strncmp(cmd1,"SPU",3)){
		DCBAutoStopflg = false;
		returncmd(0);
	}
	
	//SPDコマンド：DCB1 軽量停止設定
	else if(!strncmp(cmd1,"SPD",3)){
		DCBADcflg = true;
		returncmd(0);
	}
	
	//SPEコマンド：DCB1 軽量停止解除
	else if(!strncmp(cmd1,"SPE",3)){
		DCBADcflg = false;
		returncmd(0);
	}
	
	//SPQコマンド：DCB1/2 シーケンス動作
	else if(!strncmp(cmd1,"SPQ",3)){
		DCBstartflg = true;
		DCBrunflg = true;
		DCBseqflg = true;
		DCBloadstopflg = false;
		DCB2startflg = true;
		DCB2runflg = true;
		DCB2loadstopflg = false;
		DCB2Delayflg = true;
		DCBruncnt16 = 1;
		DCB2runcnt16 = 1;
		Bckt1startflg = false;
		Bckt1runflg = false;
		Bckt2startflg = false;
		Bckt2runflg = false;
		returncmd(0);
	}
	//SPZコマンド：DCB1/2 シーケンス動作解除
	//バケット動作も終了
	else if(!strncmp(cmd1,"SPZ",3)){
		DCBstartflg = false;
		DCBrunflg = false;
		DCBseqflg = false;
		DCB2startflg = false;
		DCB2runflg = false;
		DCB2Delayflg = false;
		Bckt1startflg = false;
		Bckt2startflg = false;
		returncmd(0);
	}
		
	
	//S2Aコマンド：DCB2モータ回転開始
	else if(!strncmp(cmd1,"S2A",3)){
		DCB2startflg = true;
		DCB2runflg = true;
		DCB2loadstopflg = false;
		DCB2runcnt16 = 1;
		returncmd(0);
	}
	
	//S2Pコマンド：DCB2モータ回転停止
	else if(!strncmp(cmd1,"S2P",3)){
		R_PG_IO_PORT_Write_PF2(0x01);
		//R_PG_IO_PORT_Write_PB4(0x01);
		DCB2startflg = false;
		DCB2runflg = false;
		returncmd(0);
	}
	
	//S2Sコマンド：DCB2モータCW方向回転
	else if(!strncmp(cmd1,"S2S",3)){
		R_PG_IO_PORT_Write_P34(0x00);
		returncmd(0);
	}
	
	//S2Rコマンド：DCB2モータCCW方向回転
	else if(!strncmp(cmd1,"S2R",3)){
		R_PG_IO_PORT_Write_P34(0x01);
		returncmd(0);
	}

	//給紙用コマンド
	/*
	//S2Iコマンド：DCB2インターバル運転指令
	else if(!strncmp(cmd1,"S2I",3)){
		DCB2intflg = true;
		returncmd(0);
	}
	
	//S2Jコマンド：DCB2インターバル運転停止指令
	else if(!strncmp(cmd1,"S2J",3)){
		DCB2intflg = false;
		returncmd(0);
	}
	*/
	
	//S2Tコマンド：DCB2 自動停止設定
	else if(!strncmp(cmd1,"S2T",3)){
		DCB2AutoStopflg = true;
		returncmd(0);
	}
	
	//S2Uコマンド：DCB2 自動停止解除
	else if(!strncmp(cmd1,"S2U",3)){
		DCB2AutoStopflg = false;
		returncmd(0);
	}
	
	//S2Dコマンド：DCB2 軽量停止設定
	else if(!strncmp(cmd1,"S2D",3)){
		DCB2ADcflg = true;
		returncmd(0);
	}
	
	//S2Eコマンド：DCB2 軽量停止解除
	else if(!strncmp(cmd1,"S2E",3)){
		DCB2ADcflg = false;
		returncmd(0);
	}
	
	//ロードセル1 DZ信号送信
	else if(!strncmp(cmd1,"L1D",3)){
		L1dzflg = true;
		L1adstopflg = true;
		returncmd(0);
	}
	
	//ロードセル2 DZ信号送信
	else if(!strncmp(cmd1,"L2D",3)){
		L2dzflg = true;
		L2adstopflg = true;
		returncmd(0);
	}
	
	//ロードセル1 HOLD信号送信
	else if(!strncmp(cmd1,"L1H",3)){
		R_PG_IO_PORT_Write_PA4(0x00);
		returncmd(0);
	}
	
	//ロードセル1 HOLD信号解除
	else if(!strncmp(cmd1,"L1R",3)){
		R_PG_IO_PORT_Write_PA4(0x01);
		returncmd(0);
	}
	
	//ロードセル2 HOLD信号送信
	else if(!strncmp(cmd1,"L2H",3)){
		R_PG_IO_PORT_Write_P03(0x00);
		returncmd(0);
	}
	
	//ロードセル2 HOLD信号解除
	else if(!strncmp(cmd1,"L2R",3)){
		R_PG_IO_PORT_Write_P03(0x01);
		returncmd(0);
	}

	//バケット1 ON信号
	else if(!strncmp(cmd1,"K1H",3)){
		R_PG_IO_PORT_Write_PF4(0x01);
		returncmd(0);
	}
	
	//バケット1 OFF信号
	else if(!strncmp(cmd1,"K1R",3)){
		R_PG_IO_PORT_Write_PF4(0x00);
		returncmd(0);
	}
	
	//バケット1 動作開始
	else if(!strncmp(cmd1,"K1A",3)){
		Bckt1startflg = true;
		//カウンタ初期化
		Bckt1runcnt = 1;
		returncmd(0);
	}
	
	//バケット1 停止指令
	//現在の状態で停止
	else if(!strncmp(cmd1,"K1P",3)){
		Bckt1startflg = false;
		returncmd(0);
	}
	
	//バケット2 ON信号
	else if(!strncmp(cmd1,"K2H",3)){
		R_PG_IO_PORT_Write_P25(0x01);
		returncmd(0);
	}
	
	//バケット2 OFF信号
	else if(!strncmp(cmd1,"K2R",3)){
		R_PG_IO_PORT_Write_P25(0x00);
		returncmd(0);
	}
	
	//バケット2 動作開始
	else if(!strncmp(cmd1,"K2A",3)){
		Bckt2startflg = true;
		Bckt2runcnt = 1;
		returncmd(0);
	}
	
	//バケット2 停止指令
	else if(!strncmp(cmd1,"K2P",3)){
		Bckt2startflg = false;
		returncmd(0);
	}
	
	//INFコマンド：状態通知
	else if(!strncmp(cmd1,"INF",3)){
		
		//運転状態を通知
		//サーボモータ回転状態を通知
		Senddata[0] = valueascii(PORTD.PODR.BIT.B2);//CW出力状態(0:Lo)
		Senddata[1] = valueascii(PORT0.PODR.BIT.B4);//CCW出力状態(1:Hi)
		
		//回転数を通知 3byte
		Senddata[2] = valueascii((DA.DADR0 >> 8) & 0x00F);
		Senddata[3] = valueascii((DA.DADR0 >> 4) & 0x00F);
		Senddata[4] = valueascii(DA.DADR0 & 0x00F); 
		
		//DCB回転状態を通知
		Senddata[5] = valueascii(PORTA.PODR.BIT.B2);//回転方向 CW/CCW
		Senddata[6] = valueascii(PORTF.PODR.BIT.B3);//START/STOP
		
		//回転数を通知 3byte
		Senddata[7] = valueascii((DA.DADR1 >> 8) & 0x00F);
		Senddata[8] = valueascii((DA.DADR1 >> 4) & 0x00F);
		Senddata[9] = valueascii(DA.DADR1 & 0x00F);
		
		//CMT制御周期を通知 4byte
		Senddata[10] = valueascii((CMT0.CMCOR >> 12) & 0x000F);
		Senddata[11] = valueascii((CMT0.CMCOR >> 8) & 0x000F);
		Senddata[12] = valueascii((CMT0.CMCOR >> 4) & 0x000F);
		Senddata[13] = valueascii(CMT0.CMCOR & 0x000F);	
		
		//DCB2回転状態を通知
		Senddata[14] = valueascii(PORT3.PODR.BIT.B4);//回転方向 CW/CCW
		Senddata[15] = valueascii(PORTF.PODR.BIT.B2);//START/STOP
		
		//DCB2回転数通知
		Senddata[16] = valueascii((GPT0.GTCCRA >> 12) & 0x000F);
		Senddata[17] = valueascii((GPT0.GTCCRA >> 8)  & 0x000F);
		Senddata[18] = valueascii((GPT0.GTCCRA >> 4)  & 0x000F);
		Senddata[19] = valueascii( GPT0.GTCCRA & 0x000F);
		
		Senddata[20] = 0x0d;
		//デリミタ CR
		
		R_PG_SCI_StartSending_C1(Senddata,21);
	}
	
	//IN2コマンド：状態通知
	else if(!strncmp(cmd1,"IN2",3)){
		
		//オートリバース有無
		Senddata[0] = valueascii(autoreverseflg);
		
		//オートリバース回転数
		Senddata[1] = valueascii((AreverseDA >> 8) & 0x000F);
		Senddata[2] = valueascii((AreverseDA >> 4) & 0x000F);
		Senddata[3] = valueascii( AreverseDA & 0x000F);
		
		//オートリバース条件
		Senddata[4] = valueascii((Areverselimit >> 8) & 0x000F);
		Senddata[5] = valueascii((Areverselimit >> 4) & 0x000F);
		Senddata[6] = valueascii( Areverselimit & 0x000F);
		
		//オートリバース時間
		Senddata[7] = valueascii((Areversetime >> 4) & 0x0F);
		Senddata[8] = valueascii( Areversetime & 0x0F);
		
		//DCBインターバル動作有無
		Senddata[9] = valueascii(DCBintflg);
	
		//DCB間欠運転 運転時間
		Senddata[10] = valueascii((Runtime >> 4) & 0x0F);
		Senddata[11] = valueascii( Runtime & 0x0F);
		
		//DCB間欠運転 停止時間
		Senddata[12] = valueascii((Stoptime >> 4) & 0x0F);
		Senddata[13] = valueascii( Stoptime & 0x0F);
		
		//DCB2インターバル動作有無
		Senddata[14] = valueascii(DCB2intflg);
		
		//DCB2間欠運転 運転時間
		Senddata[15] = valueascii((Runtime2 >> 4) & 0x0F);
		Senddata[16] = valueascii( Runtime2 & 0x0F);
		
		//DCB2間欠運転 停止時間
		Senddata[17] = valueascii((Stoptime2 >> 4) & 0x0F);
		Senddata[18] = valueascii( Stoptime2 & 0x0F);
		
		Senddata[19] = 0x0d;
		//デリミタ CR
		
		R_PG_SCI_StartSending_C1(Senddata,20);		
	}
	
	else if(!strncmp(cmd1,"IN3",3)){
		//サーボモータ自動停止時間
		Senddata[0] = valueascii((SVstopcnt >> 8) & 0x00F);
		Senddata[1] = valueascii((SVstopcnt >> 4) & 0x00F);
		Senddata[2] = valueascii( SVstopcnt & 0x00F);
		
		//サーボモータ自動停止動作有無
		Senddata[3] = valueascii(SVmotorAutoStopflg);
		
		//DCB1 自動停止時間
		Senddata[4] = valueascii((DCBstopcnt >> 8) & 0x00F);
		Senddata[5] = valueascii((DCBstopcnt >> 4) & 0x00F);
		Senddata[6] = valueascii( DCBstopcnt & 0x00F);
		
		//DCB2 自動停止時間
		Senddata[7] = valueascii((DCB2stopcnt >> 8) & 0x00F);
		Senddata[8] = valueascii((DCB2stopcnt >> 4) & 0x00F);
		Senddata[9] = valueascii( DCB2stopcnt & 0x00F);
		
		//DCB 自動停止設定有無
		Senddata[10] = (DCBstartflg << 6) + (DCBAutoStopflg << 5) 
			+ (DCBADcflg << 4) + (DCB2startflg << 3) + (DCB2AutoStopflg << 2)
			+ (DCB2ADcflg << 1);
		
		//ロードセル1 閾値
		Senddata[11] = valueascii((L1setvalue >> 8) & 0x00F);
		Senddata[12] = valueascii((L1setvalue >> 4) & 0x00F);
		Senddata[13] = valueascii( L1setvalue & 0x00F);
		
		//ロードセル2 閾値
		Senddata[14] = valueascii((L2setvalue >> 8) & 0x00F);
		Senddata[15] = valueascii((L2setvalue >> 4) & 0x00F);
		Senddata[16] = valueascii( L2setvalue & 0x00F);
		
		//ロードセル1 変動閾値
		Senddata[17] = valueascii((L1varval >> 8) & 0x00F);
		Senddata[18] = valueascii((L1varval >> 4) & 0x00F);
		Senddata[19] = valueascii( L1varval & 0x00F);
		
		Senddata[20] = 0x0d;
		
		R_PG_SCI_StartSending_C1(Senddata,21);
		
	}
	
	else if(!strncmp(cmd1,"IN4",3)){
		//ロードセル2 変動閾値
		Senddata[0] = valueascii((L2varval >> 8) & 0x00F);
		Senddata[1] = valueascii((L2varval >> 4) & 0x00F);
		Senddata[2] = valueascii( L2varval & 0x00F);
		
		//ロードセル1 監視時間
		Senddata[3] = valueascii((L1vartime >> 8) & 0x00F);
		Senddata[4] = valueascii((L1vartime >> 4) & 0x00F);
		Senddata[5] = valueascii( L1vartime & 0x00F);
		
		//ロードセル2 監視時間
		Senddata[6] = valueascii((L2vartime >> 8) & 0x00F);
		Senddata[7] = valueascii((L2vartime >> 4) & 0x00F);
		Senddata[8] = valueascii( L2vartime & 0x00F);
		
		//バケット1 ON時間
		Senddata[9] = valueascii(Bckt1ONtime / 10);
		Senddata[10] = valueascii(Bckt1ONtime % 10);
		
		//バケット1 OFF時間
		Senddata[11] = valueascii(Bckt1OFFtime / 10);
		Senddata[12] = valueascii(Bckt1OFFtime % 10);
		
		//バケット2 ON時間
		Senddata[13] = valueascii(Bckt2ONtime / 10);
		Senddata[14] = valueascii(Bckt2OFFtime % 10);
		
		//バケット2 OFF時間
		Senddata[15] = valueascii(Bckt2OFFtime / 10);
		Senddata[16] = valueascii(Bckt2OFFtime % 10);
		
		//バケット設定
		Senddata[17] = (Bckt1startflg << 2) + (Bckt2startflg << 1);
		
		//バケットの状態
		Senddata[18] = valueascii(PORTF.PODR.BIT.B4);
		Senddata[19] = valueascii(PORT2.PODR.BIT.B5);
		
		Senddata[20] = 0x0d;
		
		R_PG_SCI_StartSending_C1(Senddata,21);
	}
		
	//IN5コマンド：状態通知
	else if(!strncmp(cmd1,"IN5",3)){
		//サーボモータ回転状態を通知
		Senddata[0] = valueascii(PORTD.PODR.BIT.B2);//CW出力状態(0:Lo)
		Senddata[1] = valueascii(PORT0.PODR.BIT.B4);//CCW出力状態(1:Hi)
		
		//DCB回転状態を通知
		Senddata[2] = valueascii(PORTA.PODR.BIT.B2);//回転方向 CW/CCW
		Senddata[3] = valueascii(PORTF.PODR.BIT.B3);//START/STOP
		
		//DCB2回転状態を通知
		Senddata[4] = valueascii(PORT3.PODR.BIT.B4);//回転方向 CW/CCW
		Senddata[5] = valueascii(PORTF.PODR.BIT.B2);//START/STOP
		
		//バケットの状態
		Senddata[6] = valueascii(PORTF.PODR.BIT.B4);
		Senddata[7] = valueascii(PORT2.PODR.BIT.B5);
		
		Senddata[8] = valueascii((ADtval[0] >> 8) & 0x00F);
		Senddata[9] = valueascii((ADtval[0] >> 4) & 0x00F);
		Senddata[10] = valueascii(ADtval[0] & 0x00F); 
		
		Senddata[11] = valueascii((ADtval[1] >> 8) & 0x00F);
		Senddata[12] = valueascii((ADtval[1] >> 4) & 0x00F);
		Senddata[13] = valueascii( ADtval[1] & 0x00F);
		
		Senddata[14] = valueascii((L1fixval >> 8) & 0x00F);
		Senddata[15] = valueascii((L1fixval >> 4) & 0x00F);
		Senddata[16] = valueascii( L1fixval & 0x00F);
		
		Senddata[17] = valueascii((L2fixval >> 8) & 0x00F);
		Senddata[18] = valueascii((L2fixval >> 4) & 0x00F);
		Senddata[19] = valueascii( L2fixval & 0x00F);
		
		Senddata[20] = 0x0d;
		//デリミタCRを付与
		
		R_PG_SCI_StartSending_C1(Senddata,21);

	}
		
		
		
	//ADSコマンド：ADデータ送信要求
	else if(!strncmp(cmd1,"ADS",3)){
		
		Senddata[0] = valueascii((ADtval[0] >> 8) & 0x00F);
		Senddata[1] = valueascii((ADtval[0] >> 4) & 0x00F);
		Senddata[2] = valueascii( ADtval[0] & 0x00F); 
		
		Senddata[3] = valueascii((ADtval[1] >> 8) & 0x00F);
		Senddata[4] = valueascii((ADtval[1] >> 4) & 0x00F);
		Senddata[5] = valueascii( ADtval[1] & 0x00F);
		
		Senddata[6] = valueascii((L1fixval >> 8) & 0x00F);
		Senddata[7] = valueascii((L1fixval >> 4) & 0x00F);
		Senddata[8] = valueascii( L1fixval & 0x00F);
		
		Senddata[9] = valueascii((L2fixval >> 8) & 0x00F);
		Senddata[10] = valueascii((L2fixval >> 4) & 0x00F);
		Senddata[11] = valueascii( L2fixval & 0x00F);
		
		Senddata[12] = 0x0d;
		//デリミタCRを付与
		
		R_PG_SCI_StartSending_C1(Senddata,13);

	}
	//AD4�R�}���h�FRS485�Ŏ�M����AD�l���M�v��
	else if(!strncmp(cmd1,"AD4",3)){
		
		for(i=0;i<7;i++){
			Senddata[i] = Load_Cell_return_data[i+7];
		}
		Senddata[7] = 0x0d;
		//�f���~�^CR��t�^
		
		R_PG_SCI_StartSending_C1(Senddata,8);

	}	
	
	//RPSコマンド：パルスカウント数送信要求
	/*
	else if(!strncmp(cmd1,"RPS",3)){
		
		if(plssend == 0){
			returncmd(1);
		}
		else if(plsrcnt == 0){
			returncmd(1);
		}
		else{
			Senddata[0] = valueascii((plssend >> 8) & 0x00F);
			Senddata[1] = valueascii((plssend >> 4) & 0x00F);
			Senddata[2] = valueascii( plssend & 0x00F); 
			//Senddata[0] = ((plssend >> 8) & 0x000F) + 0x40;
			//Senddata[1] = ((plssend >> 4) & 0x000F) + 0x40;
			//Senddata[2] = ( plssend & 0x000F) + 0x40;
			//パルスカウント値をアルファベットに変換して送信データを作成
			
			Senddata[3] = valueascii((plsrcnt >> 4) & 0x0F);
			Senddata[4] = valueascii( plsrcnt & 0x0F);
			//Senddata[3] = plsrcnt + 0x40;
			//積算数
			
			Senddata[5] = 0x0d;
			//デリミタCRを付与
			
			R_PG_SCI_StartSending_C1(Senddata,6);
		}
		
	}
	*/
	

	//未対応コマンドの場合エラー
	else{
		returncmd(1);
	}
	
	//デリミタ格納変数を初期化
	delim=0x00;
		
}


//CMT0割り込み
void Cmt0IntFunc(void)
{

	//ロードセル通信
	if(!L1_485_receive_flag){
		L1_485_receive_flag = true;
		/*��M�o�b�t�@�̒l��������
		for(i=0;i<20;i++){
			Load_Cell_return_data[i] = 0;
		}*/
		PORTB.PODR.BIT.B0 = 1; 
		R_PG_SCI_StartSending_C0(Load_Cell_data_request,5);
	}
	//給紙用制御
	/*
	if(DCBstartflg && DCBintflg){
	//DCB運転命令中かつ間欠運転中の時にカウント
		if(DCBrunflg){
		//DCB実運転中
			if(DCBruncnt < Runtime){
			//Runtimeまでカウント
				DCBruncnt = DCBruncnt + 1;
			}else{
			//Runtimeカウント完了後
				DCBruncnt = 0;
				DCBrunflg = false;
				R_PG_IO_PORT_Write_PF3(0x01);
				//DCB運転停止
			}
		}else{
		//DCB停止中
			if(DCBruncnt < Stoptime){
			//Stoptimeまでカウント
				DCBruncnt = DCBruncnt + 1;
			}else{
			//Stoptimeカウント完了後
				DCBruncnt = 0;
				DCBrunflg = true;
				R_PG_IO_PORT_Write_PF3(0x00);
				//DCB運転再開
			}
		}
	}

					
	if(DCB2startflg && DCB2intflg){
	//DCB2運転命令中かつ間欠運転中
		if(DCB2runflg){
		//DCB2実運転中
			if(DCB2runcnt < Runtime){
			//Runtimeまでカウント
				DCB2runcnt = DCBruncnt + 1;
			}else{
			//Runtimeカウント完了後
				DCB2runcnt = 0;
				DCB2runflg = false;
				R_PG_IO_PORT_Write_PF2(0x01);
				//DCB2運転停止
			}
		}else{
		//DCB停止中
			if(DCB2runcnt < Stoptime){
			//Stoptimeまでカウント
				DCB2runcnt = DCB2runcnt + 1;
			}else{
			//Stoptimeカウント完了後
				DCB2runcnt = 0;
				DCB2runflg = true;
				R_PG_IO_PORT_Write_PF2(0x00);
				//DCB運転再開
			}
		}
	}

	if(ARwaitflg){
	//オートリバース動作まで待機
		if(ARtimecnt < ARwaittime){
		//規定時間までカウントを継続
			ARtimecnt = ARtimecnt + 1;
		}else{
		//規定時間経過後
			
			R_PG_DAC_ControlOutput_C0(AreverseDA);
			//逆回転時の回転数をインプット
			R_PG_IO_PORT_Write_PD2(0x01);
			//CW回転開始
			ARtimecnt = 0;
			//カウントをクリア
			
			ARwaitflg = false;
			ARstartflg = true;
		}
	}
	
	
	
	if(ARstartflg){
		if(ARtimecnt < Areversetime){
		//Areversetimeまでカウント
			ARtimecnt = ARtimecnt + 1;
		}else{
		//Areversetimeまでカウント完了後
			ARtimecnt = 0;
			//カウントリセット
			R_PG_IO_PORT_Write_PD2(0x00);
			//シュッレッダー動作停止
			R_PG_DAC_ControlOutput_C0(DAset);
			//シュレッダー回転数を戻す
			ARstartflg = false;
		}
	}
	*/
	
	//L1dzflg=trueでロードセル1 DZ信号をLoにする。
	//1周期(100ms)後に元に戻す。
	if(L1dzflg){
		R_PG_IO_PORT_Write_P26(0x01);
		L1dzflg = false;
		L1adstopcnt = L1adstoptime;
	}else{
		R_PG_IO_PORT_Write_P26(0x00);
	}
	
	if(L2dzflg){
		R_PG_IO_PORT_Write_P02(0x01);
		L2dzflg = false;
		L2adstopcnt = L2adstoptime;
	}else{
		R_PG_IO_PORT_Write_P02(0x00);
	}
	
	if(L1adstopcnt > 0){
		L1adstopcnt = L1adstopcnt - 1;
	}else{
		L1adstopflg = false;
	}
	
	if(L2adstopcnt > 0){
		L2adstopcnt = L2adstopcnt - 1;
	}else{
		L2adstopflg = false;
	}
	
	//サーボモータ自動停止フラグ
	//指定カウント後に動作を停止
	if(SVmotorRunflg){
		if(SVruncnt > SVstopcnt){
			R_PG_IO_PORT_Write_PD2(0x00);
			R_PG_IO_PORT_Write_P04(0x00);
			SVruncnt = 1;
			SVmotorRunflg = false;
		}else{
			R_PG_IO_PORT_Write_PD2(ShrCW);
			R_PG_IO_PORT_Write_P04(ShrCCW);
			if(SVmotorAutoStopflg){
				SVruncnt = SVruncnt + 1;
			}
		}
	}
	
	//DCB自動停止フラグ
	//指定カウント後に動作を停止
	if(DCBrunflg){
		if(DCBruncnt16 > DCBstopcnt){
			R_PG_IO_PORT_Write_PF3(0x01);
			//R_PG_IO_PORT_Write_PA6(0x01);
			DCBruncnt16 = 1;
			DCBrunflg = false;
			R_PG_DAC_ControlOutput_C1(DAsetp);//初期回転数にセット
			if(DCBseqflg){
				Bckt1startflg = true;
				Bckt1runflg = false;
				Bckt1runcnt = 100;
			}
		}else{
			if(!DCBloadstopflg){
				R_PG_IO_PORT_Write_PF3(0x00);
				//R_PG_IO_PORT_Write_PA6(0x00);
			}else{
				R_PG_IO_PORT_Write_PF3(0x01);
				//R_PG_IO_PORT_Write_PA6(0x01);
			}
			if(DCBAutoStopflg){
				DCBruncnt16 = DCBruncnt16 + 1;
			}
		}
	}

	
	//DCB2自動停止フラグ
	//指定カウント後に動作を停止
	if(DCB2Delayflg){
		if(DCB2runcnt16 > DCB2Delaytime){
			DCB2Delayflg = false;
			R_PG_IO_PORT_Write_PF2(0x00);
			//R_PG_IO_PORT_Write_PB4(0x00);
			DCB2runcnt16 = 2;
		}else{
			DCB2runcnt16 = DCB2runcnt16 + 1;
		}
	}else{
		if(DCB2runflg){
			if(DCB2runcnt16 > DCB2stopcnt){
				R_PG_IO_PORT_Write_PF2(0x01);
				//R_PG_IO_PORT_Write_PB4(0x01);
				DCB2runcnt16 = 1;
				DCB2runflg = false;
				if(DCBseqflg){
					Bckt2startflg = true;
					Bckt2runflg = false;
					Bckt2runcnt = 100;
				}
			}else{
				if(!DCB2loadstopflg){
					R_PG_IO_PORT_Write_PF2(0x00);
					//R_PG_IO_PORT_Write_PB4(0x00);
				}else{
					R_PG_IO_PORT_Write_PF2(0x01);
					//R_PG_IO_PORT_Write_PB4(0x01);
				}
				if(DCB2AutoStopflg){
					DCB2runcnt16 = DCB2runcnt16 + 1;
				}
			}
		}
	}
	
	/*
	//L1waitflg=trueの間カウントする
	if(L1waitflg){
		if(L1varcnt > L1vartime){
			//規定時間後待機完了
			L1waitflg = false;
			L1varcnt = 1;
		}else{
			L1varcnt = L1varcnt + 1;
		}
	}
	
	//L2waitflg=trueの間カウントする
	if(L2waitflg){
		if(L2varcnt > L2vartime){
			L2waitflg = false;
			L2varcnt = 1;
		}else{
			L2varcnt = L2varcnt + 1;
		}
	}
	*/
	
	//バケットOFF後、安定するまで待機
	if(L1stablemonflg){
		if(L1scnt > L1tcnt){
			L1adstopflg = true;
			L1adstopcnt = L1scnt;
			L1tcnt = L1tcnt + 1;
		}else{
			DCBrunflg = true;
			DCBloadstopflg = false;
			R_PG_IO_PORT_Write_PF3(0x00);
			//R_PG_IO_PORT_Write_PA6(0x00);
			DCBruncnt16 = 2;
			L1tcnt = 0;
			L1dzflg = true;
			L1adstopflg = true;
			L1stablemonflg = false;
		}
	}
	if(L2stablemonflg){
		if(L2scnt > L2tcnt){
			L2adstopflg = true;
			L2adstopcnt = L2scnt;
			L2tcnt = L2tcnt + 1;
		}else{
			DCB2runflg = true;
			DCB2loadstopflg = false;
			R_PG_IO_PORT_Write_PF2(0x00);
			//R_PG_IO_PORT_Write_PB4(0x00);
			DCB2runcnt16 = 2;
			L2tcnt = 0;
			L2dzflg = true;
			L2adstopflg = true;
			L2stablemonflg = false;
		}
	}
	
	
	//バケット1 周期運転
	//周期運転開始命令で動作
	if(Bckt1startflg){
		//バケット1がONかOFFかで時間を変更
		if(Bckt1runflg){
			//ONの場合、ONtimeまでカウントする。
			if(Bckt1runcnt >= Bckt1ONtime){
				//カウント完了後停止
				R_PG_IO_PORT_Write_PF4(0x00);
				Bckt1runflg = false;
				//カウンタ初期化
				Bckt1runcnt = 1;
				if(DCBseqflg){
					Bckt1startflg = false;
					L1stablemonflg = true;
				}
			}else{
				Bckt1runcnt = Bckt1runcnt + 1;
			}
		}else{
			//OFFの場合、OFFtimeまでカウントする。
			if(Bckt1runcnt >= Bckt1OFFtime){
				//カウント完了後動作
				R_PG_IO_PORT_Write_PF4(0x01);
				Bckt1runflg = true;
				//カウンタ初期化
				Bckt1runcnt = 1;
			}else{
				Bckt1runcnt = Bckt1runcnt + 1;
			}
		}
	}
	
	
	//バケット2 周期運転
	if(Bckt2startflg){
		if(Bckt2runflg){
			if(Bckt2runcnt >= Bckt2ONtime){
				R_PG_IO_PORT_Write_P25(0x00);
				Bckt2runflg = false;
				Bckt2runcnt = 1;
				R_PG_Timer_SetGTCCR_A_GPT_U0_C0(PWMvalue);
				if(DCBseqflg){
					Bckt2startflg = false;
					L2stablemonflg = true;
				}
			}else{
				Bckt2runcnt = Bckt2runcnt + 1;
			}
		}else{
			if(Bckt2runcnt >= Bckt2OFFtime){
				R_PG_IO_PORT_Write_P25(0x01);
				Bckt2runflg = true;
				Bckt2runcnt = 1;
			}else{
				Bckt2runcnt = Bckt2runcnt + 1;
			}
		}
	}
	
	
	
	
	LED0 = LED0 ^ 0x01;
	
	R_PG_IO_PORT_Write_P71(LED0);
	
}


//SCI0 送信割り込み
void Sci0TrFunc(void)
{
	/* ロードセルから文字列を受信 */
	R_PG_SCI_StartReceiving_C0(Load_Cell_return_data,15);
	/* RS-485 enable = Lo */
	PORTB.PODR.BIT.B0 = 0;
}

//SCI0 受信割り込み
void Sci0ReFunc(void)
{
	static uint8_t dot_count;
	/* 小数点の位置を検索 */
	for(dot_count=7;dot_count<14;dot_count++){
		if(Load_Cell_return_data[dot_count] == '.'){
			break;
		}
	}
	Load_Cell1_com_value = 0;
	for(i=7;i<14;i++){
		if(i < dot_count){
			Load_Cell1_com_value = Load_Cell1_com_value + (Load_Cell_return_data[i] - 0x30) * power_func(10,dot_count - 1 - i);
		}else if(i > dot_count){
			Load_Cell1_com_value = Load_Cell1_com_value + (Load_Cell_return_data[i] - 0x30) * power_func(10,dot_count - i);
		}
	}
	L1_485_receive_flag = false;
	
}

//CMT1 割り込み周期10ms
void Cmt1IntFunc(void)
{
	R_PG_ADC_12_StartConversion_S12AD0();		
}

//AD変換完了割り込み
void S12ad0AIntFunc(void)
{
	R_PG_ADC_12_GetResult_S12AD0(ADval);
	//AD変換の結果をADvalに格納
	//ADval[0]:可変抵抗出力
	//ADval[1]:外部入力0-10V
	//ADval[2]:外部入力4-20mA
	
	//給紙用コマンド
	/*
	if(autoreverseflg){
	//オートリバース動作設定
		if(ADval[2] > Areverselimit){
		//トルク値が上限値をオーバー
			R_PG_IO_PORT_Write_PD2(0x00);
			R_PG_IO_PORT_Write_P04(0x00);
			//シュレッダー停止
			R_PG_IO_PORT_Write_PF2(0x01);
			R_PG_IO_PORT_Write_PF3(0x01);
			//給紙ローラ停止
			
			ARwaitflg = true;
			//オートリバース動作中フラグを設定
		}
	}
	*/
	
	//AD変換のタイミングで自動送信
	/*
	if(ADsendflg){
		
		Senddata[0] = valueascii((ADval[1] >> 8) & 0x00F);
		Senddata[1] = valueascii((ADval[1] >> 4) & 0x00F);
		Senddata[2] = valueascii( ADval[1] & 0x00F); 

		Senddata[0] = ((ADval[1] >> 8) & 0x000F) + 0x40;
		Senddata[1] = ((ADval[1] >> 4) & 0x000F) + 0x40;
		Senddata[2] = ( ADval[1] & 0x000F) + 0x40;
		//AD1(0-10V)をアルファベットに変換して送信データを作成

		Senddata[3] = valueascii((ADval[2] >> 8) & 0x00F);
		Senddata[4] = valueascii((ADval[2] >> 4) & 0x00F);
		Senddata[5] = valueascii( ADval[2] & 0x00F); 

		Senddata[3] = ((ADval[2] >> 8) & 0x000F) + 0x40;
		Senddata[4] = ((ADval[2] >> 4) & 0x000F) + 0x40;
		Senddata[5] = ( ADval[2] & 0x000F) + 0x40;
		//AD2(4-20mA)をアルファベットに変換して送信データを作成	
		
		Senddata[6] = valueascii(k);
		//取り逃した回数を送信
		
		
		Senddata[7] = 0x0d;
		//デリミタCRを付与
		
		R_PG_SCI_StartSending_C1(Senddata,8);
		
		k = 0;
		ADsendflg = false;
		//フラグをリセット
	}
	else{
		k = k + 1;
	}
	*/
	
	/*
	//wait時間終了で変動閾値以内か判定する。
	if(!DCBloadstopflg){
		if(!L1waitflg){
			//前回値との差分を計算
			if(ADval[1] > L1nval){
				L1defval = ADval[1] - L1nval;
			}else{
				L1defval = L1nval - ADval[1];
			}
			//差分が規定値以内か判定
			if(L1defval < L1varval){
				L1fixflg = true;
			}else{
				L1fixflg = false;
			}
			//今回の値を保存
			L1nval = ADval[1];
			//wait時間待機
			L1waitflg = true;
		}
	}
	//DCB計量停止
	//DCB動作中でロードセルの値がFixしていたら判定値と比較する。
	if(DCBADcflg && DCBrunflg && L1fixflg && ADval[1] > L1setvalue){
		//判定値を超えていればDCB動作停止
		R_PG_IO_PORT_Write_PF3(0x01);
		DCBloadstopflg = true;
	}
	
	L1fixflg = false;
	
	//wait時間終了で変動閾値以内か判定する。
	if(!DCB2loadstopflg){
		if(!L2waitflg){
			if(ADval[2] > L2nval){
				L2defval = ADval[2] - L2nval;
			}else{
				L2defval = L2nval - ADval[2];
			}
			if(L2defval < L2varval){
				L2fixflg = true;
			}else{
				L2waitflg = true;
				L2fixflg = false;
			}
			L2nval = ADval[2];
			L2waitflg = true;
		}
	}
	
	//DCB2計量停止
	if(DCB2ADcflg && DCB2runflg && L2fixflg &&  ADval[2] > L2setvalue){
		R_PG_IO_PORT_Write_PF2(0x01);
		DCB2loadstopflg = true;
	}
	
	L2fixflg = false;
	*/

	//バケットクローズ後、ロードセルの読み値が下がったら、
	//DZ実行する。
	/*
	if(L1resflg){
		if(ADval[1] < 5000){
			L1dzflg = true;
			L1adstopflg = true;
			L1resflg = false;
		}
	}
	if(L2resflg){
		if(ADval[2] < 5000){
			L2dzflg = true;
			L2adstopflg = true;
			L2resflg = false;
		}
	}
	*/

	//DZ処理中はAD変換処理中止
	if(!L1adstopflg){
	
		//AD値の5回平均
		if(AD1_counter == 4){
			AD1_counter = 0;
		}else{
			AD1_counter = AD1_counter + 1;
		}
		AD1_buf[AD1_counter] = ADval[1];
		AD1_reg = 0;
		for(i=0;i<5;i++){
			AD1_reg = AD1_reg + AD1_buf[i];
		}
		ADtval[0] = AD1_reg / 5;
		
		//初期値との差分を取得
		if(ADtval[0] > L1nval){
			L1defval = ADtval[0] - L1nval;
		}else{
			L1defval = L1nval - ADtval[0];
		}
		
		//差分が規定値以内か判定
		if(L1defval < L1varval){
			L1varcnt = L1varcnt + 1;
			//規定回数以上カウントしているか判定
			if(L1varcnt > L1vartime){
				//設定値に達しているか判定
				if(L1nval > L1setvalue){
					if(DCBADcflg){
						DCBloadstopflg = true;
						R_PG_IO_PORT_Write_PF3(0x01);
						//R_PG_IO_PORT_Write_PA6(0x01);
					}
				}else if(L1nval > L1setvalue1){
					if(DCBADcflg){
						R_PG_DAC_ControlOutput_C1(DAset2);
					}
				}

				L1fixval = L1nval;
				//規定回数後の処理が完了後初期化
				L1nval = ADtval[0];
				L1varcnt = 1;
			}
		}else{
			//規定値を超えていれば、今回の値を初期値に設定
			L1nval = ADtval[0];
			L1varcnt = 1;
		}
	}
	
	//DZ処理中はAD変換処理中止
	if(!L2adstopflg){
		
		//AD�l��5��ώZ
		if(AD2_counter == 4){
			AD2_counter = 0;
		}else{
			AD2_counter = AD2_counter + 1;
		}
		AD2_buf[AD2_counter] = ADval[2];
		AD2_reg = 0;
		for(i=0;i<5;i++){
			AD2_reg = AD2_reg + AD2_buf[i];
		}
		ADtval[1] = AD2_reg / 5;
		
		//初期値との差分を取得
		if(ADtval[1] > L2nval){
			L2defval = ADtval[1] - L2nval;
		}else{
			L2defval = L2nval - ADtval[1];
		}
		
		//差分が規定値以内か判定
		if(L2defval < L2varval){
			L2varcnt = L2varcnt + 1;
			//規定回数以上カウントしているか判定
			if(L2varcnt > L2vartime){
				//設定値に達しているか判定
				if(L2nval > L2setvalue){
					if(DCB2ADcflg){
						DCB2loadstopflg = true;
						R_PG_IO_PORT_Write_PF2(0x01);
						//R_PG_IO_PORT_Write_PB4(0x01);
					}
				}
				else if(L2nval > L2setvalue1){
					if(DCB2ADcflg){
						R_PG_Timer_SetGTCCR_A_GPT_U0_C0(PWMvalue2);
						//Duty�l��GPT���W�X�^�ɏ�������
					}
				}
				L2fixval = L2nval;
				//規定回数後の処理が完了後初期化
				L2nval = ADtval[1];
				L2varcnt = 1;
			}
		}else{
			//規定値を超えていれば、今回の値を初期値に設定
			L2nval = ADtval[1];
			L2varcnt = 1;
		}
	}
}


//MTU3インプットキャプチャ割り込み
/*
void Mtu3IcCmCIntFunc(void){
	
	R_PG_Timer_GetTGR_MTU_U0_C3(0,0,& pulcnt,0,0,0);
	//TGRCの値をpulcntへ格納
	
	cntbuf = cntbuf + pulcnt;
	//cntbufに値を積算
	
	if(cntbuf < 5){
	//低回転数の時、測定精度を上げるため、積算を行う。
			
		j = j + 1;
		//積算回数を記録
		
	}
	else{
		
		plssend = cntbuf;
		plsrcnt = j;
		//送信用変数に値を代入
		
		j = 1;
		cntbuf = 0;
		//バッファを初期化
		
	}

}
*/
	

void returncmd(uint8_t cmd2){
	
	if(cmd2 == 0){
		Senddata[0] = 0x4f;//O
		Senddata[1] = 0x4b;//K
		Senddata[2] = 0x3e;//>
		Senddata[3] = 0x0d;//CR
		R_PG_SCI_StartSending_C1(Senddata,4);
	}
	else if(cmd2 == 1){
		Senddata[0] = 0x45;//E
		Senddata[1] = 0x72;//r
		Senddata[2] = 0x72;//r
		Senddata[3] = 0x32;//2
		Senddata[4] = 0x3e;//>
		Senddata[5] = 0x0d;//CR
		R_PG_SCI_StartSending_C1(Senddata,6);
	}
}

uint8_t valueascii(uint8_t val)
{
	uint8_t val1;
	
	if(val < 0x0a){
		val1 = val + 0x30;
	}
	else{
		val1 = val + 0x37;
	}
	return val1;
}


/* �w���v�Z, �߂�l = a^b */
double power_func(uint8_t a, int b)
{
	static uint8_t i;
	static double c;
	c = 1;
	if(b<0){
		b = b * -1;
		for(i=0;i<b;i++)
		{
			c = c / a;
		}
	}else if(b>0){
		for(i=0;i<b;i++)
		{
			c = c * a;
		}
	}
	return c;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
