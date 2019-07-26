/***********************************************************************
*
*  FILE        : RX66T_e2s_test_project.c
*  DATE        : 2019-05-14
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include <stdio.h>
#include <string.h>

/* CMT0割り込みフラグ */
extern volatile uint8_t g_CMT0_intrpt_flag;

/* MTU3カウント数量バッファ */
volatile uint32_t g_MTU3_stop_counter;
volatile uint32_t g_MTU3_stop_receive_count;

/* MTU3出力パルス数のカウント */
extern volatile uint32_t g_MTU3_output_pulse_counter;

/* MTU3 GTRAコンペアマッチ割り込みフラグ */
extern volatile uint8_t g_MTU3_TGRA_intrpt_flag;

/* グローバル変数 CMT0インターバル設定 */
volatile uint16_t interval_level = 1;

/* PCへのメッセージ用変数 */
static char print_str[80];

/* PCからのデータ受信フラグ */
extern volatile uint8_t g_rx_flag;

/* グローバル変数 PCからの受信バッファ */
extern volatile uint8_t g_rx_char[80];

static char rdata[10],sdata[15];
static uint8_t i,j,k,l,cala, MTU3_step_interval, MTU3_startup_flag, MTU3_ENC_stop_flag;
static uint16_t pulsecnt, MTU3_wait_count[100], MTU3_TGRA_value[100], MTU3_step_number,
				MTU3_short_stop_counter_value, MTU3_step_counter, GPT0_stop_counter;
static uint32_t MTU3_Sdown_counter, MTU3_waittime_counter, MTU3_short_stop_count, ENC_counter_stop_value;
static double caldata, MTU3_slew_rate;
static double calc;

/* SCI11データ転送関数 */
MD_STATUS R_SCI11_AsyncTransmit(uint8_t * const tx_buf, const uint16_t tx_num);

double power(double a, double b);

void main(void);

void main(void)
{
	/* CMT0 タイマスタート */
	R_Config_CMT0_Start();
	/* GPT0 タイマスタート */
	R_Config_GPT0_Start();
	/* GPT1タイマスタート */
	R_Config_GPT1_Start();
	/* SCI11受信バッファアドレスと受信割り込みのセット*/
	R_Config_SCI11_Serial_Receive((uint8_t *)&g_rx_char, 14);
	/* SCI11動作開始 */
	R_Config_SCI11_Start();
	sprintf(print_str,"ID01RB\r");
	/* レジスタへの読み書き許可 */
	MTU.TRWERA.BIT.RWE = 1U;
	g_MTU3_stop_receive_count = 300001;
	MTU3_step_interval = 10;
	MTU3_step_number = 20;

	while(1U)
	{
		/* CMT0 割り込み処理 */
		if(g_CMT0_intrpt_flag == 1U)
		{
			/* CMT0割り込みフラグリセット */
			g_CMT0_intrpt_flag = 0U;
			/* 汎用PWMのカウンタ値を変数に保存(モニタ用)
			 * MTIOC3A出力とGTIOC1A入力を短絡
			 * パルス数を汎用PWMにてモニタ*/
			g_MTU3_stop_counter = GPTW1.GTCNT;
			/* SW1の入力と1pinの出力を連動
			 * SW1 ON で 1pin Lo出力
			 * SW1 OFFで 1pin Hi出力 */
			if(PORT1.PIDR.BIT.B0 == 0U){
				PORTE.PODR.BIT.B5 = 0U;
			}
			else{
				PORTE.PODR.BIT.B5 = 1U;
			}
		}
		/* SCI11 割り込み処理 シリアル通信受信コマンド */
		if(g_rx_flag == 1U)
		{
			/* SCI11受信バッファアドレスと受信割り込みのセット*/
			R_Config_SCI11_Serial_Receive((uint8_t *)&g_rx_char, 14);
			/* SCI11受信割り込みフラグリセット */
			g_rx_flag = 0U;
			/* RBコマンド 数値読み取り場合の動作 */
			if(g_rx_char[4] == 'R' && g_rx_char[5] == 'B')
			{
				/* 戻り値の±判別 */
				if(g_rx_char[6] == '+')
				{
					for(i=0;i<6;i++)
					{
						/* 小数点位置の検索 */
						rdata[i] = g_rx_char[i+7];
						if(rdata[i] == '.')
						{
							j = i;
						}
					}
				}
				else
				{/* 値が負なら"0"に設定 */
					for(i=0;i<6;i++)
					{
						rdata[i] = '0';
					}
				}
				/* 値初期化 */
				caldata = 0;
				for(i=0;i<6;i++)
				{
					if(i==j)
					{
						//
					}
					else
					{
						/* 小数点からのずれ量を指数にし、文字列→数値変換を実施 */
						caldata = caldata + ( rdata[i] - 0x30 ) * power(10, j-i);
					}
				}
				/* 数値→文字列変換 最大"12345."のため、値を10以下に変更する。 */
				calc = caldata / 10000;
				for(l=0;l<11;l++)
				{
					if(l==5)
					{
						/* 小数点を挿入 */
						sdata[l] = '.';
					}
					else
					{
						/* 変数を整数に変換し、小数点以下を削除 */
						cala = calc;
						/* 0x30を足してASCIIコードに変換 */
						sdata[l] = cala + 0x30;
						/* 元の値から小数点以下を取り出す */
						calc = calc - cala;
						/* 次の桁の計算を行うため、10倍する */
						calc = calc * 10;
					}
				}
				sdata[11] = 0x0d;
				/* 変換後の文字列をPCへ送信 */
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 12);
			}
			/* CNコマンド カウント数を送信
			 * pulsecnt変数の値を送信
			 * 16bit変数のため、4bitずつ文字列に変換(+0x40)して送信*/
			else if(g_rx_char[4] == 'C' && g_rx_char[5] == 'N')
			{
				for(l=0;l<4;l++)
				{
					sdata[l] = ((pulsecnt >> (12 - 4 * l)) & 0x000F) + 0x40;
				}
				sdata[4] = 0x0d;
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 5);
			}
			/* HIコマンド MTU4の速度を上げる */
			else if(g_rx_char[4] == 'H' && g_rx_char[5] == 'I')
			{
				if(MTU4.TGRC > 10)
				{
					/* レジスタへの読み書き許可 */
					MTU.TRWERA.BIT.RWE = 1U;
					/* レジスタの値変更 */
					MTU4.TGRA = MTU4.TGRA >> 1;
					MTU4.TGRB = MTU4.TGRB >> 1;
					MTU4.TGRC = MTU4.TGRC >> 1;
					MTU4.TGRD = MTU4.TGRD >> 1;
					/* レジスタの読み書き禁止 */
					MTU.TRWERA.BIT.RWE = 0U;
					/* 完了応答 */
					sdata[0] = 'F';
					sdata[1] = 'A';
					sdata[2] = 'S';
					sdata[3] = 'T';
					sdata[4] = 0x0d;
					R_Config_SCI11_Serial_Send((uint8_t *)&sdata,5);
				}
				else
				{
					sdata[0] = 'M';
					sdata[1] = 'A';
					sdata[2] = 'X';
					sdata[3] = 0x0d;
					R_Config_SCI11_Serial_Send((uint8_t *)&sdata,4);
				}
			}
			/* LOコマンド MTU4の速度を下げる*/
			else if(g_rx_char[4] == 'L' && g_rx_char[5] == 'O')
			{
				if(MTU4.TGRA < 30000)
				{
					/* レジスタの読み書き許可 */
					MTU.TRWERA.BIT.RWE = 1U;
					/* レジスタの値変更 */
					MTU4.TGRA = MTU4.TGRA << 1;
					MTU4.TGRB = MTU4.TGRB << 1;
					MTU4.TGRC = MTU4.TGRC << 1;
					MTU4.TGRD = MTU4.TGRD << 1;
					/* レジスタの読み書き禁止 */
					MTU.TRWERA.BIT.RWE = 0U;
					/* 完了応答 */
					sdata[0] = 'S';
					sdata[1] = 'L';
					sdata[2] = 'O';
					sdata[3] = 'W';
					sdata[4] = 0x0d;
					R_Config_SCI11_Serial_Send((uint8_t *)&sdata,5);
				}
				else
				{
					sdata[0] = 'M';
					sdata[1] = 'I';
					sdata[2] = 'N';
					sdata[3] = 0x0d;
					R_Config_SCI11_Serial_Send((uint8_t *)&sdata,4);
				}
			}
			/* RGコマンド GPT0カウンタ値を読み取る */
			else if(g_rx_char[4] == 'R' && g_rx_char[5] == 'G')
			{
				for(i=0;i<4;i++){
					sdata[i] = (GPTW0.GTCNT >> (12 - (i * 4)) & 0x000F) + 0x40;
				}
				sdata[4] = 0x0d;
				/* 変換後の文字列をPCへ送信 */
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 5);
			}
			/* STコマンド GPT0カウント目標値を受信 6桁 pulse(16bit)
			 * エンコーダの目標パルス Pt */
			else if(g_rx_char[4] == 'S' && g_rx_char[5] == 'T')
			{
				/* カウント目標値を文字列から数字に変換 */
				GPT0_stop_counter = 0;
				for(i=0;i<6;i++)
				{
					GPT0_stop_counter = GPT0_stop_counter + ((g_rx_char[i+7] - 0x30) * power(10,5-i));
					sdata[i] = g_rx_char[i+7];
				}
				sdata[7] = 0x0d;
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 8);
			}
			/* RMコマンド MTU3の送信済みパルス数を送信 */
			else if(g_rx_char[4] == 'R' && g_rx_char[5] == 'M')
			{
				for(i=0;i<8;i++){
					sdata[i] = (g_MTU3_output_pulse_counter >> (28 - (i * 4)) & 0x000F) + 0x40;
				}
				sdata[8] = 0x0d;
				/* 変換後の文字列をPCへ送信 */
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 9);
			}
			/* SPコマンド MTU3 加速ステップ間隔を受信 3桁 ms単位(8bit)
			 * 初期値：10ms */
			else if(g_rx_char[4] == 'S' && g_rx_char[5] == 'P')
			{
				/* ステップ間隔初期化 */
				MTU3_step_interval = 0;
				/* 受信文字列を数値に変換 */
				for(i=7;i<10;i++)
				{
					MTU3_step_interval = MTU3_step_interval + (g_rx_char[i] - 0x30) * power(10, 9 - i);
					sdata[i-7] = g_rx_char[i];
				}
				/* 受信完了応答 */
				sdata[3] = 0x0d;
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 4);
			}
			/* SCコマンド MTU3 加速ステップ数を受信 3桁 steps(16bit)
			 * 初期値：20step */
			else if(g_rx_char[4] == 'S' && g_rx_char[5] == 'C')
			{
				/* ステップ数を初期化 */
				MTU3_step_number = 0;
				/* 受信文字列を数値に変換 */
				for(i=7;i<10;i++)
				{
					MTU3_step_number = MTU3_step_number + (g_rx_char[i] - 0x30) * power(10, 9 - i);
					sdata[i-7] = g_rx_char[i];
				}
				/* 受信完了応答 */
				sdata[3] = 0x0d;
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 4);
			}
			/* FVコマンド MTU3の周波数変化率を受信 6桁 Hz/step単位 */
			else if(g_rx_char[4] == 'F' && g_rx_char[5] == 'V')
			{
				/* スルーレートの初期化 */
				MTU3_slew_rate = 0;
				/* 小数点の位置を検索
				 * 小数点が見つからなければ、7文字目に小数点を設定 */
				for(i=0;i<7;i++)
				{
					if(g_rx_char[i+7] == '.'){
						j = i;
						break;
					}
					j = i + 1;
				}
				/* 受信文字列を数値に変換 */
				for(i=0;i<7;i++)
				{
					if(j > i){
						MTU3_slew_rate = MTU3_slew_rate + (g_rx_char[i+7] - 0x30) * power(10, j - i - 1);
					}else if(j < i){
						MTU3_slew_rate = MTU3_slew_rate + (g_rx_char[i+7] - 0x30) * power(10, j - i);
					}
					sdata[i-7] = g_rx_char[i];
				}
				/* 受信完了応答 */
				sdata[6] = 0x0d;
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 7);
			}
			/* PCコマンド MTU3の総ステップ数を受信 6桁 1pulse単位 */
			else if(g_rx_char[4] == 'P' && g_rx_char[5] == 'C')
			{
				/* MTU3カウント値の初期化 */
				g_MTU3_stop_receive_count = 0;
				/* 総パルス数を数値に変換 */
				for(i=7;i<13;i++)
				{
					g_MTU3_stop_receive_count = g_MTU3_stop_receive_count + (g_rx_char[i] - 0x30) * power(10,12-i);
					sdata[i-7] = g_rx_char[i];
				}
				/* 受信完了応答 */
				sdata[6] = 0x0d;
				R_Config_SCI11_Serial_Send((uint8_t *)&sdata, 7);
				/* 受信パルス数が偶数の場合、奇数に変換 */
				if((g_MTU3_stop_receive_count & 1) == 0)
				{
					g_MTU3_stop_receive_count--;
				}
			}
			/* 3Aコマンド MTU3 カウントスタート */
			else if(g_rx_char[4] == '3' && g_rx_char[5] == 'A')
			{
				/* 各ステップでの待機ステップを計算 */
				MTU3_Sdown_counter = 0;
				for(k=0;k<MTU3_step_number + 1;k++)
				{
					/* 待機パルス数の計算
					 * 運転周波数 = (開始周波数:50Hz + 加速レート x ステップ数)
					 * 待機パルス数 = 運転周波数Hz / 1000 x ステップ間隔ms x 2
					 *                                             ^^^
					 *                                             ↑コンペアマッチでトグル出力のため2パルスで1周期 */
					MTU3_wait_count[k] = ((50 + MTU3_slew_rate * k) * 2 * MTU3_step_interval) / 1000;
					/* 各ステップでのレジスタ値を計算
					 * コンペアマッチ周期 = レジスタ値 / 基準周波数
					 * 運転周波数 = 1 / (コンペアマッチ周期 * 2)
					 * コンペアマッチレジスタの値 = 基準周波数 5MHz / (目標周波数Hz x 2) */
					MTU3_TGRA_value[k] = 2500000 / (50 + MTU3_slew_rate * k);
					/* 加速に必要なパルス数を計算
					 * 各ステップ毎の待機パルス数を積算 */
					MTU3_Sdown_counter = MTU3_Sdown_counter + MTU3_wait_count[k];
				}
				MTU3_TGRA_value[MTU3_step_number + 1] = MTU3_TGRA_value[MTU3_step_number];

				/* 加速中に総パルス数に到達する場合、加速時間を短縮する。 */
				if(g_MTU3_stop_receive_count < (MTU3_Sdown_counter * 2))
				{
					/* 加速を中断するパルスを決定する。 */
					MTU3_short_stop_count = 0;
					MTU3_short_stop_counter_value = 0;
					/* 加速中の累積パルス数が、総パルスの1/2となるステップを検索
					 * 加速時の待機パルスを総パルスの1/2を超えるまで積算し、超えた時のステップ数を記録
					 * ループ完了時、ステップ数は1多いので、最後に-1する。 */
					while(MTU3_short_stop_count < (g_MTU3_stop_receive_count / 2))
					{
						MTU3_short_stop_count = MTU3_short_stop_count + MTU3_wait_count[MTU3_short_stop_counter_value];
						MTU3_short_stop_counter_value++;
					}
					MTU3_short_stop_counter_value--;
					if(MTU3_short_stop_counter_value > 0)
					{
						MTU3_short_stop_count = MTU3_short_stop_count - MTU3_wait_count[MTU3_short_stop_counter_value];
						MTU3_short_stop_counter_value--;
					}
				}
				else
				{
					MTU3_short_stop_count = 0;
				}
				/* 開始周波数 = 50Hz */
				MTU3.TGRA = 49999;
				MTU3.TGRC = 49999;
				/* ステップカウンタ初期化 */
				MTU3_step_counter = 0;
				/* TGRAコンペアマッチ割り込みフラグの初期化 */
				g_MTU3_TGRA_intrpt_flag = 0U;
				/* パルスカウント用汎用PWM1のカウンタをリセット(出力パルスカウント用疑似入力) */
				//R_Config_GPT1_Software_Clear();
				/* 加速動作フラグをセット */
				MTU3_startup_flag = 1U;
				/* 加速ステップ待機用カウンタリセット */
				MTU3_waittime_counter = 0;
				/* MTU3出力パルスカウンタリセット*/
				g_MTU3_output_pulse_counter = 0;
				/* MTU3 エンコーダカウント停止フラグをリセット*/
				MTU3_ENC_stop_flag = 0U;
				/* MTU3動作開始 */
				R_Config_MTU3_Start();
				/* GPT0 カウンタリセット */
				R_Config_GPT0_Software_Clear();
				/* MTU4 タイマスタート(疑似エンコーダ用出力) */
				//R_Config_MTU4_Start();
			}
		}
		/* MTU3 TGRAコンペアマッチ割り込み */
		if(g_MTU3_TGRA_intrpt_flag == 1U)
		{
			/* 割り込みフラグの初期化 */
			g_MTU3_TGRA_intrpt_flag = 0U;
			/* 総パルス数経過したか判定 */
			if(g_MTU3_stop_receive_count > 0)
			{
				/* LED1を1/10周期で点滅させる。 */
				PORT9.PODR.BIT.B5 = (g_MTU3_stop_receive_count >> 10) & 0x01;
				/* 総パルスカウンタを1減らす */
				g_MTU3_stop_receive_count--;
				/* エンコーダカウント値が目標値を超えているか判定 */
				if(MTU3_ENC_stop_flag == 0U && (GPT0_stop_counter - 1) < GPTW0.GTCNT)
				{
					MTU3_ENC_stop_flag = 1U;
					ENC_counter_stop_value = g_MTU3_output_pulse_counter;
					/* エンコーダカウントが超えていれば、シャットダウンシーケンスに移行する
					 * まだ起動シーケンス中の場合、ここまでに出力したパルス数分で停止させる。 */
					if(g_MTU3_output_pulse_counter < MTU3_Sdown_counter)
					{
						MTU3_startup_flag = 0U;
						g_MTU3_stop_receive_count = g_MTU3_output_pulse_counter;
					}
					/* 定速運転中なら、直ちに減速停止に移行させる。
					 * 総パルスカウンタは、減速に必要なパルス数に設定。
					 * 減速停止中なら値の変更はせず、そのまま停止シーケンスを続行させる。 */
					else if(g_MTU3_stop_receive_count > MTU3_Sdown_counter)
					{
						MTU3_startup_flag = 0U;
						g_MTU3_stop_receive_count = MTU3_Sdown_counter;
					}

				}
				/* 起動時及び停止時、ステップカウンタで速度を調整する。 */
				if(MTU3_startup_flag == 1U)
				{
					/* 規定カウント数まで同じ周波数で回転 */
					MTU3_waittime_counter++;
					/* 総パルスが起動時間より短い場合、途中で終了シーケンスに移行する。 */
					if(g_MTU3_stop_receive_count == MTU3_short_stop_count)
					{
						MTU3_startup_flag = 0U;
						MTU3_step_counter = MTU3_short_stop_counter_value;
						MTU3_waittime_counter = 0;
						MTU3.TGRC = MTU3_TGRA_value[MTU3_step_counter];
					}
					else if(MTU3_waittime_counter == MTU3_wait_count[MTU3_step_counter])
					{
						/* ステップ数に応じた回転数へレジスタ値を変更 */
						MTU3.TGRC = MTU3_TGRA_value[MTU3_step_counter + 1];
						MTU3_waittime_counter = 0;
						/* 最終ステップまで到達していれば、加速中フラグをOFFにする。
						 * ステップの途中ならば、次のステップへ移行する。*/
						if(MTU3_step_counter == MTU3_step_number)
						{
							MTU3_startup_flag = 0U;
						}
						else
						{
							MTU3_step_counter++;
						}
					}
				}
				/* 停止シーケンス開始カウントまで待機
				 * 停止シーケンス中は、ステップカウンタを減らす。 */
				else if(g_MTU3_stop_receive_count < MTU3_Sdown_counter)
				{
					MTU3_waittime_counter++;
					if(MTU3_waittime_counter == MTU3_wait_count[MTU3_step_counter])
					{
						MTU3_waittime_counter = 0;
						if(MTU3_step_counter > 0)
						{
							MTU3_step_counter--;
							MTU3.TGRC = MTU3_TGRA_value[MTU3_step_counter];
						}
						else
						{
							MTU3.TGRC = MTU3_TGRA_value[0];
						}
					}
				}
			}
			else
			{
				/* カウント完了後、タイマストップ */
				R_Config_MTU3_Stop();
				PORT9.PODR.BIT.B5 = 1U;
				/* 変数の初期化 */
				MTU3_step_counter = 0;
				MTU3_waittime_counter = 0;
				/* MTU4 タイマストップ(疑似エンコーダ用出力 */
				//R_Config_MTU4_Stop();
			}

		}
	}
}

/* 指数計算をする関数
 * power( 底, 指数)
 * a ^ b を計算*/
double power(double a, double b)
{
	static double c;

	c = 1;
	/* 指数の符号判別 */
	if(b>0)
	{
		/* 指数が正なら、指定回数分底をかけ算*/
		while(b > 0)
		{
			c = c * a;
			b--;
		}
	}
	else
	{
		/* 指数が負なら、指定回数分底の逆数をかけ算 */
		while(b < 0)
		{
			c = c * 1 / a;
			b++;
		}
	}
	return c;
}
