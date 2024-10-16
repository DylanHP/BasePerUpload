#ifndef ATmega
#define ATmega

// manipolazione registri
struct port_reg {
  uint8_t b0 : 1;
  uint8_t b1 : 1;
  uint8_t b2 : 1;
  uint8_t b3 : 1;
  uint8_t b4 : 1;
  uint8_t b5 : 1;
  uint8_t b6 : 1;
  uint8_t b7 : 1;
};

// definizione porte
#define DDPA (*((volatile struct port_reg *)0x0400))  // PORTA_DIR
#define DDPB (*((volatile struct port_reg *)0x0420))  // PORTB_DIR
#define DDPC (*((volatile struct port_reg *)0x0440))  // PORTC_DIR
#define DDPD (*((volatile struct port_reg *)0x0460))  // PORTD_DIR
#define DDPE (*((volatile struct port_reg *)0x0480))  // PORTE_DIR
#define DDPF (*((volatile struct port_reg *)0x04A0))  // PORTE_DIR

// pilotaggio porte
#define SPA (*((volatile struct port_reg *)0x0404))  // PORTA_OUT
#define SPB (*((volatile struct port_reg *)0x0424))  // PORTB_OUT
#define SPC (*((volatile struct port_reg *)0x0444))  // PORTC_OUT
#define SPD (*((volatile struct port_reg *)0x0464))  // PORTD_OUT
#define SPE (*((volatile struct port_reg *)0x0484))  // PORTE_OUT
#define SPF (*((volatile struct port_reg *)0x04A4))  // PORTE_OUT

// lettura porte
#define GPA (*((volatile struct port_reg *)0x0408))  // PORTA_IN
#define GPB (*((volatile struct port_reg *)0x0428))  // PORTB_IN
#define GPC (*((volatile struct port_reg *)0x0448))  // PORTC_IN
#define GPD (*((volatile struct port_reg *)0x0468))  // PORTD_IN
#define GPE (*((volatile struct port_reg *)0x0488))  // PORTE_IN
#define GPF (*((volatile struct port_reg *)0x04A8))  // PORTE_IN



void initCPU() {
  int64_t cpu_freq;
#if (F_CPU == 20000000)
  cpu_freq = 20000000;
  /* No division on clock */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0x00);
#elif (F_CPU == 16000000)
  cpu_freq = 16000000;
  /* No division on clock */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0x00);
#elif (F_CPU == 8000000)
  cpu_freq = 8000000;
  /* Clock DIV2 */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_2X_gc));
#elif (F_CPU == 4000000)
  cpu_freq = 4000000;
  /* Clock DIV4 */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_4X_gc));
#elif (F_CPU == 2000000)
  cpu_freq = 2000000;
  /* Clock DIV8 */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_8X_gc));
#else

#ifndef F_CPU
#warning "F_CPU not defined"
#define F_CPU 16000000
#endif

#warning "F_CPU defined as an invalid value - may cause undefined behavior"
  /* Default value is 16MHz */
  cpu_freq = 16000000;
  /* No division on clock */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0x00);
#endif
  /* Apply calculated value to F_CPU_CORRECTED */
  // F_CPU_CORRECTED = (uint32_t)cpu_freq;
}

#endif
