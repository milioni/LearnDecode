/******************************************************************************
 *
 * THIS IS A FREE SOFTWARE THAT OPPENED FOR EDUCATION, RESEARCH AND COMMERCIAL
 * DEVELOPMENTS UNDER LICENSE POLICY OF FOLLOWING TERMS.
 *
 * Copyright (C) 2019 Thiago Milioni <thiago.milioni@hotmail.com>
 * all righ reserved.
 *
 * No restriction on use. You can use, modify and redistribute it for personal,
 * non-profit or commercial products UNDER YOUR RESPONSIBILITY.
 * 
 * IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Redistributions of source code must retain the above copyright notice.
 * 
 *****************************************************************************/

/******************************************************************************
 *                                  Includes
 *****************************************************************************/
#include <main.h>
#include <stdint.h>

/******************************************************************************
 *                               Private Defines
 *****************************************************************************/

/******************************************************************************
 *                            External declarations
 *****************************************************************************/

/******************************************************************************
 *                              Private Typedefs
 *****************************************************************************/

/******************************************************************************
 *                    Private global variable declarations
 *****************************************************************************/
unsigned uint8_t isr;
unsigned uint8_t tmo;

/******************************************************************************
 *                        Private function prototypes
 *****************************************************************************/

/*
          PREAMBLE                          Valid tranmission
   |¯¯¯|   |¯¯¯|   |¯¯¯|   |¯¯¯|XXX|   |¯¯¯|XXX|   |¯¯¯|XXX|   |¯¯¯|XXX|   |¯¯¯  / / ¯¯|XXX|   |¯¯¯|XXX|  
___|   |___|   |___|   |___|   |XXX|___|   |XXX|___|   |XXX|___|   |XXX|___|    / /    |XXX|___|   |XXX|___
   ^ 1 2 3 X 1 2 3 ^ 1 2 3 ^ 1 2 3 4 5 ^ 1 2 3 4 5 ^ 1 2 3 4 5 ^ 1 2 3 4 5 ^ 1        2 3 4 5 ^ 1 2 3 4 5 ^
                               BIT1        BIT2        BIT3        BIT4                BITN-1       BITN

   ^ Trugguer External Interrupt
   1  Level H
   2  Border1
   3  Bit Capture
   4  Border 2
   5  Level 2
   6  Wait Trigger
   7  Timeout
*/
void main()
{
   STT state = STT_TM;
   uint8_t data;
   uint8_t buffer[8];
   uint8_t pos;
   port_A_pullups(0x04);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      //524 ms overflow

   enable_interrupts(INT_EXT);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);

   while(TRUE)
   {
      loop();
   }
}

/* Loop Function */
void loop(void)
{
  if( isr )
  { // limpa flag de interrupcao
    isr = false;

    // reseta timeout
    set_timer0(0);

    // avanca maquina de estado
    switch( state )
    { 
      case STT_HI:
        state = ( input_state(PIN_A2) == true ) ? STT_HI : STT_TM;
        break;
      
      case STT_BC:
        data = input_state(PIN_A2);
        break;
      
      case STT_LO:
        state = ( input_state(PIN_A2) == false ) ? STT_WT : STT_TM;
        break;
      
      case STT_B1:
      case STT_B2:
        state = state + 1;
        break;
      
      case STT_WT:
        buffer[pos] = data;
        pos++;
        state = STT_HI;
        break;
      
      case STT_TM:
        pos = 0;
        state = STT_HI;
        break;
    }
  }
  else if(tmo)
  { tmo = false;
    state = STT_TM;
  }
}

#INT_EXT
void  EXT_isr(void) 
{ // seta flag que identificou nova borda de subida do sinal RF
  isr = true;
}

#INT_TIMER1
void  TIMER1_isr(void) 
{ // Timeout da recepcao
  tmo = true;
}