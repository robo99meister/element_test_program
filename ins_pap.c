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
	
	//�N���b�N�ݒ�
	R_PG_Clock_WaitSet(0.01);
	
	//�|�[�g�ݒ�
	initial_port();
	initial_SCI();
	initial_MTU();
	initial_S12AD();
	initial_DA();
	initial_CMT();
	
	//GPT�����ݒ�
	R_PG_Timer_Set_GPT_U0();
	R_PG_Timer_Set_GPT_U0_C0();
	
	PWMvalue = 0;
	
	R_PG_Timer_SetGTCCR_A_GPT_U0_C0(PWMvalue);
	
	//�^�C�}�J�E���g�J�n
	R_PG_Timer_StartCount_CMT_U0_C0();
	R_PG_Timer_StartCount_MTU_U0_C3();
	R_PG_Timer_StartCount_MTU_U0_C4();
	R_PG_Timer_StartCount_GPT_U0_C0();
	
	
	R_PG_SCI_StartReceiving_C1(Redata,4);
	
	while(1)
	{
		
	}
	
}

//RS232C���M�㊄�荞��
void Sci1TrFunc(void)
{
	
	
	for(i=0; i<=20; i++){
		dataS[i] = Senddata[i];
		Senddata[i] = 0x00;
	}

}


//RS232C��M�㊄�荞��
void Sci1ReFunc(void)
{
	
	R_PG_SCI_StartReceiving_C1(Redata,4);
	
	//�f���~�^�̈ʒu������
	for(i=0; i<=3; i++){
		if(Redata[i]==0x0d){
		//0x0d = "CR" CR�̈ʒu��delim�ϐ��Ɋi�[
			delim=i;
		}
	}
	
	cmd1[0] = Redata[delim-3];
	cmd1[1] = Redata[delim-2];
	cmd1[2] = Redata[delim-1];
	
	//B�R�}���h�F�V�����b�_�[���[�^�I�[�g���o�[�X���̉�]���ύX
	if(!strncmp(cmd1,"B",1)){
		AreverseDA = ((Redata[delim-2] - 0x30) << 5) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//C�R�}���h�F�V�����b�_�[���[�^��]���ύX
	else if(!strncmp(cmd1,"C",1)){
		DAset = 0x0000;
		//C�R�}���h�ȍ~�̃f�[�^��DAset�֓n��
		DAset = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		R_PG_DAC_ControlOutput_C0(DAset);//DAC�o�͐ݒ�ύX
		returncmd(0);//�R�}���h��M�ʒm 0=OK>
	}
	
	//D�R�}���h�F�C���^�[�o���^�]�̉^�]���ԕύX
	else if(!strncmp(cmd1,"D",1)){
		Runtime2 = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//E�R�}���h�F�C���^�[�o���^�]�̒�~���ԕύX
	else if(!strncmp(cmd1,"E",1)){
		Stoptime2 = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//F�R�}���h�F�I�[�g���o�[�X���̋t��]���Ԑݒ�
	else if(!strncmp(cmd1,"F",1)){
		Areversetime = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//G�R�}���h�F�I�[�g���o�[�X���쎞��AD���~�b�g��ݒ�
	else if(!strncmp(cmd1,"G",1)){
		Areverselimit = ((Redata[delim-2] - 0x30) << 6) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//P�R�}���h�F�������[�^��]���ύX
	else if(!strncmp(cmd1,"P",1)){
		DAsetp = 0x0000;
		//P�R�}���h�ȍ~�̃f�[�^��DAset�֓n��
		DAsetp = ( ( Redata[delim-2] - 0x30 ) << 5 ) + (Redata[delim-1] - 0x30 ) ;
		R_PG_DAC_ControlOutput_C1(DAsetp);//DAC�o�͐ݒ�ύX
		returncmd(0);//�R�}���h��M�ʒm 0=OK>		
	}
	
	//T�R�}���h�FCMT�g���K�^�C�~���O�ύX
	else if(!strncmp(cmd1,"T",1)){
		CMTset = ( ( ( Redata[delim-2] - 0x30 ) * 10 ) + ( Redata[delim-1] - 0x30 )  ) * 937 ;
		
		if(CMTset>=61000){
			returncmd(1);
			//�ݒ�\�͈͊O �G���[�ʒm
		}
		else{
			R_PG_Timer_SetConstantRegister_CMT_U0_C0(CMTset);
			returncmd(0);
			//CMT���W�X�^�ݒ�ύX
		}
	}
	
	//U�R�}���h�F�C���^�[�o���^�]�̉^�]���ԕύX
	else if(!strncmp(cmd1,"U",1)){
		Runtime = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}
	
	//V�R�}���h�F�C���^�[�o���^�]�̒�~���ԕύX
	else if(!strncmp(cmd1,"V",1)){
		Stoptime = ((Redata[delim-2] - 0x30) * 10) + (Redata[delim-1] - 0x30);
		returncmd(0);
	}

	//X�R�}���h�F�p���X���擾�����̕ύX
	else if(!strncmp(cmd1,"X",1)){
		
		PCTset = ( ( ( Redata[delim-2] - 0x30 ) * 10 ) + ( Redata[delim-1] - 0x30 )  ) * 937 ;
		
		if(PCTset>=61000){
			returncmd(1);
			//�ݒ�\�͈͊O �G���[�ʒm
		}
		else{
			R_PG_Timer_SetTGR_C_MTU_U0_C4(PCTset);
			returncmd(0);
			//CMT���W�X�^�ݒ�ύX
		}
	}
	
	//Y�R�}���h�FPWM�o�͂�ύX
	else if(!strncmp(cmd1,"Y",1)){
		
		PWMvalue = 0x0000;
		
		PWMvalue = ( ( Redata[delim-2] - 0x30 ) << 6 ) | (Redata[delim-1] - 0x30 ) ;
		//12bit�f�[�^��PWMvalue�Ɋi�[
		//0�`100%��12bit�f�[�^�Ƃ��Ď�M����B
		
		calPWM = 4799900/4095;
		
		calPWM = calPWM * PWMvalue;
		
		//calPWM = calPWM * ( 47999 / 4095 );
		//��M�f�[�^(�䗦)�ƃJ�E���g�������|���ADuty��ݒ�
		
		PWMvalue = calPWM/100;
		
		R_PG_Timer_SetGTCCR_A_GPT_U0_C0(PWMvalue);
		//Duty�l��GPT���W�X�^�ɏ�������
		
		returncmd(0);
	}
	
	//STA�R�}���h�F�V�����b�_�[��]�J�n
	else if(!strncmp(cmd1,"STA",3)){
		R_PG_IO_PORT_Write_PD2(ShrCW);
		R_PG_IO_PORT_Write_P04(ShrCCW);
		returncmd(0);
	}
	
	//STP�R�}���h�F�V�����b�_�[��~
	else if(!strncmp(cmd1,"STP",3)){
		R_PG_IO_PORT_Write_PD2(0x00);
		R_PG_IO_PORT_Write_P04(0x00);
		returncmd(0);
	}
	
	//STS�R�}���h�F�V�����b�_�[CW������]
	else if(!strncmp(cmd1,"STS",3)){
		ShrCW = 0x01;
		ShrCCW = 0x00;
		returncmd(0);
	}
	
	//STR�R�}���h�F�V�����b�_�[CCW������]
	else if(!strncmp(cmd1,"STR",3)){
		ShrCW = 0x00;
		ShrCCW = 0x01;
		returncmd(0);
	}
	
	//STB�R�}���h�F�I�[�g���o�[�X�@�\��L����
	else if(!strncmp(cmd1,"STB",3)){
		autoreverseflg = true;
		returncmd(0);
	}
	
	//STC�R�}���h�F�I�[�g���o�[�X�@�\�𖳌���
	else if(!strncmp(cmd1,"STC",3)){
		autoreverseflg = false;
		returncmd(0);
	}
	
	//SPA�R�}���h�F�������[�^�^�]�J�n
	else if(!strncmp(cmd1,"SPA",3)){
		R_PG_IO_PORT_Write_PF3(0x00);
		DCBstartflg = true;
		DCBrunflg = true;
		DCBruncnt = 0;
		returncmd(0);
	}
	
	//SPP�R�}���h�F�������[�^��~
	else if(!strncmp(cmd1,"SPP",3)){
		R_PG_IO_PORT_Write_PF3(0x01);
		DCBstartflg = false;
		DCBruncnt = 0;
		returncmd(0);
	}
	
	//SPS�R�}���h�F�������[�^CW��]�����ݒ�
	else if(!strncmp(cmd1,"SPS",3)){
		R_PG_IO_PORT_Write_PA2(0x00);
		returncmd(0);
	}
	
	//SPR�R�}���h�F�������[�^CCW��]�����ݒ�
	else if(!strncmp(cmd1,"SPR",3)){
		R_PG_IO_PORT_Write_PA2(0x01);
		returncmd(0);
	}

	//SPI�R�}���h�FDCB���[�^�C���^�[�o���^�]�w��
	else if(!strncmp(cmd1,"SPI",3)){
		DCBintflg = true;
		returncmd(0);
	}
	
	//SPJ�R�}���h�FDCB���[�^�C���^�[�o���^�]��~�w��
	else if (!strncmp(cmd1,"SPJ",3)){
		DCBintflg = false;
		returncmd(0);
	}
	
	//S2A�R�}���h�FDCB2���[�^��]�J�n
	else if(!strncmp(cmd1,"S2A",3)){
		R_PG_IO_PORT_Write_PF2(0x00);
		DCB2startflg = true;
		DCB2runflg = true;
		DCB2runcnt = 0;
		returncmd(0);
	}
	
	//S2P�R�}���h�FDCB2���[�^��]��~
	else if(!strncmp(cmd1,"S2P",3)){
		R_PG_IO_PORT_Write_PF2(0x01);
		DCB2startflg = false;
		DCB2runcnt = 0;
		returncmd(0);
	}
	
	//S2S�R�}���h�FDCB2���[�^CW������]
	else if(!strncmp(cmd1,"S2S",3)){
		R_PG_IO_PORT_Write_P34(0x00);
		returncmd(0);
	}
	
	//S2R�R�}���h�FDCB2���[�^CCW������]
	else if(!strncmp(cmd1,"S2R",3)){
		R_PG_IO_PORT_Write_P34(0x01);
		returncmd(0);
	}
	
	//S2I�R�}���h�FDCB2�C���^�[�o���^�]�w��
	else if(!strncmp(cmd1,"S2I",3)){
		DCB2intflg = true;
		returncmd(0);
	}
	
	//S2J�R�}���h�FDCB2�C���^�[�o���^�]��~�w��
	else if(!strncmp(cmd1,"S2J",3)){
		DCB2intflg = false;
		returncmd(0);
	}
	
	//INF�R�}���h�F��Ԓʒm
	else if(!strncmp(cmd1,"INF",3)){
		
		//�^�]��Ԃ�ʒm
		//�V�����b�_�[��]��Ԃ�ʒm
		Senddata[0] = valueascii(PORTD.PODR.BIT.B2);//CW�o�͏��(0:Lo)
		Senddata[1] = valueascii(PORT0.PODR.BIT.B4);//CCW�o�͏��(1:Hi)
		
		//��]����ʒm 3byte
		Senddata[2] = valueascii((DA.DADR0 >> 8) & 0x00F);
		Senddata[3] = valueascii((DA.DADR0 >> 4) & 0x00F);
		Senddata[4] = valueascii(DA.DADR0 & 0x00F); 
		
		//DCB��]��Ԃ�ʒm
		Senddata[5] = valueascii(PORTA.PODR.BIT.B2);//��]���� CW/CCW
		Senddata[6] = valueascii(PORTF.PODR.BIT.B3);//START/STOP
		
		//��]����ʒm 3byte
		Senddata[7] = valueascii((DA.DADR1 >> 8) & 0x00F);
		Senddata[8] = valueascii((DA.DADR1 >> 4) & 0x00F);
		Senddata[9] = valueascii(DA.DADR1 & 0x00F);
		
		//CMT���������ʒm 4byte
		Senddata[10] = valueascii((CMT0.CMCOR >> 12) & 0x000F);
		Senddata[11] = valueascii((CMT0.CMCOR >> 8) & 0x000F);
		Senddata[12] = valueascii((CMT0.CMCOR >> 4) & 0x000F);
		Senddata[13] = valueascii(CMT0.CMCOR & 0x000F);	
		
		//DCB2��]��Ԃ�ʒm
		Senddata[14] = valueascii(PORT3.PODR.BIT.B4);//��]���� CW/CCW
		Senddata[15] = valueascii(PORTF.PODR.BIT.B2);//START/STOP
		
		//DCB2��]���ʒm
		Senddata[16] = valueascii((GPT0.GTCCRA >> 12) & 0x000F);
		Senddata[17] = valueascii((GPT0.GTCCRA >> 8)  & 0x000F);
		Senddata[18] = valueascii((GPT0.GTCCRA >> 4)  & 0x000F);
		Senddata[19] = valueascii( GPT0.GTCCRA & 0x000F);
		
		Senddata[20] = 0x0d;
		//�f���~�^ CR
		
		R_PG_SCI_StartSending_C1(Senddata,21);
	}
	
	//IN2�R�}���h�F��Ԓʒm
	else if(!strncmp(cmd1,"IN2",3)){
		
		//�I�[�g���o�[�X�L��
		Senddata[0] = valueascii(autoreverseflg);
		
		//�I�[�g���o�[�X��]��
		Senddata[1] = valueascii((AreverseDA >> 8) & 0x000F);
		Senddata[2] = valueascii((AreverseDA >> 4) & 0x000F);
		Senddata[3] = valueascii( AreverseDA & 0x000F);
		
		//�I�[�g���o�[�X����
		Senddata[4] = valueascii((Areverselimit >> 8) & 0x000F);
		Senddata[5] = valueascii((Areverselimit >> 4) & 0x000F);
		Senddata[6] = valueascii( Areverselimit & 0x000F);
		
		//�I�[�g���o�[�X����
		Senddata[7] = valueascii((Areversetime >> 4) & 0x0F);
		Senddata[8] = valueascii( Areversetime & 0x0F);
		
		//DCB�C���^�[�o������L��
		Senddata[9] = valueascii(DCBintflg);
	
		//DCB�Ԍ��^�] �^�]����
		Senddata[10] = valueascii((Runtime >> 4) & 0x0F);
		Senddata[11] = valueascii( Runtime & 0x0F);
		
		//DCB�Ԍ��^�] ��~����
		Senddata[12] = valueascii((Stoptime >> 4) & 0x0F);
		Senddata[13] = valueascii( Stoptime & 0x0F);
		
		//DCB2�C���^�[�o������L��
		Senddata[14] = valueascii(DCB2intflg);
		
		//DCB2�Ԍ��^�] �^�]����
		Senddata[15] = valueascii((Runtime2 >> 4) & 0x0F);
		Senddata[16] = valueascii( Runtime2 & 0x0F);
		
		//DCB2�Ԍ��^�] ��~����
		Senddata[17] = valueascii((Stoptime2 >> 4) & 0x0F);
		Senddata[18] = valueascii( Stoptime2 & 0x0F);
		
		Senddata[19] = 0x0d;
		//�f���~�^ CR
		
		R_PG_SCI_StartSending_C1(Senddata,20);		
	}
	
	//ADS�R�}���h�FAD�f�[�^���M�v��
	else if(!strncmp(cmd1,"ADS",3)){
		//ADsendflg = true;
		//AD���M�t���O��true�ɐݒ�
		
		Senddata[0] = valueascii((ADval[1] >> 8) & 0x00F);
		Senddata[1] = valueascii((ADval[1] >> 4) & 0x00F);
		Senddata[2] = valueascii( ADval[1] & 0x00F); 
		
		Senddata[3] = valueascii((ADval[2] >> 8) & 0x00F);
		Senddata[4] = valueascii((ADval[2] >> 4) & 0x00F);
		Senddata[5] = valueascii( ADval[2] & 0x00F);
		
		Senddata[6] = valueascii(PORT0.PODR.BIT.B4);//�V�����b�_�[ CCW�o�͂����j�^
		
		Senddata[7] = 0x0d;
		//�f���~�^CR��t�^
		
		R_PG_SCI_StartSending_C1(Senddata,8);

	}
	
	//QQQ�R�}���h�FHigh�J�E���g����ʒm
	else if(!strncmp(cmd1,"QQQ",3)){
		Senddata[0] = valueascii((P26Highcnt >> 4) & 0x0F);
		Senddata[1] = valueascii( P26Highcnt & 0x0F);
		Senddata[2] = 0x0d;
		
		R_PG_SCI_StartSending_C1(Senddata,3);
	}
	
	//RPS�R�}���h�F�p���X�J�E���g�����M�v��
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
			//�p���X�J�E���g�l���A���t�@�x�b�g�ɕϊ����đ��M�f�[�^���쐬
			
			Senddata[3] = valueascii((plsrcnt >> 4) & 0x0F);
			Senddata[4] = valueascii( plsrcnt & 0x0F);
			//Senddata[3] = plsrcnt + 0x40;
			//�ώZ��
			
			Senddata[5] = 0x0d;
			//�f���~�^CR��t�^
			
			R_PG_SCI_StartSending_C1(Senddata,6);
		}
		
	}
	
	

	//���Ή��R�}���h�̏ꍇ�G���[
	else{
		returncmd(1);
	}
	
	//�f���~�^�i�[�ϐ���������
	delim=0x00;
		
}

//CMT���荞��
void Cmt0IntFunc(void)
{
	R_PG_ADC_12_StartConversion_S12AD0();
	//CMT���荞�݂�AD�ϊ��J�n
	
	if(DCBstartflg && DCBintflg){
	//DCB�^�]���ߒ����Ԍ��^�]���̎��ɃJ�E���g
		if(DCBrunflg){
		//DCB���^�]��
			if(DCBruncnt < Runtime){
			//Runtime�܂ŃJ�E���g
				DCBruncnt = DCBruncnt + 1;
			}else{
			//Runtime�J�E���g������
				DCBruncnt = 0;
				DCBrunflg = false;
				R_PG_IO_PORT_Write_PF3(0x01);
				//DCB�^�]��~
			}
		}else{
		//DCB��~��
			if(DCBruncnt < Stoptime){
			//Stoptime�܂ŃJ�E���g
				DCBruncnt = DCBruncnt + 1;
			}else{
			//Stoptime�J�E���g������
				DCBruncnt = 0;
				DCBrunflg = true;
				R_PG_IO_PORT_Write_PF3(0x00);
				//DCB�^�]�ĊJ
			}
		}
	}

					
	if(DCB2startflg && DCB2intflg){
	//DCB2�^�]���ߒ����Ԍ��^�]��
		if(DCB2runflg){
		//DCB2���^�]��
			if(DCB2runcnt < Runtime2){
			//Runtime�܂ŃJ�E���g
				DCB2runcnt = DCB2runcnt + 1;
			}else{
			//Runtime�J�E���g������
				DCB2runcnt = 0;
				DCB2runflg = false;
				R_PG_IO_PORT_Write_PF2(0x01);
				//DCB2�^�]��~
			}
		}else{
		//DCB��~��
			if(DCB2runcnt < Stoptime2){
			//Stoptime�܂ŃJ�E���g
				DCB2runcnt = DCB2runcnt + 1;
			}else{
			//Stoptime�J�E���g������
				DCB2runcnt = 0;
				DCB2runflg = true;
				R_PG_IO_PORT_Write_PF2(0x00);
				//DCB�^�]�ĊJ
			}
		}
	}

	if(ARwaitflg){
	//�I�[�g���o�[�X����܂őҋ@
		if(ARtimecnt < ARwaittime){
		//�K�莞�Ԃ܂ŃJ�E���g���p��
			ARtimecnt = ARtimecnt + 1;
		}else{
		//�K�莞�Ԍo�ߌ�
			
			R_PG_DAC_ControlOutput_C0(AreverseDA);
			//�t��]���̉�]�����C���v�b�g
			R_PG_IO_PORT_Write_PD2(0x01);
			//CW��]�J�n
			ARtimecnt = 0;
			//�J�E���g���N���A
			
			ARwaitflg = false;
			ARstartflg = true;
		}
	}
	
	
	
	if(ARstartflg){
		if(ARtimecnt < Areversetime){
		//Areversetime�܂ŃJ�E���g
			ARtimecnt = ARtimecnt + 1;
		}else{
		//Areversetime�܂ŃJ�E���g������
			ARtimecnt = 0;
			//�J�E���g���Z�b�g
			R_PG_IO_PORT_Write_PD2(0x00);
			//�V���b���b�_�[�����~
			R_PG_DAC_ControlOutput_C0(DAset);
			//�V�����b�_�[��]����߂�
			ARstartflg = false;
		}
	}
	
	//�C���^�[���b�N����
	//5��A����v�Őݒ胊�Z�b�g
	if(PORT2.PIDR.BIT.B6 == 0){
	//P26 = Low�̎��A�J�E���g�����Z�b�g
		P26HighcntC = 0;
		if(!(P26HighcntC == 0)){
			P26HighcntL = P26HighcntL + 1;
		}
	}else{
		//3��A��High���o�܂ŃJ�E���g
		if(P26HighcntC < 3){
			P26HighcntC = P26HighcntC + 1;
			P26HighcntL = P26HighcntL + 1;
		//3��A����v��A�����~
		}else{
			//�V�����b�_�[�����~
			R_PG_IO_PORT_Write_PD2(0x00);
			R_PG_IO_PORT_Write_P04(0x00);
			ARwaitflg = false;
			//�������[���[��~
			R_PG_IO_PORT_Write_PF3(0x01);
			DCBstartflg = false;
			//�s�b�N���[���[��~
			R_PG_IO_PORT_Write_PF2(0x01);
			DCB2startflg = false;
			P26HighcntC = 0;
		}
		P26Highcnt = P26Highcnt + 1;
	}
	
	LED0 = LED0 ^ 0x01;
	
	R_PG_IO_PORT_Write_P71(LED0);
	
}

//AD�ϊ��������荞��
void S12ad0AIntFunc(void)
{
	R_PG_ADC_12_GetResult_S12AD0(ADval);
	//AD�ϊ��̌��ʂ�ADval�Ɋi�[
	//ADval[0]:�ϒ�R�o��
	//ADval[1]:�O������0-10V
	//ADval[2]:�O������4-20mA
	
	if(autoreverseflg){
	//�I�[�g���o�[�X����ݒ�
		if(ADval[2] > Areverselimit){
		//�g���N�l������l���I�[�o�[
			R_PG_IO_PORT_Write_PD2(0x00);
			R_PG_IO_PORT_Write_P04(0x00);
			//�V�����b�_�[��~
			R_PG_IO_PORT_Write_PF2(0x01);
			R_PG_IO_PORT_Write_PF3(0x01);
			//�������[����~
			
			ARwaitflg = true;
			//�I�[�g���o�[�X���쒆�t���O��ݒ�
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
		//AD1(0-10V)���A���t�@�x�b�g�ɕϊ����đ��M�f�[�^���쐬

		Senddata[3] = valueascii((ADval[2] >> 8) & 0x00F);
		Senddata[4] = valueascii((ADval[2] >> 4) & 0x00F);
		Senddata[5] = valueascii( ADval[2] & 0x00F); 

		Senddata[3] = ((ADval[2] >> 8) & 0x000F) + 0x40;
		Senddata[4] = ((ADval[2] >> 4) & 0x000F) + 0x40;
		Senddata[5] = ( ADval[2] & 0x000F) + 0x40;
		//AD2(4-20mA)���A���t�@�x�b�g�ɕϊ����đ��M�f�[�^���쐬	
		
		Senddata[6] = valueascii(k);
		//��蓦�����񐔂𑗐M
		
		
		Senddata[7] = 0x0d;
		//�f���~�^CR��t�^
		
		R_PG_SCI_StartSending_C1(Senddata,8);
		
		k = 0;
		ADsendflg = false;
		//�t���O�����Z�b�g
	}
	else{
		k = k + 1;
	}
	*/
	
}


//MTU3�C���v�b�g�L���v�`�����荞��
void Mtu3IcCmCIntFunc(void){
	
	R_PG_Timer_GetTGR_MTU_U0_C3(0,0,& pulcnt,0,0,0);
	//TGRC�̒l��pulcnt�֊i�[
	
	cntbuf = cntbuf + pulcnt;
	//cntbuf�ɒl��ώZ
	
	if(cntbuf < 5){
	//���]���̎��A���萸�x���グ�邽�߁A�ώZ���s���B
			
		j = j + 1;
		//�ώZ�񐔂��L�^
		
	}
	else{
		
		plssend = cntbuf;
		plsrcnt = j;
		//���M�p�ϐ��ɒl����
		
		j = 1;
		cntbuf = 0;
		//�o�b�t�@��������
		
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
