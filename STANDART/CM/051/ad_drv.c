
//  ��������� ������� ��� �� ���������.
//  �.�. ����� �������������� ��� ����� 6����� �� ����������
//  �� ���������� ��� � ����������� ������� ��� ��������� ���������
//  �� �����������������.
//--------------------------------------------------------

//  ��������� ������������� ��� ��� ��� ���������� � ������� ��� ����������.
void Start_AD( void )
{
    lword adc_clk;

	LPC_SC->PCONP |= CLKPWR_PCONP_PCADC;

	LPC_ADC->CNR = 0;
    // �������� ���
    adc_clk =  PeripheralClock / _ADC_CLK - 1;
    LPC_ADC->CNR = ( ADC_CR_CLKDIV( adc_clk ) ) | ADC_CR_PDN;

	// ��������� ����� AN0
    LPC_ADC->CNR |= ADC_CR_CH_SEL( 0 );

    //LPC_ADC->CNR |= 0x3b | ADC_CR_BURST;

    return;
}


//----------------------------------------------
//     �.�. ����� �������������� ��� ����� 6����� �� ����������
//  �� ���������� ��� � ����������� ������� ��� ��������� ���������
//  �� �����������������, �� ������������ ��������� ����� ��� �������������
//  � ����������� MCS196.

/* struct Channel_AD ach - ��� ��������� ������ ��� ������ ��� �� ��������
 *              ������������ ���������; �� ���� ��������� ������ ��������
 *              ����������� ����� ��� ��������������� ������� ������.
 * word* AddrResult - ����� ������ � ������� ������� ��������� ���������
 *                    ����� ���������.
 */

static __INLINE void mAD_Izm( struct Channel_AD ach, word* AddrResult )
{
    slword ax;
    volatile lword lax;

    __disable_interrupt();
    tx = timer1;

    LPC_ADC->CNR &= ~( 0x000000FF | ADC_CR_START_NOW );
    LPC_ADC->CNR |= ( ADC_CR_CH_SEL( ( ach.mux & 0x0f ) ) | ADC_CR_START_NOW );
    lax = LPC_ADC->GDR;
    ax = timer1;
    while( ( lax & ADC_GDR_DONE_FLAG ) == 0 )
    {
        if( (u)((w)( timer1 - ax ) ) >= _MkSec( 10 ) )
        {
            ax = timer1;
            LPC_ADC->CNR &= ~( 0x000000FF | ADC_CR_START_NOW );
            LPC_ADC->CNR |= ( ADC_CR_CH_SEL( ( ach.mux & 0x0f ) ) | ADC_CR_START_NOW );
        }
        lax = LPC_ADC->GDR;
    };
    *AddrResult = ADC_GDR_RESULT( LPC_ADC->DR[ ach.mux & 0x0f ] );


    //lax = LPC_ADC->DR[ ach.mux & 0x0f ];
    //if( ( lax & ADC_GDR_DONE_FLAG ) != 0 )
    //while( ( LPC_ADC->DR[ ach.mux & 0x0f ] & ADC_GDR_DONE_FLAG ) != 0 )
    //{
    //    *AddrResult = (w)(( LPC_ADC->DR[ ach.mux & 0x0f ] >> 4 ) & 0xFFF);
    //}

    dtizm = timer1 - tx;
    __enable_interrupt();


    return;
}

/*   ������� ��� ������� ��������� - ���������� ������ ���� �����������
 * ������ - ��-�� ���� ����� �� ���������� ������, ��� �������, �� �������
 * ������ ��� �� ������������� ������
 *   �� ����� ����� ������������ � ���������� �� �������������� �� �������.
 */
void AD_Izm( struct Channel_AD ach, word* AddrResult )
{
    mAD_Izm( ach, AddrResult );
    return;
}
