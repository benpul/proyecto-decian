#include <16F877A.h>
#device adc=8
#fuses XT, NOWDT, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT,
#use delay(clock=4000000)
#include <math.h>
float volta,volti,voltd,disa,disi,disd;
int  adelante,izq,der;

void giro_180(){
  setup_timer_2(T2_DIV_BY_4,255,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
  setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
    set_pwm1_duty(207);
  set_pwm2_duty(80);
  delay_ms(500);
}

void giro_der90(){
  
    setup_timer_2(T2_DIV_BY_4,255,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
  setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
    set_pwm1_duty(207);
  set_pwm2_duty(80);
  delay_ms(250);
}

void giro_izq90(){
  setup_timer_2(T2_DIV_BY_4,255,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
  setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
    set_pwm1_duty(80);
  set_pwm2_duty(207);
  delay_ms(250);
}



void main(){
  set_tris_A(0x1F);
  set_tris_C(0x00);
     
     setup_adc(ADC_CLOCK_DIV_4);
     setup_adc_ports(3);
    
  
  while(1){
    setup_timer_2(T2_DIV_BY_16,255,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
      setup_ccp1(CCP_PWM);
      setup_ccp2(CCP_PWM);
    set_pwm1_duty(207);
      set_pwm2_duty(80);;
        set_adc_channel(0);
    delay_ms(15);
    adelante = read_adc();
    volta = adelante*5.0/256.0;
        set_adc_channel(1);
      delay_ms(15);
    izq = read_adc();
        volti = izq* 5.0/256.0;
        set_adc_channel(2);
    delay_ms(15);
    der = read_adc();
    voltd = der* 5.0/256.0;
        if ((Volta >0.5) && (volta<2.7)){
                disa=(((16.75*pow(volta,4.0))-119.26*pow(volta,3.0))+(311.7*pow(volta,2.0))-(365.71*volta)+184.03);
                        if (disa<10.0){
                                        
                                if ((volti >0.5) && (volti<2.7)){
                                            disi=(((16.75*pow(volti,4.0))-119.26*pow(volti,3.0))+(311.7*pow(volti,2.0))-(365.71*volti)+184.03);
                                            if (disi<10.0){ 
                                            if ((voltd >0.5) && (voltd<2.7)){
                                            disd=(((16.75*pow(voltd,4.0))-119.26*pow(voltd,3.0))+(311.7*pow(voltd,2.0))-(365.71*voltd)+184.03);
                                            }if (disd<10.0){ 
                                                     set_pwm1_duty(207);
                                                     set_pwm2_duty(80);
                                                   delay_ms(500);
                                                   giro_180();
                                            }else {giro_der90();
                                                       set_pwm1_duty(207);
                                                     set_pwm2_duty(80);
                                                     delay_ms(250);  }

                                     }else{
                                          giro_izq90();
                                              set_pwm1_duty(80);
                                            set_pwm2_duty(207);
                                          delay_ms(250);  
                                                        }
                        }else{ set_pwm1_duty(80);
                                            set_pwm2_duty(207);
                                          delay_ms(250);

                        } 
       }
                        
           
                
       else{ 
           if ((volti >0.5) && (volti<2.7)){
                disi=(((16.75*pow(volti,4.0))-119.26*pow(volti,3.0))+(311.7*pow(volti,2.0))-(365.71*volti)+184.03);
                if (disi<10.0){
                     set_pwm1_duty(207);
                   set_pwm2_duty(80);
                   delay_ms(250); 

                      giro_der90();
                }
              }
              
        else{
              if ((voltd >0.5) && (voltd<2.7)){
                       disd=(((16.75*pow(voltd,4.0))-119.26*pow(voltd,3.0))+(311.7*pow(voltd,2.0))-(365.71*voltd)+184.03);
                       if (disd<10.0){ 
                            set_pwm1_duty(80);
                            set_pwm2_duty(207);
                          delay_ms(250); 


                              giro_izq90();
                       }
              }
            }      
        
 }  

}
}
}