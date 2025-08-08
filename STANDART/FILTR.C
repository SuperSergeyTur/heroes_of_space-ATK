// Фильтр низких частот с постоянной времени, задаваемой
// уставкой в диапазоне 0.0005...12.0сек ( _fSec(...) ).
// Вычисление производится по формуле, взятой из Ultralogik'a:
// out = { (inp - out) * (Ттек - Тпред) } / { tau + (Ттек - Тпред) } + out
// Время выполнения:
//                   NXP double:         7...10 мкс
//                   NXP FPU float:      3...6 мкс
//                   Fujitsu 591 double: 450...550 мкс
//                   Fujitsu 591 float:  160...190 мкс

void FiltrLowFreq( struct fil *ft )
{
    word ax, bx;

    do { ax = Timer1_Ovr, bx = timer1; } while ( ax != Timer1_Ovr );
    ax <<= 8;           // Из четырехбайтного полного значения времени
    ax += ( bx >> 8 );  // для работы берутся средние два байта прини-
                        // мающие значения в диапазоне 0.25мсек-12.0сек.

    if( ft->first == 0 || *ft->tau == 0 )
    {
        ft->first = 1;
        ft->time = ax;
        ft->out = *ft->in;
        ft->d_out = (double)(slw)(sw)ft->out;
        return;
    }

    bx = ax - ft->time;
    if( bx == 0 ) return;
    ft->time = ax;

    if( *ft->in == ft->out )
    {
        ft->d_out = (double)(slw)(sw)ft->out;
    }
    else
    {
        ft->d_out += ((double)(slw)(sw)*ft->in - (double)(slw)(sw)ft->out) * (double)(w)bx / (double)(w)(*ft->tau + bx);
        ft->out = (w)ft->d_out;
    }

    return;
}
