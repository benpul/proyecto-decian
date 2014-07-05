#include <16F877A.h>
#device adc=8
#fuses XT, NOWDT, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT,
#use delay(clock=4000000)

#include <math.h>

float voltajeFrontal,voltajeIzquierda,voltajeDerecha,distanciaFrontal,distanciaIzquierda,distanciaDerecha;
int sensorFrontal,sensorIzquierda,sensorDerecha;
float resolucion= 5/255; 



void giro_180(){
  setup_timer_2(T2_DIV_BY_1,249,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_PWM);
  set_pwm1_duty(70);
	set_pwm2_duty(30);
	delay_ms(500);
}

void giro_der90(){
  setup_timer_2(T2_DIV_BY_1,249,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_PWM);
  set_pwm1_duty(70);
	set_pwm2_duty(30);
	delay_ms(250);
}

void giro_izq90(){
	setup_timer_2(T2_DIV_BY_1,249,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_PWM);
  set_pwm1_duty(30);
	set_pwm2_duty(70);
	delay_ms(250);
}

void main(){
	set_tris_A(0x1F);
	set_tris_C(0x00);
	setup_adc(ADC_CLOCK_DIV_4);
	setup_adc_ports(3);
	while(1){
    //Modo, periodo y postscaler, para que funciones a 1 Hz
		setup_timer_2(T2_DIV_BY_1,249,1);
	  setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
		set_pwm1_duty(70);
    set_pwm2_duty(70);;
    //Se hace la conversión de los tres sensores
    set_adc_channel(0);
		delay_ms(1);
		sensorFrontal = read_adc();
		voltajeFrontal = sensorFrontal * resolucion;
    set_adc_channel(1);
	  delay_ms(1);
		sensorIzquierda = read_adc();
    voltajeIzquierda = sensorIzquierda * resolucion;
    set_adc_channel(2);
		delay_ms(1);
		sensorDerecha = read_adc();
		voltajeDerecha = sensorDerecha * resolucion;
    //Si el voltaje frontal esta entre 0,5 y 2,7, ingresa al IF
    if ((voltajeFrontal > 0.5) && (voltajeFrontal < 2.7)){
      //Realiza el calculo de la distancia del sensor frontal
      distanciaFrontal=(((16.75*pow(voltajeFrontal,4.0))-119.26*pow(voltajeFrontal,3.0))+(311.7*pow(voltajeFrontal,2.0))-(365.71*voltajeFrontal)+184.03);
      //Si la distancia del sensor frontal es menor a 10 cm ingresa al IF
      while (distanciaFrontal < 10.0){
        //Si el voltaje izquierda esta entre 0,5 y 2,7, ingresa al IF
        if ((voltajeIzquierda > 0.5) && (voltajeIzquierda < 2.7)){
          //Realiza el calculo de la distancia del sensor izquierdo
          distanciaIzquierda=(((16.75*pow(voltajeIzquierda,4.0))-119.26*pow(voltajeIzquierda,3.0))+(311.7*pow(voltajeIzquierda,2.0))-(365.71*voltajeIzquierda)+184.03);
          //Si la distancia del sensor izquierdo es menor a 10 cm ingresa al IF
          if (distanciaIzquierda < 10.0){ 
            //Si el voltaje derecha esta entre 0,5 y 2,7, ingresa al IF
            while ((voltajeDerecha > 0.5) && (voltajeDerecha < 2.7)){
              //Realiza el calculo de la distancia del sensor derecho
              distanciaDerecha=(((16.75*pow(voltajeDerecha,4.0))-119.26*pow(voltajeDerecha,3.0))+(311.7*pow(voltajeDerecha,2.0))-(365.71*voltajeDerecha)+184.03);
            }
            //Si la distancia del sensor derecho es menor a 10 cm ingresa al IF
            while (distanciaDerecha < 10.0){ 
              giro_180();
            }
          }
          else{
            giro_der90();
          } 
        }
        //Si la distancia del sensor frontal es mayor a 10 cm ingresa al IF
        else{ 
          giro_izq90();
        }
      }
    }
    else{ 
      if ((voltajeIzquierda > 0.5) && (voltajeIzquierda < 2.7)){
        distanciaIzquierda=(((16.75*pow(voltajeIzquierda,4.0))-119.26*pow(voltajeIzquierda,3.0))+(311.7*pow(voltajeIzquierda,2.0))-(365.71*voltajeIzquierda)+184.03);
        while (distanciaIzquierda<10.0){
          giro_der90();
        }
      }
      else{
        if ((voltajeDerecha >0.5) && (voltajeDerecha<2.7)){
          distanciaDerecha=(((16.75*pow(voltajeDerecha,4.0))-119.26*pow(voltajeDerecha,3.0))+(311.7*pow(voltajeDerecha,2.0))-(365.71*voltajeDerecha)+184.03);
          while (distanciaDerecha<10.0){ 
            giro_izq90();
          }
        }
      }      
    }
  }  
}