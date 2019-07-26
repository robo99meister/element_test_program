//�|�[�g�����ݒ�

void initial_port(void);

void initial_port(void)
{
	//IO�|�[�g�����ݒ�
	//P0~
	R_PG_IO_PORT_Set_P00();//SW4_2 pull-up
	R_PG_IO_PORT_Set_P01();//RDn ���g�p ���� pull-up
	R_PG_IO_PORT_Set_P02();//TXD2 ���g�p �o��L
	R_PG_IO_PORT_SetOpenDrain_P02();//���[�h�Z��2,DZ�o�� �I�[�v���h���C��
	R_PG_IO_PORT_Write_P02(0x01);//�C�j�V����Open
	R_PG_IO_PORT_Set_P03();//RXD2 ���g�p �o��L
	R_PG_IO_PORT_SetOpenDrain_P03();//���[�h�Z��2,HOLD�o�� �I�[�v���h���C��
	R_PG_IO_PORT_Write_P03(0x01);//�C�j�V���� Open
	R_PG_IO_PORT_Set_P04();//IO4 ���g�p �o��L //�C���o�[�^��] CCW�^�]�E��~
	R_PG_IO_PORT_Write_P04(0X00);//�C�j�V������~
	R_PG_IO_PORT_Set_P05();//CS2n_WAITn ���g�p ���� pull-up
	
	//P1~
	R_PG_IO_PORT_Set_P10();//SW1 ���荞�݂Ŏg�p pull-up
	R_PG_IO_PORT_Set_P11();//SW2 ���荞�݂Ŏg�p pull-up
	R_PG_IO_PORT_Set_P12();//CANSTB 100k�� pull-down
	R_PG_IO_PORT_Set_P13();//USB0VBUSENN 4.7k�� pull-down
	R_PG_IO_PORT_Set_P14();//SCK2 ���g�p �o��L
	R_PG_IO_PORT_Write_P14(0x00);
	
	//P2~
	R_PG_IO_PORT_Set_P20();//MTCLKB ���g�p �o��L
	R_PG_IO_PORT_Write_P20(0x00);
	R_PG_IO_PORT_Set_P21();//MTCLKA ���g�p �o��L
	R_PG_IO_PORT_Write_P21(0x00);
	R_PG_IO_PORT_Set_P22();//CRX1 CAN�g�����V�[�o�o�͂Ɛڑ� ���̓|�[�g
	R_PG_IO_PORT_Set_P23();//CTX1 CAN�g�����V�[�o���͂Ɛڑ� �o��L
	R_PG_IO_PORT_Write_P23(0x00);
	R_PG_IO_PORT_Set_P24();//D11 ���g�p �o��L
	R_PG_IO_PORT_Write_P24(0x00);
	R_PG_IO_PORT_Set_P25();//SCL1 �\���m�C�h2�쓮 
	R_PG_IO_PORT_Write_P25(0x00);//�C�j�V����L(OFF)
	R_PG_IO_PORT_Set_P26();//SDA1 ���g�p pull-up
	R_PG_IO_PORT_SetOpenDrain_P26();//���[�h�Z�� DZ�o�� �I�[�v���h���C��
	R_PG_IO_PORT_Write_P26(0x01);//�C�j�V���� open
	
	//P3~
	R_PG_IO_PORT_Set_P30();//MTCLKD ���g�p �o��L
	R_PG_IO_PORT_Write_P30(0x00);
	R_PG_IO_PORT_Set_P31();//MTCLKC ���g�p �o��L
	R_PG_IO_PORT_Write_P31(0x00);
	R_PG_IO_PORT_Set_P32();//MTIO3C ���g�p �o��L
	R_PG_IO_PORT_Write_P32(0x00);
	R_PG_IO_PORT_Set_P33();//MTIO3A LED3 L�Ŕ���
	R_PG_IO_PORT_Write_P33(0x01);
	R_PG_IO_PORT_Set_P34();//IO7 ���g�p �o��L
	R_PG_IO_PORT_SetOpenDrain_P34();//DC�u���V���X2 CW/CCW����o��
	R_PG_IO_PORT_Write_P34(0x01);//�C�j�V����CCW����
	R_PG_IO_PORT_Set_P35();//CANEN CAN���g�p pull-up �o��L
	R_PG_IO_PORT_Write_P35(0x00);
	
	//P4~
	//R_PG_IO_PORT_Set_P40();//AN000 �ϒ�R�ɐڑ�
	//R_PG_IO_PORT_Set_P41();//AN001 �T�[�{���[�^�̃t�B�[�h�o�b�N�ɐڑ�
	//R_PG_IO_PORT_Set_P42();//AN002 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P43();//AN003 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P44();//AN100 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P45();//AN101 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P46();//AN102 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P47();//AN103 ���g�p �o�̓|�[�g�ɐݒ�s��
	
	//P5~
	//R_PG_IO_PORT_Set_P50();//P50 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P51();//P51 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P52();//A7 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P53();//A6 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P54();//DA0 DA�ϊ��|�[�g�Ŏg�p
	//R_PG_IO_PORT_Set_P55();//DA1 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P56();//P56 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P57();//P57 ���g�p �o�̓|�[�g�ɐݒ�s��
	
	//P6~
	//R_PG_IO_PORT_Set_P60();//A5 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P61();//A4 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P62();//A3 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P63();//A2 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P64();//A1 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_P65();//A0 ���g�p �o�̓|�[�g�ɐݒ�s��
	
	//P7~
	R_PG_IO_PORT_Set_P70();//POE0n ���g�p 100k�� pull-up
	R_PG_IO_PORT_Set_P71();//LED0 �o��L�Ŕ���
	R_PG_IO_PORT_Write_P71(0x01);
	R_PG_IO_PORT_Set_P72();//MTIOC4A�Ŏg�p LED1�o�� L�Ŕ���
	R_PG_IO_PORT_Write_P72(0x01);
	R_PG_IO_PORT_Set_P73();//LED2�o�� L�Ŕ���
	R_PG_IO_PORT_Write_P73(0x01);
	R_PG_IO_PORT_Set_P74();//D2_MTIOC3D ���g�p �o��L
	R_PG_IO_PORT_Write_P74(0x00);
	R_PG_IO_PORT_Set_P75();//D1_MTIOC4C ���g�p �o��L
	R_PG_IO_PORT_Write_P75(0x00);
	R_PG_IO_PORT_Set_P76();//D0_MTIOC4D ���g�p �o��L
	R_PG_IO_PORT_Write_P76(0x00);
	
	//P8~
	R_PG_IO_PORT_Set_P80();//A9_MTIC5W ���g�p �o��L
	R_PG_IO_PORT_Write_P80(0x00);
	R_PG_IO_PORT_Set_P81();//A8_MTIC5V ���g�p �o��L
	R_PG_IO_PORT_Write_P81(0x00);
	R_PG_IO_PORT_Set_P82();//MTIC5U ���g�p �o��L
	R_PG_IO_PORT_Write_P82(0x00);
	
	//P9~
	R_PG_IO_PORT_Set_P90();//MTIOC7D ���g�p �o��L
	R_PG_IO_PORT_Write_P90(0x00);
	R_PG_IO_PORT_Set_P91();//MTIOC7C ���g�p �o��L
	R_PG_IO_PORT_Write_P91(0x00);
	R_PG_IO_PORT_Set_P92();//MTIOC6D ���g�p �o��L
	R_PG_IO_PORT_Write_P92(0x00);
	R_PG_IO_PORT_Set_P93();//MTIOC7B ���g�p �o��L
	R_PG_IO_PORT_Write_P93(0x00);
	R_PG_IO_PORT_Set_P94();//MTIOC7A ���g�p �o��L
	R_PG_IO_PORT_Write_P94(0x00);
	R_PG_IO_PORT_Set_P95();//MTIOC6B ���g�p �o��L
	R_PG_IO_PORT_Write_P95(0x00);
	R_PG_IO_PORT_Set_P96();//POE4n 100k�� pull-up
	
	//PA~
	R_PG_IO_PORT_Set_PA0();//MTIOC6C ���g�p �o��L
	R_PG_IO_PORT_Write_PA0(0x00);
	R_PG_IO_PORT_Set_PA1();//MTIOC6A ���g�p �o��L
	R_PG_IO_PORT_Write_PA1(0x00);
	R_PG_IO_PORT_Set_PA2();//IO5
	R_PG_IO_PORT_SetOpenDrain_PA2();//DC�u���V���X CW/CCW�؂�ւ�
	R_PG_IO_PORT_Write_PA2(0x01);//�C�j�V���� Lo(CCW����)
	R_PG_IO_PORT_Set_PA3();//MTIOC2A ���g�p �o��L
	R_PG_IO_PORT_Write_PA3(0x00);
	R_PG_IO_PORT_Set_PA4();//ADTRG0n 100k�� pull-up
	R_PG_IO_PORT_SetOpenDrain_PA4();//���[�h�Z�� HOLD�o�� �I�[�v���h���C��
	R_PG_IO_PORT_Write_PA4(0x01);//�C�j�V���� open
	R_PG_IO_PORT_Set_PA5();//ADTRG1n 100k�� pull-up
	R_PG_IO_PORT_Set_PA6();//IO6 ���g�p �o��L
	R_PG_IO_PORT_Write_PA6(0x00);
	
	//PB~
	R_PG_IO_PORT_Set_PB0();//A14 ���g�p �o��L
	R_PG_IO_PORT_Write_PB0(0x00);
	//R_PG_IO_PORT_Set_PB1();//RXD0 RS-485 ���[�h�Z���ʐM
	//R_PG_IO_PORT_Write_PB1(0x00);
	//R_PG_IO_PORT_Set_PB2();//TXD0 RS-485 ���[�h�Z���ʐM
	//R_PG_IO_PORT_Write_PB2(0x00);
	R_PG_IO_PORT_Set_PB3();//MTIOC0A ���g�p �o��L
	R_PG_IO_PORT_Write_PB3(0x00);
	R_PG_IO_PORT_Set_PB4();//���g�p �o��L
	R_PG_IO_PORT_Write_PB4(0x00);
	R_PG_IO_PORT_Set_PB5();//LINTXD ���g�p �o��L
	R_PG_IO_PORT_Write_PB5(0x00);	
	R_PG_IO_PORT_Set_PB6();//LINRXD 4.7k�� pull-up
	R_PG_IO_PORT_Set_PB7();//A19 ���g�p �o��L
	R_PG_IO_PORT_Write_PB7(0x00);	
	
	//PC~
	//R_PG_IO_PORT_Set_PC0();//PC0 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_PC1();//PC1 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_PC2();//PC2 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_PC3();//PC3 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_PC4();//PC4 ���g�p �o�̓|�[�g�ɐݒ�s��
	//R_PG_IO_PORT_Set_PC5();//CANENRRn ���g�p �o�̓|�[�g�ɐݒ�s��
	
	//PD~
	R_PG_IO_PORT_Set_PD0();//GTIOC3B ���g�p �o��L
	R_PG_IO_PORT_Write_PD0(0x00);
	R_PG_IO_PORT_Set_PD1();//GTIOC3A ���g�p �o��L
	R_PG_IO_PORT_Write_PD1(0x00);
	R_PG_IO_PORT_Set_PD2();//�C���o�[�^��] CW�^�]�E��~
	R_PG_IO_PORT_Write_PD2(0x00);//�C�j�V���� ��~
	//R_PG_IO_PORT_Set_PD3();//TXD1 RS232C TX
	R_PG_IO_PORT_Set_PD4();//SCK1 ���g�p �o��L
	R_PG_IO_PORT_Write_PD4(0x00);
	//R_PG_IO_PORT_Set_PD5();//RXD1 RS232C RX
	R_PG_IO_PORT_Set_PD6();//GTIOC0B ���g�p �o��L
	R_PG_IO_PORT_Write_PD6(0x00);
	//R_PG_IO_PORT_Set_PD7();//CTS0RTS0 ���g�p �o��L
	//R_PG_IO_PORT_Write_PD7(0x00);
	//GTIOC0A�Ƃ��Ďg�p
	
	//PE~
	R_PG_IO_PORT_Set_PE0();//WR1n 4.7k�� pull-up
	R_PG_IO_PORT_Set_PE1();//USB0OVRCURA 100k�� pull-up
	//R_PG_IO_PORT_Set_PE2();//NMI 4.7k�� pull-up �o�͐ݒ�s��
	R_PG_IO_PORT_Set_PE3();//IRQ2-DS SW3 SW-ON��L
	R_PG_IO_PORT_Set_PE4();//A10 ���g�p �o��L
	R_PG_IO_PORT_Write_PE4(0x00);
	R_PG_IO_PORT_Set_PE5();//USB0VBUS
	
	//PF~
	//R_PG_IO_PORT_Set_PF0();//TMS E1�p
	//R_PG_IO_PORT_Set_PF1();//TRST# E1�p
	R_PG_IO_PORT_Set_PF2();//IRQ5 100k�� pull-up
	R_PG_IO_PORT_SetOpenDrain_PF2();//DC�u���V���X2 START/STOP����p(�I�[�v���h���C��)
	R_PG_IO_PORT_Write_PF2(0x01);//�C�j�V���� STOP�ݒ�
	R_PG_IO_PORT_Set_PF3();//IO1 ���g�p �o��L 
	R_PG_IO_PORT_SetOpenDrain_PF3();//DC�u���V���X START/STOP����p(�I�[�v���h���C��)
	R_PG_IO_PORT_Write_PF3(0x01);//�C�j�V���� STOP�ݒ�
	R_PG_IO_PORT_Set_PF4();//IO0 �\���m�C�h1�쓮
	R_PG_IO_PORT_Write_PF4(0x00);//�C�j�V����L(OFF)
	
	
	//PG~
	R_PG_IO_PORT_Set_PG0();//DLCDD4 LCD�p
	R_PG_IO_PORT_Set_PG1();//DLCDD5 LCD�p
	R_PG_IO_PORT_Set_PG2();//DLCDD6 LCD�p
	R_PG_IO_PORT_Set_PG3();//DLCDD7 LCD�p
	R_PG_IO_PORT_Set_PG4();//DLCDRS LCD�p
	R_PG_IO_PORT_Set_PG5();//DLCDE LCD�p
	R_PG_IO_PORT_Set_PG6();//LINNSLP �o��L(LIN�X���[�v)
	R_PG_IO_PORT_Write_PG6(0x00);
}

//�V���A���C���^�[�t�F�[�X�����ݒ�

void initial_SCI(void);

void initial_SCI(void)
{
	//SCI0 ���[�h�Z���ʐM RS-485
	R_PG_SCI_Set_C0();
	//SCI1
	R_PG_SCI_Set_C1();//TRXD1, RS232�ʐM�p
}
	

//���荞�ݏ����ݒ�
/*
void initial_IRQ(void);

void initial_IRQ(void)
{
	//IRQ0 �����ݒ�
	R_PG_ExtInterrupt_Set_IRQ0();//pull-up �����茟�o �D��F10
	
	//IRQ1 �����ݒ�
	R_PG_ExtInterrupt_Set_IRQ1();//pull-up �����茟�o �D��F8
	
	//IRQ3 �����ݒ�
	R_PG_ExtInterrupt_Set_IRQ3();//pull-up Low���o �D��F2 �X�p�C�����̃A���[�����o�p
	
}
*/

//MTU�����ݒ�
/*
void initial_MTU(void);

void initial_MTU(void)
{
	
	R_PG_Timer_Set_MTU_U0_C3();//MTIO3�̐ݒ�
	R_PG_Timer_Set_MTU_U0_C4();//MTIO4�̐ݒ�
	
}
*/

	
//12bit A/D�ϊ������ݒ�
void initial_S12AD(void);

void initial_S12AD(void)
{
	R_PG_ADC_12_Set_S12AD0();//12bit AD�R���o�[�^�ݒ�
	//AD�ݒ�
	//�A���X�L�������[�h
	//AN000,AN001,AN002 �L��
	//AD�ϊ��I�����荞�ݗL��
	
}

//DA�ϊ��|�[�g�����ݒ�
void initial_DA(void);

void initial_DA(void)
{
	R_PG_DAC_Set_C0();//�X�e�[�W��]���w�ߏo��
	R_PG_DAC_Set_C1();//�X�p�C������]���w�ߏo��
	
	R_PG_DAC_SetWithInitialValue_C0(0x0000);
	R_PG_DAC_SetWithInitialValue_C1(0x0000);
}


//CMT�����ݒ�
void initial_CMT(void);

void initial_CMT(void)
{
	R_PG_Timer_Set_CMT_U0_C0();
	R_PG_Timer_Set_CMT_U0_C1();
}


