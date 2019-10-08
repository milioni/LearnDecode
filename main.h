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

#ifndef __MAIN_H__
#define __MAIN_H__

/******************************************************************************
 *                              Extern Libraries
 *****************************************************************************/
#include <12F675.h>

/******************************************************************************
 *                                Macro Defines
 *****************************************************************************/
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer

#use delay(internal=4MHz)
#use FIXED_IO( A_outputs=PIN_A0 )

/******************************************************************************
 *                            External declarations
 *****************************************************************************/

/******************************************************************************
 *                                  Typedefs
 *****************************************************************************/
typedef enum STT
{
  STT_HI,
  STT_B1,
  STT_BC,
  STT_B2,
  STT_LO,
  STT_WT,
  STT_TM
};

/******************************************************************************
 *                        Global variable declarations
 *****************************************************************************/

/******************************************************************************
 *                             Function prototypes
 *****************************************************************************/
void loop(void);
void EXT_isr(void);
void TIMER1_isr(void);

/******************************************************************************
 *                                End of File
 ******************************************************************************/
#endif