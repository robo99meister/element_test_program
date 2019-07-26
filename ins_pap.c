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
#include "R_PG_ins_pap2.h"


void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void returncmd(uint8_t);
uint8_t valueascii(uint8_t);

int i;
int j=1;

double calPWM;

char cmd1[3];

bool ADsendflg;
bool DCBstartflg = false;
bool DCBintflg = false;
bool DCBrunflg = false;
bool DCB2startflg = false;
bool DCB2intflg = false;
bool DCB2runflg = false;
bool autoreverseflg = false;
bool ARstartflg = false;
bool ARwaitflg = false;

uint8_t Redata[4];
uint8_t delim;
uint8_t ShrCW, ShrCCW;
uint8_t Senddata[21];
uint8_t dataS[21];
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
uint8_t P26Highcnt,P26HighcntC,P26HighcntL;


//uint16_t a,b;

uint16_t DAset;
uint16_t DAsetp;
uint16_t CMTset;
uint16_t ADval[4];
uint16_t pulcnt;
uint16_t PCTset;
uint16_t cntbuf;
uint16_t plssend;
uint16_t PWMvalue;
uint16_t Areverselimit = 0.8 * 4095;
uint16_t AreverseDA;


void main(void)
{
	
	//クロック設定
	R_PG_Clock_WaitSet(0.01);
	
	//ポート設定
	initial_port();
	initial_SCI();
	initial_MTU();
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
	R_PG_Timer_StartCount_MTU_U0_C3();
	R_PG_Timer_StartCount_MTU_U0_C4();
	R_PG_Timer_StartCount_GPT_U0_C0();
	
	
	R_PG_SCI_StartReceiving_C1(Redata,4);
	
	while(1)
	{
		
	}
	
}

//RS232C送信後割り込み
void Sci1TrFunc(void)
{
	
	
	for(i=0; i<=20; i++){
		dataS[i] = Senddata[i];
		Senddata[i] = 0x00;
	}

}


//RS232C受信後割り込み
void Sci1ReFunc(void)
{
	
	R_PG_SCI_StartReceiving_C1(Redata,4);
	
	//デリミタの位置を検索
	for(i=0; i<=3; i++){
		if(Redata[i]==0x0d){
		//0x0d = "CR" CRの位置をdelim変数に格納
			delim=i;
		}
	}
	
	cmd1[0] = Redata[delim-3];
	cmd1[1] = Redata[delim-2];
	cmd1[2] = Redata[delim-1];
	
	//Bコマンド：シュレッダーモータオートリバース時の回転数変更
	if(!strncmp(cmd1,"B",1)){
		AreverseDA = ((Redata[delim-2] - 0x30) << 5) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//Cコマンド：シュレッダーモータ回転数変更
	else if(!strncmp(cmd1,"C",1)){
		DAset = 0x0000;
		//Cコマンド以降のデータをDAsetへ渡す
		DAset = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		R_PG_DAC_ControlOutput_C0(DAset);//DAC出力設定変更
		returncmd(0);//コマンド受信通知 0=OK>
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
	
	//Pコマンド：給紙モータ回転数変更
	else if(!strncmp(cmd1,"P",1)){
		DAsetp = 0x0000;
		//Pコマンド以降のデータをDAsetへ渡す
		DAsetp = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		R_PG_DAC_ControlOutput_C1(DAsetp);//DAC出力設定変更
		returncmd(0);//コマンド受信通知 0=OK>		
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
	
	//STAコマンド：シュレッダー回転開始
	else if(!strncmp(cmd1,"STA",3)){
		R_PG_IO_PORT_Write_PD2(ShrCW);
		R_PG_IO_PORT_Write_P04(ShrCCW);
		returncmd(0);
	}
	
	//STPコマンド：シュレッダー停止
	else if(!strncmp(cmd1,"STP",3)){
		R_PG_IO_PORT_Write_PD2(0x00);
		R_PG_IO_PORT_Write_P04(0x00);
		returncmd(0);
	}
	
	//STSコマンド：シュレッダーCW方向回転
	else if(!strncmp(cmd1,"STS",3)){
		ShrCW = 0x01;
		ShrCCW = 0x00;
		returncmd(0);
	}
	
	//STRコマンド：シュレッダーCCW方向回転
	else if(!strncmp(cmd1,"STR",3)){
		ShrCW = 0x00;
		ShrCCW = 0x01;
		returncmd(0);
	}
	
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
	
	//SPAコマンド：給紙モータ運転開始
	else if(!strncmp(cmd1,"SPA",3)){
		R_PG_IO_PORT_Write_PF3(0x00);
		DCBstartflg = true;
		DCBrunflg = true;
		DCBruncnt = 0;
		returncmd(0);
	}
	
	//SPPコマンド：給紙モータ停止
	else if(!strncmp(cmd1,"SPP",3)){
		R_PG_IO_PORT_Write_PF3(0x01);
		DCBstartflg = false;
		DCBruncnt = 0;
		returncmd(0);
	}
	
	//SPSコマンド：給紙モータCW回転方向設定
	else if(!strncmp(cmd1,"SPS",3)){
		R_PG_IO_PORT_Write_PA2(0x00);
		returncmd(0);
	}
	
	//SPRコマンド：給紙モータCCW回転方向設定
	else if(!strncmp(cmd1,"SPR",3)){
		R_PG_IO_PORT_Write_PA2(0x01);
		returncmd(0);
	}

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
	
	//S2Aコマンド：DCB2モータ回転開始
	else if(!strncmp(cmd1,"S2A",3)){
		R_PG_IO_PORT_Write_PF2(0x00);
		DCB2startflg = true;
		DCB2runflg = true;
		DCB2runcnt = 0;
		returncmd(0);
	}
	
	//S2Pコマンド：DCB2モータ回転停止
	else if(!strncmp(cmd1,"S2P",3)){
		R_PG_IO_PORT_Write_PF2(0x01);
		DCB2startflg = false;
		DCB2runcnt = 0;
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
	
	//INFコマンド：状態通知
	else if(!strncmp(cmd1,"INF",3)){
		
		//運転状態を通知
		//シュレッダー回転状態を通知
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
	
	//ADSコマンド：ADデータ送信要求
	else if(!strncmp(cmd1,"ADS",3)){
		//ADsendflg = true;
		//AD送信フラグをtrueに設定
		
		Senddata[0] = valueascii((ADval[1] >> 8) & 0x00F);
		Senddata[1] = valueascii((ADval[1] >> 4) & 0x00F);
		Senddata[2] = valueascii( ADval[1] & 0x00F); 
		
		Senddata[3] = valueascii((ADval[2] >> 8) & 0x00F);
		Senddata[4] = valueascii((ADval[2] >> 4) & 0x00F);
		Senddata[5] = valueascii( ADval[2] & 0x00F);
		
		Senddata[6] = valueascii(PORT0.PODR.BIT.B4);//シュレッダー CCW出力をモニタ
		
		Senddata[7] = 0x0d;
		//デリミタCRを付与
		
		R_PG_SCI_StartSending_C1(Senddata,8);

	}
	
	//QQQコマンド：Highカウント数を通知
	else if(!strncmp(cmd1,"QQQ",3)){
		Senddata[0] = valueascii((P26Highcnt >> 4) & 0x0F);
		Senddata[1] = valueascii( P26Highcnt & 0x0F);
		Senddata[2] = 0x0d;
		
		R_PG_SCI_StartSending_C1(Senddata,3);
	}
	
	//RPSコマンド：パルスカウント数送信要求
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
	
	

	//未対応コマンドの場合エラー
	else{
		returncmd(1);
	}
	
	//デリミタ格納変数を初期化
	delim=0x00;
		
}

//CMT割り込み
void Cmt0IntFunc(void)
{
	R_PG_ADC_12_StartConversion_S12AD0();
	//CMT割り込みでAD変換開始
	
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
			if(DCB2runcnt < Runtime2){
			//Runtimeまでカウント
				DCB2runcnt = DCB2runcnt + 1;
			}else{
			//Runtimeカウント完了後
				DCB2runcnt = 0;
				DCB2runflg = false;
				R_PG_IO_PORT_Write_PF2(0x01);
				//DCB2運転停止
			}
		}else{
		//DCB停止中
			if(DCB2runcnt < Stoptime2){
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
	
	//インターロック動作
	//5回連続一致で設定リセット
	if(PORT2.PIDR.BIT.B6 == 0){
	//P26 = Lowの時、カウントをリセット
		P26HighcntC = 0;
		if(!(P26HighcntC == 0)){
			P26HighcntL = P26HighcntL + 1;
		}
	}else{
		//3回連続High検出までカウント
		if(P26HighcntC < 3){
			P26HighcntC = P26HighcntC + 1;
			P26HighcntL = P26HighcntL + 1;
		//3回連続一致後、動作停止
		}else{
			//シュレッダー動作停止
			R_PG_IO_PORT_Write_PD2(0x00);
			R_PG_IO_PORT_Write_P04(0x00);
			ARwaitflg = false;
			//搬送ローラー停止
			R_PG_IO_PORT_Write_PF3(0x01);
			DCBstartflg = false;
			//ピックローラー停止
			R_PG_IO_PORT_Write_PF2(0x01);
			DCB2startflg = false;
			P26HighcntC = 0;
		}
		P26Highcnt = P26Highcnt + 1;
	}
	
	LED0 = LED0 ^ 0x01;
	
	R_PG_IO_PORT_Write_P71(LED0);
	
}

//AD変換完了割り込み
void S12ad0AIntFunc(void)
{
	R_PG_ADC_12_GetResult_S12AD0(ADval);
	//AD変換の結果をADvalに格納
	//ADval[0]:可変抵抗出力
	//ADval[1]:外部入力0-10V
	//ADval[2]:外部入力4-20mA
	
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
	
}


//MTU3インプットキャプチャ割り込み
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
	

void returncmd(uint8_t cmd2){
	
	if(cmd2 == 0){
		Senddata[0] = 0x4f;
		Senddata[1] = 0x4b;
		Senddata[2] = 0x3e;
		Senddata[3] = 0x0d;
		R_PG_SCI_StartSending_C1(Senddata,4);
	}
	else if(cmd2 == 1){
		Senddata[0] = 0x45;
		Senddata[1] = 0x72;
		Senddata[2] = 0x72;
		Senddata[3] = 0x32;
		Senddata[4] = 0x3e;
		Senddata[5] = 0x0d;
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

#ifdef __cplusplus
void abort(void)
{

}
#endif
