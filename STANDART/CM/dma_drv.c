      //   ��������� ��������� ������ DMA ��� �����
      //  �������������.
word init_syn_dma( void )
{
  word i;
    DMA_Synh[0].req.src = _DMA0_ExtINT ;
    DMA_Synh[1].req.src = _DMA1_ExtINT ;
    DMA_Synh[2].req.src = _DMA2_ExtINT ;
    DMA_Synh[3].req.src = _DMA3_ExtINT ;
    DMA_Synh[4].req.src = _DMA4_ExtINT ;

  for ( i=0;i<5;++i)
  {
    DMA_Synh[i].dest = timer1 ;
    DMA_Synh[i].req.level = Int_Falling ;
    ExtInt_DMA_ini(DMA_Synh[i] );

  }
    DMA_start( DMA_Synh) ;

  return 0 ;
}

void ExtInt_DMA_ini(struct DMA_Syn in )
{

/*   switch (in.req.src )
   {
    case _DMA_ExtINT0:
                        ENIR_EN0 = 0;
                        ICR00 = 31;
                        ELVR_LAB0 = in.req.level;
                        EIRR_ER0 = 0;
                        ENIR_EN0 = 1;
                        break;
    case _DMA_ExtINT1:
                        ENIR_EN1 = 0;
                        ICR01 = 31;
                        ELVR_LAB1 = in.req.level;
                        EIRR_ER1 = 0;
                        ENIR_EN1 = 1;
                        break;
    case _DMA_ExtINT2:

                        ENIR_EN2 = 0;
                        ICR02 = 31;
                        ELVR_LAB2 = in.req.level;
                        EIRR_ER2 = 0;
                        ENIR_EN2 = 1;
                        break;
    case _DMA_ExtINT3:

                        ENIR_EN3 = 0;
                        ICR03 = 31;
                        ELVR_LAB3 = in.req.level;
                        EIRR_ER3 = 0;
                        ENIR_EN3 = 1;
                        break;
    default:
                        break;
   //   ��������� INT� � DMA �� ��������.
   //
   }*/
}
//��������� ������� DMA � ����������� �� �������� �������
void DMA_start(struct DMA_Syn* in )
{
/*  lword lax;
  //��������� ���������� �������.

 HRCL   = 0;
 DMACR  = 0;
 #ifdef _DMA0_Synh

    DMACB0 = 0x04800000u;   // ����� ��������: ������������ �������� � �������� 16-�� ����.�����
    DMASA0 = (lw)(&timer1);  // ����� ���������
    DMADA0 = (lw)(&in[0].dest);  // ����� ��������..

 #endif
 #ifdef _DMA1_Synh

    DMACB1 = 0x04800000u;   // ����� ��������: ������������ �������� � �������� 16-�� ����.�����
    DMASA1 = (lw)(&timer1);  // ����� ���������
    DMADA1 = (lw)(&in[1].dest);  // ����� ��������..

 #endif
 #ifdef _DMA2_Synh

    DMACB2 = 0x04800000u;   // ����� ��������: ������������ �������� � �������� 16-�� ����.�����
    DMASA2 = (lw)(&timer1);  // ����� ���������
    DMADA2 = (lw)(&in[2].dest);  // ����� ��������..

 #endif
 #ifdef _DMA3_Synh

    DMACB3 = 0x04800000u;   // ����� ��������: ������������ �������� � �������� 16-�� ����.�����
    DMASA3 = (lw)(&timer1);  // ����� ���������
    DMADA3 = (lw)(&in[3].dest);  // ����� ��������..

 #endif

 #ifdef _DMA4_Synh

    DMACB4 = 0x04800000u;   // ����� ��������: ������������ �������� � �������� 16-�� ����.�����
    DMASA4 = (lw)(&timer1);  // ����� ���������
    DMADA4 = (lw)(&in[4].dest);  // ����� ��������..

 #endif
    DMACR  = 0x80;
    lax = 0x8011ffffu ; //�������� ������� �������� ������ 24-28
#ifdef _DMA0_Synh

    DMACA0 = lax | ((lw)in[0].req.src)<<24;
#endif

#ifdef _DMA1_Synh

    DMACA1 = lax | ((lw)in[1].req.src)<<24;
#endif
#ifdef _DMA2_Synh

    DMACA2 = lax | ((lw)in[2].req.src)<<24;
#endif
#ifdef _DMA3_Synh

    DMACA3 = lax | ((lw)in[3].req.src)<<24;
#endif
#ifdef _DMA4_Synh

    DMACA4 = lax | ((lw)in[4].req.src)<<24;
#endif
  */
}


