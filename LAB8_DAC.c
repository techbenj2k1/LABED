//#include <avr/io.h>
//#include <avr/interrupt.h>
int ms=0, l, h, poz=0, value,i=0;
unsigned int sin20[] = {127,166,202,230,248,254,248,230,202,166,127,88,52,24,6,0,6,24,52,88};

void display(char p, char c)
{
 PORTA &= 0b11110000;
 PORTC &= 0b00000000;

  switch(c){
     case 0: PORTC|=0b00111111; break;
     case 1: PORTC|=0b00000110; break;
     case 2: PORTC|=0b01011011; break;
     case 3: PORTC|=0b01001111; break;
     case 4: PORTC|=0b01100110; break;
     case 5: PORTC|=0b01101101; break;
     case 6: PORTC|=0b01111101; break;
     case 7: PORTC|=0b00000111; break;
     case 8: PORTC|=0b01111111; break;
     case 9: PORTC|=0b01101111; break;
  }
  switch(p){
      case 1: PORTA|=0b00000001; break;
      case 2: PORTA|=0b00000010; break;
      case 3: PORTA|=0b00000100; break;
      case 4: PORTA|=0b00001000; break;
  }
  // Delay_ms(1); // #include <util/delay.h>
}

void init_adc()
{
  ADMUX = 0b01000000;
  ADCSRA= 0b10000111;
}

int readADC(char ch)
{
  ADMUX &= 0b11100000;
  ADMUX |= ch;
  ADCSRA|=(1<<6);
    while(ADCSRA&(1<<6));
  l = ADCL;
  h = ADCH;
  return h << 8 | l;
}


void init_timer()
{
        TCCR0 = 0b00001011;
        TCNT0 = 0;
        OCR0  = 124;
        TIMSK|= 0b00000010;  //activeaza intreruperea de Output Compare Match (comparare la iesire)
}


void init_PWM(){
  DDRD |=1<<7;        //PD7 - output
  TCCR2 = 0b01101001;
  OCR2 = 128;                 //factor de umplere 50%
}

//ISR
void ISR_Timer0() iv IVT_ADDR_TIMER0_COMP ics ICS_AUTO {

                if (ms>=0){

                   OCR2 = sin20[i++];
                   if(i == 20)
                        i=0;
                   ms=0;
                }
                else ms++;
}

void main(){
  DDRA = 0b00001111;  //seteaza pinii de iesire
  DDRC = 0b01111111;

 // init_adc();
  init_timer();
  init_PWM();
  SREG |= 1<<7;            //set enable interrupt - activeaza intreruperile

    for(;;){
    }
}

